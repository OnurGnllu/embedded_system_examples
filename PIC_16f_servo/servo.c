#include <16f877.h>
#use delay(clock=4000000)
#fuses XT,NOWDT,NOPUT,NOLVP,NOCPD,NOPROTECT,NODEBUG,NOBROWNOUT,NOWRT

#use fast_io(b)

int sayac=0,duty=0,adim=0;
const int deger[]={4,5,6,7,8,9,10};

int16 gecikme=0;

#int_timer0
void kesme(){
set_timer0(231);
if(sayac==0)
output_high(pin_b0);

if(sayac>=duty)
output_low(pin_b0);
sayac++;
if(sayac==100)
sayac=0;

gecikme++;
if(gecikme>10000){
gecikme=0;
adim++;
if(adim==6)
adim=0;
}

}


void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   set_tris_b(0x00);
   
   setup_timer_0(RTCC_INTERNAL | RTCC_DIV_8);
   set_timer0(231);
   
   enable_interrupts(INT_timer0);
   enable_interrupts(GLOBAL);
   
   while(true){
   
   duty=deger[adim];
   
   }
   


}






