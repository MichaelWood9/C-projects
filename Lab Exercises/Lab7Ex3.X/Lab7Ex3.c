// Filename: Lab7Ex3.c 
// Version: 1.0 
// Date:  <Insert current date> 
// Author:  <Insert your name> 
 
// Description: Implementing a Timer2 delay  
 
#include <xc.h>             // Required for all MPLAB XC8 source files 
unsigned int count; 

void Timer2_delayms(unsigned int time){
    while(1){
        while(!PIR1bits.TMR2IF);    // Delay
        PIR1bits.TMR2IF = 0;//clears interrupt flag
        count++;//increments count
        if(count == time){// check to see if count is equal to time.
            count = 0;
            break;//breaks loop
        }
    }
}

void main(void) 
{ 
 ANSEL = 0x00;    // All pins to digital mode 
 ANSELH = 0x00; 
 TRISA = 0x00;   // Configure PORTA 
 PORTA = 0x00; 
 PR2 = 5.25; 
 TMR2 = 0;   // Clear Timer2 (known state) 
 T2CON = 0x4E;   // Timer2 ON, Prescaler 1:16, Postscaler 1:10 
     
             
    while(1) 
    { 
        Timer2_delayms(100);//delay function call 
        PORTA++;   // increment PORTA      
                
    } 
}
