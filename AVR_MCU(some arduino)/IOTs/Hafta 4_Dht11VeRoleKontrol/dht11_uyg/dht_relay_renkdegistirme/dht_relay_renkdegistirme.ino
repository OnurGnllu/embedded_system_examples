#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"

// Uncomment one of the lines below for whatever DHT sensor type you're using!
  #define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

//Put your SSID & Password/
const char* ssid = "OnurWi-fi";  // Enter SSID here
const char* password = "onur1905";  //Enter Password here



ESP8266WebServer server(80);

// DHT Sensor
uint8_t DHTPin = D7; // mini nodeMCU da D7, normalde D8 calisiyor...
uint8_t relay = D6;   
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                

float Temperature;
float Humidity;
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(DHTPin, INPUT);
  pinMode(relay, OUTPUT);

  dht.begin();              

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
 float Temperature1 = dht.readTemperature();
  server.handleClient();
  Serial.println();
      Serial.print(Temperature1);
    if (Temperature1>=27){
     // Serial.println("  Röle Acik");
    digitalWrite(relay,LOW);
   // delay(500);
    }
  else if (Temperature1<27){
    // Serial.println("  Röle Kapali");
    digitalWrite(relay,HIGH);
   // delay(500);
    }
     delay(1000);

}

void handle_OnConnect() {

 Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity 
  server.send(200, "text/html", SendHTML(Temperature,Humidity)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat,float Humiditystat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP8266 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="r {font-size: 24px;color: #FF0000;margin-bottom: 10px;}\n";
  ptr +="g {font-size: 24px;color: #00FF00;margin-bottom: 10px;}\n";
  ptr +="d {font-size: 24px;color: #3300CC;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP8266 NodeMCU Weather Report</h1>\n";
  
  ptr +="<p>Temperature: ";
  ptr +=(float)Temperaturestat;
  ptr +=" C</p>";
  ptr +="<p>Humidity: ";
  ptr +=(float)Humiditystat;
  ptr +="%</p>";

 if(Temperaturestat>27){
   ptr +="<d>DURUM: ";
   ptr +="<r>Sicaklik 27 dereceyi asti. Role aktif";
 }
  else if (Temperaturestat<27){
   ptr +="<d>DURUM: ";
    ptr +="<g>Sicaklik normal derecede.";
 
    }
  

  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
