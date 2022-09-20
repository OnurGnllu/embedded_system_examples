import paho.mqtt.client as mqttclient
import time


def on_connect(client,usedata,flags,rc):
    if rc==0:
        print("client is connected")
        global connected
        connected=True
    else:
        print("connection failed")

#mqtt broker codes:
connected=False
mqtt_port = 1883
mqtt_broker = "onurgonullu.cloud.shiftr.io"
mqtt_username = "onurgonullu"
mqtt_password = "12345"

client = mqttclient.Client("MQTT")
client.username_pw_set(mqtt_username,password=mqtt_password)
client.on_connect=on_connect
client.connect(mqtt_broker,port=mqtt_port)
client.loop_start()

while connected!=True:
    time.sleep(0.2)
#mqqt kodları burada bitti.


def mqtt_yaz(name): #name değiskeni mainden gönderilir

 if (name == "unknown"):
     client.publish("kapi_control", 0)
     client.publish("isim_control", name)
     client.loop_stop()
 else:
     client.publish("kapi_control", 1)
     client.publish("isim_control", name)
     time.sleep(2)
     client.publish("kapi_control", 0)
     client.publish("isim_control", "unknown")

     #client.publish("kapi_control", "ac")
     client.loop_stop()
