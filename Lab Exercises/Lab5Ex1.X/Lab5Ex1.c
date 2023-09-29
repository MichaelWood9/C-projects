// Filename:  Lab5Ex1.c 
// Version:  1.0 
// Date:    <Insert current date> 
// Author:   <Insert your name> 
// 
// Description: Looping of a short timer delay to create a longer one  
 
// PIC16F882 Configuration Bit Settings 
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits  
#pragma config WDTE = OFF       // Watchdog Timer Enable bit  
#pragma config PWRTE = OFF      // Power?up Timer Enable bit  
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit  
#pragma config CP = OFF         // Code Protection bit  
#pragma config CPD = OFF        // Data Code Protection bit 
#pragma config BOREN = OFF      // Brown Out Reset Selection bits 
#pragma config IESO = OFF       // Internal External Switchover bit 
#pragma config FCMEN = OFF      // Fail?Safe Clock Monitor Enabled bit 
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 
#pragma config BOR4V = BOR40V   // Brown?out Reset Selection bit 
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
 
#include <xc.h>             // Required by compiler, PIC specific definitions 
 
void main(void) 
{ 
    ANSEL = 0x00;     // Set all pins to digital 
  ANSELH = 0x00; 
    TRISA = 0x00;               // Set PORTA all outputs 
    PORTA = 0x00;               // Clear PORTA 
    //Timer0 setup 
    OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
    OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
    OPTION_REGbits.PS = 3;      // Set prescaler bits to 011 for 1:16 
    //Interrupt setup 
    INTCONbits.T0IE = 1;        // Enable Timer0 overflow interrupt 
    INTCONbits.T0IF = 0;        // Clear Timer0 overflow interrupt 
    INTCONbits.GIE = 1;         // Enasble interrupts 
     
    while(1);                   // Infinite do?nothing loop 
} 
 
void __interrupt() my_ISR(void) 
{ 
    // Declare a count variable. The static type ensures the variable remains  
    // in memory between subsequent functions calls. Ordinarily, a volatile 
    // variable would be destroyed on return.     
     
    static unsigned short count = 0;  
     
    if(INTCONbits.T0IF) // Check if interrupt has occurred 
    { 
        TMR0 = 131;     // Preload Timer 0 
        count++;        // Increment count variable 
        if (count == 500) // If x counts have been reached, execute background task 
  
        { 
            PORTA++;    // Background task 
            count = 0;  // Reset counter for next time 
        } 
        INTCONbits.T0IF = 0;    // Reset interrupt flag 
        return; 
    } 
}
