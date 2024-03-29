#include <ESP8266WiFi.h>
 
const char* ssid = "FiberHGW_ZTRF6K_2.4GHz";
const char* password = "hUpeexujtd";

 
int ledPin = 13; // GPIO13 ucu D7 ye karsılık gelir bahsettigimiz gibi
WiFiServer server(80);
 
void setup() {
Serial.begin(115200);
delay(10);

   pinMode(LED_BUILTIN, OUTPUT);//Dahili led kullanılmak istenirse

   
pinMode(ledPin, OUTPUT);
digitalWrite(ledPin, LOW);
 
// Wifi bağlantısı
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
// server baslatılıyor
server.begin();
Serial.println("Server started");
 
// baglantı saglandıktan sonra serial monitorde bize ip adresini gösterecek
Serial.print("Use this URL to connect: ");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
 
}
 
void loop() {
// bir clien istemci baglı olup olmadığını kontrol ediyoruz
WiFiClient client = server.available();
if (!client) {
return;
}
 
// client ın bir data gondermesini bekliyoruz
Serial.println("new client");
while(!client.available()){
delay(1);
}
 
// gelen istekleri okuyoruz
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
 
int value = LOW;
if (request.indexOf("/LED-ACIK") != -1) {
digitalWrite(ledPin, HIGH);
     digitalWrite(LED_BUILTIN, HIGH);   
value = HIGH;
}
if (request.indexOf("/LED-KAPALI") != -1) {
digitalWrite(ledPin, LOW);
      digitalWrite(LED_BUILTIN, LOW);
value = LOW;
}
 
// bu kısımda html kodlarını internet arayüzüne yazdırıyoruz.
 
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); 
client.println("<!DOCTYPE HTML>");
client.println("<html>");
 
client.print("Led suanda: ");
 
if(value == HIGH) {
client.print("ACIK");
} else {
client.print("KAPALI");
}
client.println("");
client.println("<a href=\"/LED-ACIK\"\"><button>ledi yak </button></a>");
client.println("<a href=\"/LED-KAPALI\"\"><button>ledi sondur </button></a>"); 

client.println("<a href=\"/deneme\"\"><button>deneme butonu </button></a>"); 

client.println("</html>");
 
delay(1);
Serial.println("Client disconnected");
Serial.println("");
 
}
