const int data_pin = 12;
const int clock_pin = 7;
const int latch_pin = 8;
byte led1 =B11111111;
byte led2=B00000000;


void setup()
{
  pinMode(data_pin, OUTPUT);
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
}


void loop()
{
 put_D_register(led1,led2);
 
}
  
  
  
  void put_D_register(byte led1, byte led2)
{
    
 digitalWrite(latch_pin, LOW);
 shiftOut(data_pin, clock_pin, LSBFIRST, led1);
 shiftOut(data_pin, clock_pin, LSBFIRST, led2);
 digitalWrite(latch_pin, HIGH);
 delay(300);

}
