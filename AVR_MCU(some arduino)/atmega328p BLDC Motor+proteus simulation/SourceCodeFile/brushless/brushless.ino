const int trigger=2;
const int HA=8;
const int LA=9;
const int HB=10;
const int LB=11;
const int HC=12;
const int LC=13;
const int pwmPin=3;
const int pwmOut=6;
int speedPwm=0;

int hallA=0;
int hallB=0;
int hallC=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(HA,OUTPUT);
  pinMode(LA,OUTPUT);
  pinMode(HB,OUTPUT);
  pinMode(LB,OUTPUT);
  pinMode(HC,OUTPUT);
  pinMode(LC,OUTPUT);
  speedPwm=analogRead(pwmPin);
  analogWrite(pwmOut,speedPwm);
  startJump();
attachInterrupt(digitalPinToInterrupt(trigger),triggerFase,CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
 
}

void triggerFase(){
 hallA=analogRead(0);
  hallB=analogRead(1);
  hallC=analogRead(2);
  speedPwm=analogRead(pwmPin);
  analogWrite(pwmOut,speedPwm);
//step1
  if(hallA>0 && hallB==0 && hallC>0){
    digitalWrite(HA,LOW);
    digitalWrite(LA,LOW);
    digitalWrite(HB,LOW);
    digitalWrite(LB,HIGH);
    digitalWrite(HC,HIGH);
    digitalWrite(LC,LOW);
    
  }
  //step 2
  if(hallA>0 && hallB==0 && hallC==0){
    digitalWrite(HA,HIGH);
    digitalWrite(LA,LOW);
    digitalWrite(HB,LOW);
    digitalWrite(LB,HIGH);
    digitalWrite(HC,LOW);
    digitalWrite(LC,LOW);
  }
  //step 3
  if(hallA>0 && hallB>0 && hallC==0){
   digitalWrite(HA,HIGH);
    digitalWrite(LA,LOW);
    digitalWrite(HB,LOW);
    digitalWrite(LB,LOW);
    digitalWrite(HC,LOW);
    digitalWrite(LC,HIGH);
  }
  //step4
  if(hallA==0 && hallB>0 && hallC==0){
    digitalWrite(HA,LOW);
    digitalWrite(LA,LOW);
    digitalWrite(HB,HIGH);
    digitalWrite(LB,LOW);
    digitalWrite(HC,LOW);
    digitalWrite(LC,HIGH);
  }
  //step5
  if(hallA==0 && hallB>0 && hallC>0){
   digitalWrite(HA,LOW);
    digitalWrite(LA,HIGH);
    digitalWrite(HB,LOW);
    digitalWrite(LB,LOW);
    digitalWrite(HC,HIGH);
    digitalWrite(LC,LOW);
  }
  //step6
  if(hallA==0 && hallB==0 && hallC>0){
    digitalWrite(HA,LOW);
    digitalWrite(LA,HIGH);
    digitalWrite(HB,LOW);
    digitalWrite(LB,LOW);
    digitalWrite(HC,HIGH);
    digitalWrite(LC,LOW);
  }
}

void startJump(){
    digitalWrite(HA,LOW);
    digitalWrite(LA,LOW);
    digitalWrite(HB,LOW);
    digitalWrite(LB,HIGH);
    digitalWrite(HC,HIGH);
    digitalWrite(LC,LOW);
}


