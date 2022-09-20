#include <MQTT.h>
#include <MQTTClient.h>
#include <ESP8266WiFi.h>  
#include <MQTTClient.h>

#define led1 D2

char ssid[] = "Redmi";
char pass[] = "onur1905";


const char* broker = "onurgonullu.cloud.shiftr.io"; 
char mqttUserName[] = "onurgonullu";         
char mqttPass[] = "12345";               


WiFiClient net;
MQTTClient client;
unsigned long lastMillis = 0;

int alinan_mesaj_topic1; 
int alinan_aktivasyon;

//========================================= connect
void connect() {
  Serial.print("\nconnecting to wifi.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }
   char clientID[] ="OnurGonullu"; 
  Serial.print("\nconnecting to broker...");
  while (!client.connect(clientID,mqttUserName,mqttPass)) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nconnected!");   
   client.subscribe("kapi_control"); 
}


//========================================= messageReceived
void messageReceived(String &topic, String &payload) {

if (topic=="kapi_control") {  
   alinan_mesaj_topic1 = (payload.toInt());                              
 girdi_oku();                 
} 


}


//========================================= setup

void setup() {
  Serial.begin(115200);
   
  pinMode(led1, OUTPUT); 
 
  WiFi.begin(ssid, pass); 
  client.begin(broker, net); //broker , wifi

  client.onMessage(messageReceived); 
  connect();
}
//========================================= loop

void loop() { 
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected())connect(); 
 
  if (millis() - lastMillis > 3000) {       
  girdi_oku();   
  lastMillis = millis();
  }

}


void girdi_oku() {                  
         
  if (alinan_mesaj_topic1 == 1) {
    digitalWrite(led1, HIGH); 
   Serial.println("kapi acildi");
      }  
       else {
        digitalWrite(led1, LOW); 
           Serial.println("kapi kapatildi");   
           }

  }
