#include <MQTT.h>
#include <MQTTClient.h>
#include <ESP8266WiFi.h>  
#include <MQTTClient.h>
#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
uint8_t DHTPin = D6;
uint8_t led1 = D7;
DHT dht(DHTPin, DHTTYPE);                
float Temperature;
float Humidity;


char ssid[] = "Redmi";
char pass[] = "onur1905";



const char* broker = "kenbuyukatak.cloud.shiftr.io"; 
char mqttUserName[] = "kenbuyukatak";         
char mqttPass[] = "123456789";               


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
   client.subscribe("topic1"); 
   client.subscribe("deneme");
}


//========================================= messageReceived
void messageReceived(String &topic, String &payload) {

if (topic=="topic1") {
     Serial.println("mesaj geldi");   

   alinan_mesaj_topic1 = (payload.toInt());                              
 //  digitalWrite(led1, LOW);
 oku();                 
} 


if (topic=="deneme") {
   Serial.println(" cep telefonundan nodeMcu ya bilgi gitti");
}


  
}


//========================================= setup

void setup() {
  Serial.begin(9600);
   
  pinMode(DHTPin, INPUT);
   dht.begin();
  digitalWrite(led1, OUTPUT);
 
  WiFi.begin(ssid, pass); 
  client.begin(broker, net);

  client.onMessage(messageReceived); 
  connect();
}
//========================================= loop

void loop() {
 
  client.loop();
  delay(10);  // <- fixes some issues with WiFi stability
  if (!client.connected())connect(); 
 
  if (millis() - lastMillis > 3000) {       
  oku();   
  lastMillis = millis();
  }


}


void oku() {                  
Temperature = dht.readTemperature();
Humidity = dht.readHumidity();
client.publish("onur_sensor", String(Temperature),true,1);
client.publish("onur_hum", String(Humidity),true,1);
Serial.println(Temperature);
Serial.println(Humidity);
 
  
  if (alinan_mesaj_topic1 == 1) {
    digitalWrite(led1, HIGH); 
     
  
   Serial.println("\led yanik!");      
      }  
       else {
        digitalWrite(led1, LOW); 

           Serial.println("\led sonuk!");   
           }
       
  }
