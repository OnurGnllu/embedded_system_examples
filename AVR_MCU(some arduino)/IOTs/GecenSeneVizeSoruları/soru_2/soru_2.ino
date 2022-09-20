#include <ESP8266WiFi.h>
int value =0;
int vizenotu;
int finalnotu;
float sonuc;
String cevap;

String apiKey = "93FMIWQVGLBTM38X";     //  Enter your Write API key from ThingSpeak
const char* server_thingspeak = "api.thingspeak.com";
const char* ssid = "OnurWi-fi";
const char* password = "Onur.1905";
WiFiClient client;
WiFiServer server(80); // Webpage icin kurulan server
 
void setup() {
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
    vizenotu=100;
    finalnotu=90;
    sonuc = (vizenotu+finalnotu)/2;
    
// gelen istekleri okuyoruz
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();
 
if (request.indexOf("/vize") != -1) {
     value = 1;
}
if (request.indexOf("/final") != -1) {
     value = 2;
}

if (request.indexOf("/sonuc") != -1) { 
     value = 3;
     if (sonuc>=50){
      cevap = "GECTI";
      }
     else if (sonuc<50){
      cevap = "KALDI";
      }
}
 
// bu kısımda html kodlarını internet arayüzüne yazdırıyoruz.
 
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); 
client.println("<!DOCTYPE HTML>");
client.println("<html>");
 


 
if(value == 1) {
client.print("Vizeden Bekledigim Not = ");
client.print(vizenotu);
Serial.print("Vizeden Bekledigim Not = ");
Serial.println(vizenotu);
}
else if(value == 2) {
client.print("Finalden Bekledigim Not = ");
client.print(finalnotu);
Serial.print("Finalden Bekledigim Not = ");
Serial.println(finalnotu);
}
else if(value == 3) {
client.print("DURUMU=  ");
client.print(cevap);
Serial.print("DURUMU=  ");
Serial.println(cevap);
}

client.println("");
client.println("</html>");
 
delay(1);
Serial.println("Client disconnected");
Serial.println("");



 //Thingspeak deneme

                          if (client.connect(server_thingspeak,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(vizenotu);
                             postStr +="&field2=";
                             postStr += String(finalnotu);
                             postStr +="&field3=";
                             postStr += String(sonuc);
                             postStr += "\r\n\r\n";
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);

                        }
          client.stop();
          Serial.println("Waiting...");
           // delay(10000); // Bu uygulama özelinde Kaldirilmasi gerek   // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
}
