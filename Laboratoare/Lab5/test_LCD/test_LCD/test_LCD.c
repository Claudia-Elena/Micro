#include "LCD.h"
#include <avr/io.h>

int main(){
   
   initLCD();

   while(1){
   //scrie caracter
   putchLCD('H');
   _delay_ms(1000);
   //sterge display
   clrLCD();
   _delay_ms(500);
   
   //Afiseaza mesajul „Hello micro!”
   putsLCD("Hello");
   gotoLC(2, 7);
   putsLCD("micro!");
   _delay_ms(1000);
   clrLCD();
   _delay_ms(500);
   
   //Pasul 5
   // Din linia 1, coloana 1 scrie caracter cu caracter textul 0123456789abcdef.
   char text[] = "0123456789abcdef";
   gotoLC(1, 1);
   for(int i = 0; i < 16; ++i){
      putchLCD(text[i]);
      gotoLC(1, i + 2);
      _delay_ms(500);
   }
    // Din linia 2, coloana 1 scrie mesajul „ghijklmnopqrstuv”
    gotoLC(2, 1);
    putsLCD("ghijklmnopqrstuv");
    
    // Muta cursorul pe linia 2, coloana 16.
    gotoLC(2, 16);
    
    // Muta cursorul catre stanga caracter cu caracter pana pe linia 2, coloana 1.
    for(int i = 16; i > 0; --i){
       gotoLC(2, i);
       _delay_ms(500);
    }
    
    // Muta cursorul pe linia 1, coloana 16.
    gotoLC(1, 16);
    
    // Muta cursorul catre stânga caracter cu caracter pana pe linia 1, coloana 1.
    for(int i = 16; i > 0; --i){
       gotoLC(1, i);
       _delay_ms(500);
    }
    
    // Asteapta 0.5 secunde
    _delay_ms(500);
    
    // Sterge LCD    clrLCD();
   }
}

