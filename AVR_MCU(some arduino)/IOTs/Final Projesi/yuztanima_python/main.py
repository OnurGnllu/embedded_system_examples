import cv2
from simple_facerec import SimpleFacerec
from mqtt_adapter import mqtt_yaz
from excel_adapter import excel_yaz

# Encode faces from a folder
sfr = SimpleFacerec()
sfr.load_encoding_images("image_databasefile/")

# Load Camera
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()
    # Detect Faces
    face_locations, face_names = sfr.detect_known_faces(frame)
    for face_loc, name in zip(face_locations, face_names):
        y1, x2, y2, x1 = face_loc[0], face_loc[1], face_loc[2], face_loc[3]

        cv2.putText(frame, name,(x1, y1 - 10), cv2.FONT_HERSHEY_DUPLEX, 1, (0, 0, 200), 2)
        cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 0, 200), 4)
        mqtt_yaz(name) #mqtt burada cagiriyoruz
        excel_yaz(name)
    cv2.imshow("Yuz Tanima", frame)

    key = cv2.waitKey(1) #bir tuşa basılırsa
    if key == 27: # ve bu tuş esc ise
        break
cap.release()
cv2.destroyAllWindows()
