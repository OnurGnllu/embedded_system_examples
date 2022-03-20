
//https://github.com/orgicus/Mindwave Link of the library
//    The sketch uses the brains Attention Level for Go/Stop and
//    Eye-blinks for turns.
//
// Hardware: Arduino Uno, HC-05 Bluetooth, NeuroSky MindWave Mobile 2.
// High Attention = green LED on (go); Low Att = green LED off (stop).
// First blink & left turn= yellow LED; Double-blink= red LED (right).
// Info is displayed on the Serial Monitor.
// Right and left turns are for 2 seconds.
//
#include<Servo.h>
#include <Mindwave.h> // Mindwave library from GitHub>orgicus
Mindwave mindwave;
#define YLED 2        // define the LED pins
#define GLED 4
#define RLED 7
Servo myservoG;       // Go/Stop servo
Servo myservoLR;      // Left/Right servo
int gosignal = 0;     // indicator for go or stop
int blinksignal = 0;  // counter for signals after first blink
int blinks = 0;       // number of blinks in a group
unsigned long time;   // variable for elapsed time
unsigned long time0;  // variable for time of first blink
unsigned long time1;  // variable for time from 1st to 2nd blink 

void setup() {
Serial.begin(MINDWAVE_BAUDRATE);
pinMode(13, OUTPUT);   // initialize the LED pins as output
pinMode(GLED, OUTPUT);
pinMode(YLED, OUTPUT);
pinMode(RLED, OUTPUT);
myservoG.attach(9);    // attach the Go/Stop servo on pin 9
myservoG.write(90);    // move the servo to midpoint
myservoLR.attach(10);  // attach the Left/Right servo on pin 10
myservoLR.write(90);   // move the servo to midpoint
delay(15);             // give the servo time to move there
}

void onMindwaveData() {
  if (mindwave.quality() < 90) {  // onboard LED on if poor quality
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }
// Check Attention Level
   if ((mindwave.attention() > 70) && (gosignal == 0)) {
      Serial.print("Go, ");
      Serial.print("\tattention: ");
      Serial.print(mindwave.attention());
      time = millis();
      Serial.print("\ttime: ");
      Serial.print(time);
      Serial.println();
      digitalWrite(GLED, HIGH);  // green LED on
      gosignal = 1;              // indicates going
      myservoG.write(130);       // servo for robot to go forward
      delay(4000);               // go for 4 seconds before checking
                                 // if attention has dropped
   }
  if ((mindwave.attention() < 70) && (gosignal == 1)) {
      Serial.print("Stop, ");
      Serial.print("\tattention: ");
      Serial.print(mindwave.attention());
      time = millis();
      Serial.print("\ttime: ");
      Serial.print(time);
      Serial.println();
      digitalWrite(GLED, LOW);  // green LED off
      gosignal = 0;             // indicates stopped going
      myservoG.write(90);       // servo for robot to stop
      delay(15);
   }
// First blink
   if ((mindwave.quality() < 95) && (blinksignal == 0)) { 
      Serial.print("First blink ");
      Serial.print("\tquality: ");
      Serial.print(mindwave.quality());
      time = millis();
      Serial.print("\ttime: ");
      Serial.print(time);
      Serial.print("\tgosignal: ");
      Serial.print(gosignal);
      Serial.print("\tblinksignal: ");
      Serial.print(blinksignal);
      Serial.println();
      time0 = millis();
      blinks = 1;
      blinksignal = 1;            // first blink
      digitalWrite(YLED, HIGH);   // yellow LED on
   }  
// Display quality right after the blink, & increase the counter
// for signals from the headset
   if ((blinksignal > 0) && (blinksignal < 4)) { 
       Serial.print("\tquality: ");
       Serial.print(mindwave.quality());
       time = millis();
       Serial.print("\ttime: ");
       Serial.print(time);
       Serial.print("\tgosignal: ");
       Serial.print(gosignal);
       Serial.print("\tblinksignal: ");
       Serial.print(blinksignal);
       Serial.println();
     if (blinksignal > 0) {           
       blinksignal = 1 + blinksignal; // increase counter for signals
     }
       time1 = millis() - time0;
   }
// Double-blink?
   if ((mindwave.quality()<95) && (time1 > 1200)){ 
       Serial.print("\tquality: ");
       Serial.print(mindwave.quality());
       time = millis();
       Serial.print("\ttime: ");
       Serial.print(time);
       Serial.print("\tgosignal: ");
       Serial.print(gosignal);
       Serial.print("\tblinksignal: ");
       Serial.print(blinksignal);
       Serial.print("\ttime1: ");
       Serial.print(time1);
       Serial.print("\tblinks now = 2");
       Serial.println();
       blinks = 2;
   }  
// Single blink to turn left
   if ((blinks == 1) && (blinksignal > 3)) {                                 
       Serial.print("Left, ");
       Serial.print("\tSingle blink ");
       time = millis();
       Serial.print("\ttime: ");
       Serial.print(time);
       Serial.print("\tgosignal: ");
       Serial.print(gosignal);
       Serial.print("\tblinksignal: ");
       Serial.print(blinksignal);
       Serial.println();
       blinksignal = 0;            // reset for next blink(s)
//   code for robot to turn wheels left for 2 seconds
       myservoLR.write(55);
       delay(2000);
       digitalWrite(YLED, LOW);   // yellow LED off
//   code for robot to turn wheels from left to straight
       myservoLR.write(90);
       delay(15);
   }
// Double blink to turn right
   if ((blinks == 2) && (blinksignal > 3)) {                                 
       Serial.print("Right, ");
       Serial.print("\tDouble blink ");
       time = millis();
       Serial.print("\ttime: ");
       Serial.print(time);
       Serial.print("\tgosignal: ");
       Serial.print(gosignal);
       Serial.print("\tblinksignal: ");
       Serial.print(blinksignal);
       Serial.println();
       digitalWrite(RLED, HIGH);   // red LED on if right turn
       digitalWrite(YLED, LOW);    // yellow LED off
       blinksignal = 0;            // reset for next blink(s)
//   code for robot to turn wheels right for 2 seconds
       myservoLR.write(120);
       delay(2000);
       digitalWrite(RLED, LOW);    // red LED off
//   code for robot to turn wheels from right to straight
       myservoLR.write(90);
       delay(15);
   }
}
void loop() {
    mindwave.update(Serial, onMindwaveData);
}
