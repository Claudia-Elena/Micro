#include "LCD.h"
#include <avr/io.h>
#include <stdlib.h>

int main(){
   
   long val;
   char buf[20];
   initLCD();
   // ADMUX register
   //REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
   // |      |     |     0    0   0    0    0    Vin = ADC0
   // |      |     1   aliniere la stânga
   // 0      1    VREF = AVCC
   ADMUX =0b01100000;
   
   // ADCSRA register.
   // ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
   // |      |    |    |     |    1     1     1    factor divizare=128
   // |      |    0    |     0    ADIE si ADATE se seteazã la ‚0’ si nu se mai modifica
   // |      |         0
   // |      0         0
   // 1   enable ADC
   ADCSRA = 0b10000111;
   
   while(1){
      // daca ADC este în repaus adica nu exista conversie în curs
      if( testbit(ADCSRA , ADSC) == 0 && testbit(ADCSRA , ADIF) == 0)  {
         setbit(ADCSRA, ADSC);   //start conversie
      }
      //daca s-a terminat conversia
      if( testbit(ADCSRA , ADSC) == 0 && testbit(ADCSRA , ADIF)) {
         //sterge bitul care indica sfârsitul conversiei
         clrbit(ADCSRA , ADIF);
         //citeste rezultatul conversiei din portul de date conform setãrii ADLAR
         val=ADCH;   //din ce port?
         
        //int valS=val / 100 % 10;
        //int valZ=val / 10 % 10;
        //int valU=val %10;
        //buf[0]='0' + valS;
        //buf[1]='0' + valZ;
        //buf[2]='0' + valU;
        //buf[3]='\0';
        //gotoLC(1, 1);
        //putsLCD(buf);
        long val2;
        val2=(5*val*100UL)/255;
        int valS=val2 / 100 % 10;
        int valZ=val2 / 10 % 10;
        int valU=val2 %10;
        gotoLC(1,1);
        putsLCD("V= ");
        putchLCD(valS+'0');
        putchLCD('.');
        putchLCD(valZ+'0');
        putchLCD(valU+'0');
      }
   }
}
