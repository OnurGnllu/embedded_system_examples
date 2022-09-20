#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"
#include <PubSubClient.h>


char connID[] = "broker.shiftr.io";
char ssid[] = "Redmi";           // your network SSID (name)
char pass[] = "onur1905";           // your network pass
char user_token_name[] = "***your token name**";          //your shiftr user token name
char user_token[] = "***your token***";  //your shiftr user token

int status = WL_IDLE_STATUS;


WiFiClient espClient;
PubSubClient client(espClient);
int ledPin = 13;

SoftwareSerial soft(10, 11); // RX, TX

unsigned long lastTime = 0;
int btn1 = 4, btn2 = 5, btn3 = 6;
bool ledS1 = false, ledS2 = false, ledS3 = false;

void setup() {

  pinMode(ledPin, OUTPUT);

  //butons used with pull up resistors
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(btn3, INPUT_PULLUP);

    // Set software serial baud to 115200;
    Serial.begin(115200);
    pinMode(BUILTIN_LED, OUTPUT);
    // connecting to a WiFi network
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    //connecting to a mqtt broker
   client.setServer(connID, 1883);
  //  client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        Serial.println("MQTT ye baglanıyor...");
        if (client.connect("arduino", user_token_name, user_token)) {
            Serial.println("Baglandı");
        } else {
            Serial.print("failed with state ");
            Serial.print(client.state());
            delay(2000);
        }
    }
}
void loop() {
  // put your main code here, to run repeatedly:

  //reconnect if not connetc to broker or connection lost
  if (!client.connected()) {
    reconnect();
  }

  char val[2];

  if (!digitalRead(btn1))         //buton1' e basıldı mı
  {
    if (ledS1) strcpy(val, "1");    //ledin durumunu
    else strcpy(val, "0");          //tampona yazdık
    client.publish("/esp8266/led1", val);    //tampondaki veriyi gönderdik
    ledS1 = !ledS1;                 //led durumunu değiştirdik
  }

  if (!digitalRead(btn2))
  {
    if (ledS2) strcpy(val, "1");
    else strcpy(val, "0");
    client.publish("/esp8266/led2", val);
    ledS2 = !ledS2;
  }

  if (!digitalRead(btn3))
  {
    if (ledS3) strcpy(val, "1");
    else strcpy(val, "0");
    client.publish("/esp8266/led3", val);
    ledS3 = !ledS3;
  }

  if (millis() - lastTime > 2000)
  {
    int aVal = analogRead(A0);
    char tBuff[15];
    sprintf(tBuff, "{\"analog2\": %d}", aVal);
    client.publish("sens/val2", tBuff);
    lastTime = millis();
  }
  client.loop();      //listen subscribed topics
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect, just a name to identify the client
    if (client.connect("arduino", user_token_name, user_token)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("Wake", "Arduino-Wake");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
