const int data_pin = 2;
const int clock_pin = 3;
const int latch_pin = 4;
int counter = 0;
int signal = B10000000;
byte led;

void setup() {
  
  pinMode(data_pin, OUTPUT);  //enable pin 2 as data pin
  pinMode(clock_pin, OUTPUT); //enable pin 3 as clock pin
  pinMode(latch_pin, OUTPUT); //enable pin 4 as latch pin   
  
}
 
void loop() {
led =B10101111;    
put_Register(led);
delay(500);  
led =B10101101;
put_Register(led);
delay(5000);          

}



void put_Register(byte led)
{
digitalWrite(latch_pin, LOW);
shiftOut(data_pin, clock_pin, LSBFIRST,led);
digitalWrite(latch_pin, HIGH);

}
