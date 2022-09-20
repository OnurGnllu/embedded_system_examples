#include <ESP8266WiFi.h>
int led1 = D6;
int value =0;
const char* ssid = "Redmi";
const char* password = "onur1905";
WiFiServer server(80);
 
void setup() {
Serial.begin(115200);
pinMode(led1, OUTPUT);

delay(10);

   pinMode(LED_BUILTIN, OUTPUT);
   
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
     digitalWrite(led1, HIGH);
     
     value = 1;
}
if (request.indexOf("/LED-KAPALI") != -1) {
     digitalWrite(led1, LOW);
    
     value = 2;
}

if (request.indexOf("/uckezyak") != -1) { 
   for(int i=1; i<3; i++){
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    delay(500);
    
    }
     value = 3;
}

if (request.indexOf("/onbeskezyak") != -1) { 
   for(int i=1; i<14; i++){
    digitalWrite(led1,HIGH);
    delay(500);
    digitalWrite(led1,LOW);
    delay(500);
    
    }
     value = 4;
}
// bu kısımda html kodlarını internet arayüzüne yazdırıyoruz.
 
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); 
client.println("<!DOCTYPE HTML>");
client.println("<html>");
 


 
if(value == 1) {
client.print("NODEMCU LED suanda: ");
client.print("ACIK");
}
else if(value == 2) {
 client.print("NODEMCU LED suanda: ");
client.print("KAPALI");
}
else if(value == 3) {
client.print("3 kez yandi");
}
else if(value == 4) {
client.print("15 kez yandi.");
}
client.println("");
client.println("<a href=\"/LED-ACIK\"\"><button>ledi yak </button></a>");
client.println("<a href=\"/LED-KAPALI\"\"><button>ledi sondur</button></a>");
client.println("<a href=\"/uckezyak\"\"><button>3 KEZ YAK SONDUR</button></a>");
client.println("<a href=\"/onbeskezyak\"\"><button>15 KEZ YAK SONDUR</button></a>");
client.println("</html>");
 
delay(1);
Serial.println("Client disconnected");
Serial.println("");
 
}
