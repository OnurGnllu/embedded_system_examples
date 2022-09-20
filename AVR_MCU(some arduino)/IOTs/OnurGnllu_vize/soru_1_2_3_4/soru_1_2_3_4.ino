#include <ESP8266WiFi.h>
int value =0;
int gecti_led = D8;
int kaldi_led = D7;
const char* ssid = "Redmi";
const char* password = "onur1905";
WiFiServer server(80);
 
void setup() {
 pinMode(gecti_led,OUTPUT);
pinMode(kaldi_led,OUTPUT);
Serial.begin(115200);
delay(10); 
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

int vize_notum=40;
int final_notum=50;
float ortalamam = (vize_notum+vize_notum)/2;    
    
  
    
// gelen istekleri okuyoruz
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
 
if (request.indexOf("/vizeNotu") != -1) {
     value = 1;
}
if (request.indexOf("/finalNotu") != -1) {
     value = 2;
}

if (request.indexOf("/sonuc") != -1) { 
     value = 3;
 
}

// bu kısımda html kodlarını internet arayüzüne yazdırıyoruz.
 
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); 
client.println("<!DOCTYPE HTML>");
client.println("<html>");
 


 
if(value == 1) {
client.print("Benim vizeden aldıgim not = ");
client.print(vize_notum);
Serial.print("Benim vizeden aldigim not = ");
Serial.println(vize_notum);
}
else if(value == 2) {
client.print("Benim finalden aldigim not = ");
client.print(final_notum);
Serial.print("Benim finalden aldigim not = ");
Serial.println(final_notum);
}
else if(value == 3) {
if(ortalamam>=50){
  digitalWrite(gecti_led, HIGH);
  digitalWrite(kaldi_led, LOW);
  client.print("Dersten Gectiniz");
  Serial.print("Dersten Gectiniz");
  }
  else{
   digitalWrite(gecti_led, LOW);
   digitalWrite(kaldi_led, HIGH);
  client.print("Dersten Kaldiniz");
  Serial.print("Dersten Kaldiniz");
    }
}

client.println("");
client.println("</html>");
 
delay(1);
Serial.println("Client disconnected");
Serial.println("");
 
}
