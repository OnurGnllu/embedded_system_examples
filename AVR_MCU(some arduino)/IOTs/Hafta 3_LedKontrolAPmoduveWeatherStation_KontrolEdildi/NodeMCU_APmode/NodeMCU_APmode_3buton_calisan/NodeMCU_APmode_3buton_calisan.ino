#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "OnurG";  // Enter SSID here
const char* password = "123456789";  //Enter Password here

//const char* ssid = "FiberHGW_ZTRF6K_2.4Ghz";  // Enter SSID here
//const char* password = "hUpeexujtd";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

uint8_t LED1pin = D7;
bool LED1status = LOW;
uint8_t LED2pin = D6;
bool LED2status = LOW;
uint8_t LED3pin = D8;
bool LED3status = LOW;


void setup() {
 WiFi.mode(WIFI_AP_STA); //AP ve STA mod tanımlanır ayrıca default IP adresi yerine kendi tanımladığımız bir IP adresi girmek istiyorsak zorunlu bir komuttur.
 pinMode(LED1pin, OUTPUT);
 pinMode(LED2pin, OUTPUT);
 pinMode(LED3pin, OUTPUT);
 Serial.begin(115200);
 Serial.println();
 WiFi.softAPConfig(local_ip, gateway,subnet); //.softAPConfig komutu ile yeni bir IP adresi atanır.
 WiFi.softAP(ssid, password); // yeni kullanıcı adı ve şifre atanır. ÖNEMLİ.. IPConfig atamasından sonra tanımlanmalıdır.
 IPAddress nodemcu_IP = WiFi.softAPIP(); // Kontrol amaçlı atanan Ip adresi seri ekrana yazdırılır.
 Serial.print(ssid); Serial.println(" İsimli Wifi Ağına bağlan.");
 Serial.print("Use This IP Address to Connect: ");
 Serial.println(nodemcu_IP); //Seri ekranda gör.
  
  server.on("/", handle_OnConnect);
  server.on("/led1on", handle_led1on);
  server.on("/led1off", handle_led1off);
  server.on("/led2on", handle_led2on);
  server.on("/led2off", handle_led2off);
  server.on("/ledblinkon", handle_ledblinkon); //yeni
  server.on("/ledblinkoff", handle_ledblinkoff); //yeni
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  if(LED1status)
  {digitalWrite(LED1pin, HIGH);
}
  else
  {digitalWrite(LED1pin, LOW);}
  
  if(LED2status)
  {digitalWrite(LED2pin, HIGH);
 }
  else
  {digitalWrite(LED2pin, LOW);}

  if(LED3status)
  
  {digitalWrite(LED3pin,HIGH);
   delay(50);
   digitalWrite(LED3pin,LOW);
   delay(50);
   digitalWrite(LED1pin, HIGH);
   delay(50);
   digitalWrite(LED1pin, LOW);
   delay(50);
   digitalWrite(LED2pin, HIGH);
   delay(50);
   digitalWrite(LED2pin, LOW);
   delay(50);
  }
  else 
  {digitalWrite(LED3pin,LOW);
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, LOW);
  }
}

void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  LED3status = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,LED3status)); 
}

void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true,LED2status,LED3status)); 
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false,LED2status,LED3status)); 
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status,true,LED3status)); 
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status,false,LED3status)); 
}

void handle_ledblinkon(){
 LED3status = HIGH;
  Serial.println("LED Blinking");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,true)); 
  }
void handle_ledblinkoff(){
  LED3status = LOW;
  Serial.println("LED is not Blinking");
  server.send(200, "text/html", SendHTML(LED1status,LED2status,false));
  }
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat,uint8_t led3stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body bgcolor=orange style=color:white>\n"; //background color
  ptr +="<h2>Onur GONULLU</h1>\n";
  ptr +="<h3>IOT DERSI</h2>\n";
  ptr +="<h4>Using Access Point(AP) Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Durum: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Durum: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Durum: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Durum: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

//LED3pin
 
  if(led3stat)
  {ptr +="<p>BLINK Durumu: ON</p><a class=\"button button-off\" href=\"/ledblinkoff\">NO BLINK</a>\n";} //yeni button tipi eklemeye gerek yok..
  else
  {ptr +="<p>BLINK Durumu: OFF</p><a class=\"button button-on\" href=\"/ledblinkon\">BLINK</a>\n";}


  
  
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
