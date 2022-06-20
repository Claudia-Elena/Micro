#include "LCD.h"

#define NOKEY 0x7F

#define FMSG   0
#define WAIT   1
#define RING   2
#define OPEN   3
#define COD1   4
#define COD2   5
#define COD3   6
#define ERR    7

char kbscan();

int main(){

   char code_now= NOKEY, code_ante;
   unsigned char kbhit=0;
   char kbcode;
   
   unsigned char loop_cnt=0;
   
   int cod = 123; //sau char cod[4]="123";
   char buf[4];
   char stare = FMSG;
      
   initLCD();
   PORTA = 0;
   
   while (1){
      //determina daca este tasta apasata
      if(loop_cnt==100){
         code_ante=code_now;
         code_now = kbscan();
         if(code_now!=NOKEY && code_ante==NOKEY){
            kbhit=1;
            kbcode=code_now;
         }
         loop_cnt=0;
      }
      
      //SFSM
      switch (stare){
         case FMSG:
            clrLCD();
            putsLCD("Suna la 1..8,");
            gotoLC(2,1);
            putsLCD("C pentru cod:");
            stare = WAIT;
            break;
         
         case WAIT:
            if(kbhit){
               kbhit=0;
               if ('C'==kbcode){
                  clrLCD();
                  putsLCD("Cod=");
                  stare = COD1;
               }
               if (kbcode>='1' && kbcode <= '8'){
                  clrLCD();
                  putsLCD("Sun la ");
                  putchLCD(kbcode);                  
                  stare = RING;
               }
            }               
            break;
            
         case RING:            
            ..................
            break;
            
         case COD1:
            if(kbhit){
               kbhit=0;
               if (kbcode>='0' && kbcode <= '9'){
                  buf[0]=kbcode;
                  putchLCD('*');
                  stare = COD2;               
               }
               else{
                  stare = FMSG;
               }
            }
            break;
            
         case COD2: 
            ..................
            break;
            
         case COD3: 
            ..................
            break;
            
         case OPEN: 
            ..................
            break;
            
         case ERR: 
            //asteapta  5 secunde
            stare = FMSG;
            break;
            
      }//end switch
      loop_cnt++;
 }//end while
}//end main


// adauga aici codul functiei char kbscan()
