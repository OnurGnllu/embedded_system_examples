#include <MQTT.h>
#include <MQTTClient.h>
#include <ESP8266WiFi.h> 
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

const char* broker = "onurgonullu.cloud.shiftr.io"; 
char mqttUserName[] = "onurgonullu";         
char mqttPass[] = "12345";    

WiFiClient client;
MQTTClient mqtt_client;
unsigned long lastMillis = 0;

int alinan_mesaj_topic1; 
int alinan_aktivasyon;
char ssid[] = "OnurWi-fi";       // your network SSID (name)
char password[] = "Onur.1905";  // your network keyS
String cities [] = {"istanbul","manisa","ankara"};
// For Non-HTTPS requests
 
void connect() {
 
   char clientID[] ="OnurGonullu"; 
  Serial.print("\nconnecting to broker...");
  while (!mqtt_client.connect(clientID,mqttUserName,mqttPass)) {
    Serial.print(".");
    delay(5000);
  }
  Serial.println("\nconnected!");   
   mqtt_client.subscribe("topic1"); 
   mqtt_client.subscribe("deneme");
}

////// https://api.openweathermap.org/data/2.5/weather?q=istanbul,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric
// Just the base of the URL you want to connect to
#define TEST_HOST "api.openweathermap.org"
String city ;
// #define TEST_HOST_OTHERPART "/data/2.5/weather?q=" + city + ",TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric"



void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 mqtt_client.begin(broker, client);
 connect();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");

 


  
}




void makeHTTPRequest(String name_city) {
#define TEST_HOST "api.openweathermap.org"
#define TEST_HOST_OTHERPART "/data/2.5/weather?q=" + name_city + ",TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric"
 
  if (!client.connect(TEST_HOST, 80))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  yield();
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  client.print(TEST_HOST_OTHERPART); 
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);

  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0)
  {
    Serial.println(F("Failed to send request"));
    return;
  }
  //delay(100);
  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    return;
  }

  // This is probably not needed for most, but I had issues
  // with the Tindie api where sometimes there were random
  // characters coming back before the body of the response.
  // This will cause no hard to leave it in
  // peek() will look at the character, but not take it off the queue
  while (client.available() && client.peek() != '{')
  {
    char c = 0;
    client.readBytes(&c, 1);
    Serial.print(c);
    Serial.println("BAD");
  }

StaticJsonDocument<32> filter;
filter["main"] = true;
filter["name"] = true;

StaticJsonDocument<1024> doc;

DeserializationError error = deserializeJson(doc, client, DeserializationOption::Filter(filter));

if (error) {
  Serial.print(F("deserializeJson() failed: "));
  Serial.println(error.f_str());
  return;
}

JsonObject main = doc["main"];
float main_temp = main["temp"]; // 28.45
float main_feels_like = main["feels_like"]; // 28.77
float main_temp_min = main["temp_min"]; // 23.92
float main_temp_max = main["temp_max"]; // 28.68
int main_pressure = main["pressure"]; // 1015
int main_humidity = main["humidity"]; // 48

const char* name = doc["name"]; // "Istanbul"

    Serial.print("city: ");
    Serial.println(name);
    Serial.print("temp: ");
    Serial.println(main_temp);
    Serial.print("feels_like: ");
    Serial.println(main_feels_like);

    Serial.print("temp_min: ");
    Serial.println(main_temp_min);
    Serial.print("temp_max: ");
    Serial.println(main_temp_max);

    Serial.print("pressure: ");
    Serial.println(main_pressure);
    Serial.print("humidity: ");
    Serial.println(main_humidity);
    if (!mqtt_client.connected())connect(); // loop içine atıldığında veri gönderdikten sonra aktif oluyor.
    mqtt_client.publish(name_city, String(main_temp),true,1);
    mqtt_client.publish(name_city + "_hissedilensicaklik", String(main_feels_like),true,1);
    mqtt_client.publish(name_city + "_basinc", String(main_pressure),true,1);
    mqtt_client.publish(name_city + "_nem", String(main_humidity),true,1);
    
  

}





void loop() {
 mqtt_client.loop();
  if (millis() - lastMillis > 5000) {  
         for(int i = 0; i<3; i++){
  makeHTTPRequest(cities[i]);
  }
  lastMillis = millis();
  }
 
}
