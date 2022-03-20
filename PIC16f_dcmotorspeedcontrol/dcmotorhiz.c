#include <16f877.h>
#device adc=8 //2^8-1 =255;
#use delay(clock=4000000)
#fuses XT,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(a)
#use fast_io(b)
#use fast_io(c)

#define use_portb_lcd TRUE
#include <lcd.c>

unsigned int deger;
float voltaj;

void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_4,255,1);

   
   setup_CCP1(CCP_PWM);
   setup_CCP2(CCP_OFF);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(ALL_ANALOG);
  
   set_tris_a(0x20); //a4 ü input giriþ yaptýk
   set_tris_b(0x00); //b portlarýnýn hepsi output
   set_tris_c(0x00); //c portlarýnýn hepsi output
   
   
   
   set_adc_channel(4); //a4ten adc baslattýk
   delay_us(20);
   
   output_c(0x00);
   lcd_init();
   printf(lcd_putc,"\fDC Motor\nHiz Kontrolu");
   delay_ms(1000);
   
   set_pwm1_duty(0);
   
   while(true){
   
   deger=read_adc();
   delay_us(20);
   voltaj=deger/51.0;
  

   
   output_high(pin_c3);
   output_low(pin_c4);
   
   set_pwm1_duty(deger);
   
   printf(lcd_putc,"\fVoltaj=%f V",voltaj);
   lcd_gotoxy(1,2);
   printf(lcd_putc,"Deger=%u",deger);
   delay_ms(1000);

   
   }
   
   
   
   }
   










