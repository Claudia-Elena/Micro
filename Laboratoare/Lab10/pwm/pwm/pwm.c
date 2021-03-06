#include "LCD.h"
#include <stdlib.h>

#define NOKEY 0x7F
char kbscan();

int main(){
   unsigned char code_now = NOKEY, code_ante;
   unsigned char kbhit=0, kbcode=NOKEY, loop_cnt=0;
   int lumi=50;  //luminozitatea
   char buf_lumi[10];

   initLCD();

   //initializari pentru timer0 - fast PWM

   //       ---------- Fast PWM  
   //       |  | 
   TCCR0=0b01101100;
   //        || |||
   //        ||  -----p=256
   //        --------- OC0 clear on compare match, set at bottom (non-inverting mode)

   OCR0=128;
   //seteaza OC0 ca iesire
   setbit(DDRB, 3);
   gotoLC(1, 1);
   putsLCD("Astept     ");
         
   while(1){
      if(loop_cnt==200){
         code_ante=code_now;
         code_now = kbscan();
         if(code_now != NOKEY && code_ante == NOKEY){
            kbhit=1;
            kbcode=code_now;
         }
         loop_cnt=0;
      }
      loop_cnt++;
  
      //PWM start
      if(kbhit  && (kbcode == 'C' || kbcode == 'D')){
		 kbhit=0;
         if(kbcode == 'C'){
            lumi=lumi+5;//...creste luminozitatea cu 5%
            //...
            if(lumi>100){
               lumi=100;
            }
         }
         if(kbcode == 'D'){
            lumi=lumi-5;//...scade luminozitatea cu 5%
            //...
            if(lumi<0){
               lumi=0;
            }
         }
		 
		   OCR0 = lumi*255/100-1; //......
		   
         itoa(lumi,buf_lumi,10);
         gotoLC(2,1);
         putsLCD("L=");
         putsLCD(buf_lumi);
         putsLCD("%  " );
      }
      //PWM end
     
	  //simulare calcul de durata 
      if( kbhit && kbcode>='0' && kbcode<='9'){
         //kbhit=0;
         //scrie "Calculez..." de la pozitia 1, 1
         gotoLC(1,1);
         putsLCD("Calculez    "); 
         _delay_ms(5000);
         //scrie "Astept     " de la pozitia 1, 1  
         gotoLC(1,1);
         putsLCD("Astept    "); 
      }
       // end calcul
	   kbhit=0;
      
   }//end while
}//end main

char kbscan(){
   char tabela_trans[]="123A456B789C*0#D";

   unsigned char cols=0;
   unsigned char temp;
   volatile unsigned char La; //linia activa
   volatile unsigned char Ca; //coloana activa
   unsigned char cod_intern;
   char cod_extern;

   for(DDRA=0x10;DDRA>0;DDRA<<=1) {
      _delay_us(4);
      cols=~PINA;
      cols=cols&0x0f;
      if(cols!=0)
      break;
   }
   if(DDRA==0)
   return NOKEY;

   temp=DDRA;
   for(La=0;temp!=0x10;temp>>=1)
   La++;

   for(Ca=0;cols!=1;cols>>=1)
   Ca++;

   cod_intern=La*4+Ca;
   cod_extern=tabela_trans[cod_intern];
   return cod_extern;
}
