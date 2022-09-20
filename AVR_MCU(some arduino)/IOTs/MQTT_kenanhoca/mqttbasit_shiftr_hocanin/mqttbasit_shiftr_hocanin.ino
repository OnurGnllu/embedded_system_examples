#include <MQTT.h>
#include <MQTTClient.h>
#include <ESP8266WiFi.h>  
#include <MQTTClient.h>

#define led1 D2

char ssid[] = "Redmi";
char pass[] = "onur1905";


//------ MQTT broker settings and topics

//const char* broker = "broker.emqx.io"; 
//const char* broker = "broker.hivemq.com"; 
// const char* broker = "mqtt.fluux.io"; 



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
   
  pinMode(led1, OUTPUT); 
  digitalWrite(led1, LOW);
 
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
 // oku();   
  lastMillis = millis();
  }

}


void oku() {                  
         
  if (alinan_mesaj_topic1 == 1) {
    digitalWrite(led1, HIGH); 
  //   client.publish("topic2", String(alinan_mesaj_topic1),true,1);
  
   Serial.println("\led yanik!");      
      }  
       else {
        digitalWrite(led1, LOW); 

           Serial.println("\led sonuk!");   
           }
       
  }
