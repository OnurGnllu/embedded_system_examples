#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// GPIO 5 D1
#define LED D0 
unsigned long previousMillis = 0;
const long interval = 1000;
#define FIVE_SECONDS 5000
unsigned long current_time;
unsigned long last_run = 0;
int sensorValue = 15;

// WiFi
const char *ssid = "OnurWi-fi"; // Enter your WiFi name
const char *password = "Onur.1905";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "io.adafruit.com";
const char *topic = "onurgnllu/f/mytest";
const char *mqtt_username = "onurgnllu";
const char *mqtt_password = "aio_ZDwe95DR8PzK7bjY6AecWE2Gslsz";
const int   mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    // Set software serial baud to 115200;
    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    // connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        Serial.println("MQTT ye baglanıyor...");
        if (client.connect("ESP8266", mqtt_username, mqtt_password)) {
            Serial.println("Baglandı");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
    // publish and subscribe
    client.publish(topic, "Nodemcu is connected");
    client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    String message;
    for (int i = 0; i < length; i++) {
        message = message + (char) payload[i];  // convert *byte to string
    }
    Serial.print(message);
    if (message == "led_on") {
    digitalWrite(BUILTIN_LED, LOW);  
    Serial.print("\nled yandi");}   // LED on
    if (message == "led_off") {
    digitalWrite(BUILTIN_LED, HIGH);
    Serial.print("\nled sondu");} // LED off
    Serial.println();
    Serial.println("-----------------------");


}

void loop() {
    client.loop();



   current_time = millis();

    if (current_time - last_run >= FIVE_SECONDS) {
        // save the last time you blinked the LED
        last_run = current_time;
         sensorValue++;  // burada sahte bir sayaç ile 1+2+3+4+5
         String ldrValue = String(sensorValue);
         client.publish("onurgnllu/f/publishedvalue", ldrValue.c_str());
         Serial.print("LDR: ");
         Serial.print(ldrValue);
         Serial.println("Message published");
  }


    

}
