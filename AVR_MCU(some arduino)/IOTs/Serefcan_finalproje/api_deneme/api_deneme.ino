#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>


char ssid[] = "POCO X3 Pro";       // your network SSID (name)
char password[] = "12345678900";  // your network key

// For Non-HTTPS requests
 WiFiClient client;


////// https://api.openweathermap.org/data/2.5/weather?q=istanbul,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric
// Just the base of the URL you want to connect to
#define TEST_HOST "api.openweathermap.org"
// OPTIONAL - The finferprint of the site you want to connect to.
//#define TEST_HOST_FINGERPRINT "89 25 60 5D 50 44 FC C0 85 2B 98 D7 D3 66 52 28 68 4D E6 E2"
// The finger print will change every few months.


void setup() {

  Serial.begin(115200);

  // Connect to the WiFI
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");



  //--------

  // If you don't need to check the fingerprint
//  client.setInsecure();

  // If you want to check the fingerprint
  //client.setFingerprint(TEST_HOST_FINGERPRINT);

  makeHTTPRequest();
}

void makeHTTPRequest() {

  // Opening connection to server (Use 80 as port if HTTP)
  if (!client.connect(TEST_HOST, 80))
  {
    Serial.println(F("Connection failed"));
    return;
  }

  // give the esp a breather
  yield();

  // Send HTTP request
  client.print(F("GET "));
  // This is the second half of a request (everything that comes after the base URL)
  client.print("/data/2.5/weather?q=istanbul,TR&appid=c593dca9f1e67108b4a0aa1b670e72fc&units=metric"); // %2C == ,
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

  //  // While the client is still availble read each
  //  // byte and print to the serial monitor
  //  while (client.available()) {
  //    char c = 0;
  //    client.readBytes(&c, 1);
  //    Serial.print(c);
  //  }

  //Use the ArduinoJson Assistant to calculate this:

  //StaticJsonDocument<192> doc;
 /// DynamicJsonDocument doc(192); //For ESP32/ESP8266 you'll mainly use dynamic.



// Stream& input;

StaticJsonDocument<32> filter;
filter["main"] = true;
filter["name"] = true;

StaticJsonDocument<256> doc;

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

    
  } 







void loop() {
  // put your main code here, to run repeatedly:

}
