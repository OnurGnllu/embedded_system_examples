#define DEBUGOUTPUT 0
#define kirmiziLed1  4
#define kirmiziLed2  5
#define kirmiziLed3  6
#define sariLed1     7
#define sariLed2     8
#define sariLed3     9
#define sariLed4     10
#define yesilLed1    11
#define yesilLed2    12
#define yesilLed3    13

byte kontrol = 0;
int uzunluk = 0;
byte veri[64] = {0};
byte sinyal = 0;
byte odaklanma = 0;
byte rahatlama = 0;
long sonAlinan = 0;
boolean paket = false;

void setup() 
{
  pinMode(kirmiziLed1, OUTPUT);
  pinMode(kirmiziLed2, OUTPUT);
  pinMode(kirmiziLed3, OUTPUT);
  pinMode(sariLed1, OUTPUT);
  pinMode(sariLed2, OUTPUT);
  pinMode(sariLed3, OUTPUT);
  pinMode(sariLed4, OUTPUT);
  pinMode(yesilLed1, OUTPUT);
  pinMode(yesilLed2, OUTPUT);
  pinMode(yesilLed3, OUTPUT);
  Serial.begin(57600);
}
byte fnkOku() 
{
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();
  #if DEBUGOUTPUT  
    Serial.print((char)ByteRead);  
  #endif
  return ByteRead;
}
void loop() 
{
  if(fnkOku() == 170) 
  {
    if(fnkOku() == 170) 
    {
        uzunluk = fnkOku();
        if(uzunluk > 169)  return;
        kontrol = 0;        
        for(int i = 0; i < uzunluk; i++) 
        {  
          veri[i] = fnkOku();  
          kontrol += veri[i];
        }   
        kontrol = 255 - kontrol;   
        if(fnkOku() == kontrol) 
        {    
          sinyal = 200;
          odaklanma = 0;
          rahatlama = 0;
          for(int i = 0; i < uzunluk; i++) 
          {                                         
            switch (veri[i]) 
            {
              case 2:
                i++;            
                sinyal = veri[i];
                paket = true;            
                break;
              case 4:
                i++;
                odaklanma = veri[i];                        
                break;
              case 5:
                i++;
                rahatlama = veri[i];
                break;
              case 0x80:
                i = i + 3;
                break;
              case 0x83:
                i = i + 25;      
                break;
              default:
                break;
            } 
          }

#if !DEBUGOUTPUT
    if(paket)
      {
          Serial.print("sinyal: ");
          Serial.print(sinyal, DEC);
          Serial.print(" odaklanma: ");
          Serial.print(odaklanma, DEC);
          Serial.print(" Time since last packet: ");
          Serial.print(millis() - sonAlinan, DEC);
          sonAlinan = millis();
          Serial.print("\n");
          
          switch(odaklanma / 10) 
          {
          case 0:
            digitalWrite(kirmiziLed1, LOW);
            digitalWrite(kirmiziLed2, LOW);
            digitalWrite(kirmiziLed3, LOW); 
            digitalWrite(sariLed1, LOW);
            digitalWrite(sariLed2, LOW);
            digitalWrite(sariLed3, LOW);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);
            break;
          case 1:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, LOW);
            digitalWrite(kirmiziLed3, LOW); 
            digitalWrite(sariLed1, LOW);
            digitalWrite(sariLed2, LOW);
            digitalWrite(sariLed3, LOW);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);
            break;
          case 2:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, LOW); 
            digitalWrite(sariLed1, LOW);
            digitalWrite(sariLed2, LOW);
            digitalWrite(sariLed3, LOW);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);
            break;
          case 3:              
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, LOW);
            digitalWrite(sariLed2, LOW);
            digitalWrite(sariLed3, LOW);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);            
            break;
          case 4:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, LOW);
            digitalWrite(sariLed3, LOW);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);           
            break;
          case 5:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, HIGH);
            digitalWrite(sariLed3, LOW);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);                
            break;
          case 6:              
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, HIGH);
            digitalWrite(sariLed3, HIGH);
            digitalWrite(sariLed4, LOW);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);               
            break;
          case 7:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, HIGH);
            digitalWrite(sariLed3, HIGH);
            digitalWrite(sariLed4, HIGH);
            digitalWrite(yesilLed1, LOW);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW);               
            break;    
          case 8:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, HIGH);
            digitalWrite(sariLed3, HIGH);
            digitalWrite(sariLed4, HIGH);
            digitalWrite(yesilLed1, HIGH);
            digitalWrite(yesilLed2, LOW);
            digitalWrite(yesilLed3, LOW); 
            break;
          case 9:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, HIGH);
            digitalWrite(sariLed3, HIGH);
            digitalWrite(sariLed4, HIGH);
            digitalWrite(yesilLed1, HIGH);
            digitalWrite(yesilLed2, HIGH);
            digitalWrite(yesilLed3, LOW); 
            break;
          case 10:
            digitalWrite(kirmiziLed1, HIGH);
            digitalWrite(kirmiziLed2, HIGH);
            digitalWrite(kirmiziLed3, HIGH); 
            digitalWrite(sariLed1, HIGH);
            digitalWrite(sariLed2, HIGH);
            digitalWrite(sariLed3, HIGH);
            digitalWrite(sariLed4, HIGH);
            digitalWrite(yesilLed1, HIGH);
            digitalWrite(yesilLed2, HIGH);
            digitalWrite(yesilLed3, HIGH); 
            break;           
          }                     
        }
#endif        
        paket = false;        
      }
      else 
      {
        // kontrol hatası
      }  
    } 
  } 
}
