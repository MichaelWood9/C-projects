// Filename: Lab7Ex1.c 
// Version: 1.0 
// Date:  <Insert current date> 
// Author:  <Insert your name> 
 
// Description: Implementing a Timer2 delay  
 
#include <xc.h>             // Required for all MPLAB XC8 source files 
 
void main(void) 
{ 
 ANSEL = 0x00;    // All pins to digital mode 
 ANSELH = 0x00; 
 TRISA = 0x00;   // Configure PORTA 
 PORTA = 0x00; 
 PR2 = 124; 
 TMR2 = 0;   // Clear Timer2 (known state) 
 T2CON = 0x4E;   // Timer2 ON, Prescaler 1:16, Postscaler 1:10 
     
             
    while(1) 
    { 
        while(!PIR1bits.TMR2IF);    // Delay 
        PORTA++; //increments PORTA        
        PIR1bits.TMR2IF = 0;        // Clear overflow flag 
    } 
}