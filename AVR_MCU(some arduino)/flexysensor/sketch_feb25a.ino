</pre>
#include <Servo.h>
Servo Bas_parmak_sevo, Isaret_parmak_sevo,
Orta_parmak_sevo, Yuzuk_parmak_sevo, Serce_parmak_sevo;
int Bas_parmak_flex_pini = A4;
int Isaret_parmak_flex_pini = A3;
int Orta_parmak_flex_pini = A2;
int Yuzuk_parmak_flex_pini = A1;
int Serce_parmak_flex_pini = A0;
int Bas_parmak_acik_degeri = 514;
int Isaret_parmak_acik_degeri = 665;
int Orta_parmak_acik_degeri = 670;
int Yuzuk_parmak_acik_degeri = 670;
int Serce_parmak_acik_degeri = 531;
int Bas_parmak_kapali_degeri = 840;
int Isaret_parmak_kapali_degeri = 860;
int Orta_parmak_kapali_degeri =825;
int Yuzuk_parmak_kapali_degeri =835;
int Serce_parmak_kapali_degeri =815;
int Bas_parmak_flex =0;
int Isaret_parmak_flex =0;
int Orta_parmak_flex =0;
int Yuzuk_parmak_flex =0;
int Serce_parmak_flex =0;
void setup()
{
Serial.begin(9600);
pinMode(Bas_parmak_flex_pini, INPUT);
pinMode(Isaret_parmak_flex_pini, INPUT);
pinMode(Orta_parmak_flex_pini, INPUT);
pinMode(Yuzuk_parmak_flex_pini, INPUT);
pinMode(Serce_parmak_flex_pini, INPUT);
Bas_parmak_sevo.attach(7);
Isaret_parmak_sevo.attach(6);
Orta_parmak_sevo.attach(5);
Yuzuk_parmak_sevo.attach(4);
Serce_parmak_sevo.attach(3);
}
 
void loop()
{
Bas_parmak_flex = analogRead(Bas_parmak_flex_pini);
 
if( Bas_parmak_flex < Bas_parmak_acik_degeri)
{
Bas_parmak_flex = Bas_parmak_acik_degeri;
}
if( Bas_parmak_flex > Bas_parmak_kapali_degeri)
{
Bas_parmak_flex = Bas_parmak_kapali_degeri;
}
Bas_parmak_flex = map(Bas_parmak_flex ,Bas_parmak_kapali_degeri ,Bas_parmak_acik_degeri ,0,180);
Bas_parmak_sevo.write(Bas_parmak_flex);
 
Isaret_parmak_flex = analogRead(Isaret_parmak_flex_pini);
if( Isaret_parmak_flex < Isaret_parmak_acik_degeri)
{
Isaret_parmak_flex = Isaret_parmak_acik_degeri;
}
if( Isaret_parmak_flex > Isaret_parmak_kapali_degeri)
{
Isaret_parmak_flex = Isaret_parmak_kapali_degeri;
}
Isaret_parmak_flex = map(Isaret_parmak_flex ,Isaret_parmak_kapali_degeri ,Isaret_parmak_acik_degeri ,70,180);
Isaret_parmak_sevo.write(Isaret_parmak_flex);
 
Orta_parmak_flex = analogRead(Orta_parmak_flex_pini);
 
if( Orta_parmak_flex < Orta_parmak_acik_degeri)
{
Orta_parmak_flex = Orta_parmak_acik_degeri;
}
if( Orta_parmak_flex > Orta_parmak_kapali_degeri)
{
Orta_parmak_flex = Orta_parmak_kapali_degeri;
}
 
Orta_parmak_flex = map(Orta_parmak_flex ,Orta_parmak_kapali_degeri ,Orta_parmak_acik_degeri ,0,180);
Orta_parmak_sevo.write(Orta_parmak_flex);
Yuzuk_parmak_flex = analogRead(Yuzuk_parmak_flex_pini);
if( Yuzuk_parmak_flex < Yuzuk_parmak_acik_degeri)
{
Yuzuk_parmak_flex = Yuzuk_parmak_acik_degeri;
}
if( Yuzuk_parmak_flex > Yuzuk_parmak_kapali_degeri)
{
Yuzuk_parmak_flex = Yuzuk_parmak_kapali_degeri;
}
Yuzuk_parmak_flex = map(Yuzuk_parmak_flex,Yuzuk_parmak_kapali_degeri,Yuzuk_parmak_acik_degeri,0,180);
Yuzuk_parmak_sevo.write(Yuzuk_parmak_flex);
Serce_parmak_flex = analogRead(Serce_parmak_flex_pini);
if( Serce_parmak_flex < Serce_parmak_acik_degeri)
{
Serce_parmak_flex = Serce_parmak_acik_degeri;
}
if( Serce_parmak_flex > Serce_parmak_kapali_degeri)
{
Serce_parmak_flex = Serce_parmak_kapali_degeri;
}
Serce_parmak_flex = map(Serce_parmak_flex ,Serce_parmak_kapali_degeri ,Serce_parmak_acik_degeri ,160,0);
Serce_parmak_sevo.write(Serce_parmak_flex);
delay(30);
}
 
&nbsp;
<pre>
