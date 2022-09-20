from datetime import datetime
from datetime import date


today = date.today()
day = today.strftime("%b-%d-%Y")
dosya_adi = "taninankisiler" + day + ".csv"
print(dosya_adi)

dosya_acma = open(dosya_adi, "a")
dosya_acma.write("Ad, Saat")
dosya_acma.close()

def excel_yaz(name): #name deÄŸiskeni mainden gÃ¶nderilir

    with open(dosya_adi, 'r+') as f:
        myDataList = f.readlines()
        nameList = []
        for line in myDataList:
            entry = line.split(',')
            nameList.append(entry[0])

        if name not in nameList: #name degiskeni burada var mÄ±? Yok ise ekleyebilirsin.
            now = datetime.now()
            dtString = now.strftime('%H:%M:%S')
            f.writelines(f'\n{name},{dtString}')
            name2 = name + " ismiyle giris yapildi."