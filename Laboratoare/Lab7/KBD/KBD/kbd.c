
#include <avr/io.h>
#include "LCD.h"
#define NOKEY 0x7f
#define DELAY 200

char kbscan(){
   unsigned char temp = 0;
   unsigned char cols = 0;
   
   unsigned char lina = 0; //linia activa
   unsigned char cola = 0; //coloana activa
   
   unsigned char cod_intern;
   char cod_extern;
   char tabela_trans[] = "123A456B789C*0#D";
   
   for( DDRA = 1<<4; DDRA !=0 ; DDRA<<=1 ) {
      _delay_us(4);
      cols =~ PINA;
      cols = cols & 0b00001111; //mascam bitii 7:4 la 0
      
      if(cols !=0)  //dac? cols con?ine cel pu?in un ‚1’ înseamn? c? s-a ie?it prin P4=>vom continua cu pasul P7.
      {
         break;
      }
      
   } 
   
   if (cols == 0)// caz contrar nu este nici o tast? ap?sat? ?i vom termina func?ia cu return NOKEY
   {
      return NOKEY;
   }
   
   temp = DDRA;
   
   while((temp & 1<<4)==0)//calculam num?rul liniei active
   {
      lina++;
      temp >>=1;
   }
   
   while(cols!=0b00000001)//calculam num?rul coloanei active
   {
      cola++;
      cols>>=1;
   }
   
 
   
   cod_intern = lina * 4 + cola;//cod intern
   cod_extern = tabela_trans[cod_intern];//cod extern
   return cod_extern;
}        //end kbscan
      
//int main(){
   //initLCD();
   //unsigned char temp;
   //while(1){
      //temp=kbscan();
      //if(NOKEY != temp){
         //clrLCD();
         //putchLCD(temp);
      //}
   //}//
//}

int main(){
   
   initLCD();
   
   char code_ante = NOKEY;
   char code_now = NOKEY;
   unsigned char kbhit = 0;
   char kbcode;
   unsigned char loop_cnt=0;
   //initializare LCD, kbd, etc.
   while(1){ //bucla principala
      //…
      if(loop_cnt==DELAY){ //citirile se fac din 15 ms in 15 ms
         loop_cnt=0;
         code_ante = code_now;
         code_now = kbscan();
         if( code_ante == NOKEY && code_now != NOKEY){
            kbhit=1;
            kbcode=code_now;
            
         }
      }
      //……
      //consuma codul
      if(kbhit){
         kbhit=0;
         //prelucreaza kbcode; de exemplu afi?eaza-l
          putchLCD(kbcode);
      }
      //……
      loop_cnt++;
   } //end while
} //end main

