// Filename:  Lab6Ex1.c 
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
int count = 0;
int time = 0;

void Timer1Delay(unsigned char t){
    count = 0;
    while(1){
        time = t*2;
       TMR1 = 3036;       // Preload  
        while(!PIR1bits.TMR1IF);      // Delay routine ? wait for overflow 
        PIR1bits.TMR1IF = 0;          // Reset overflow flag 
        count++;// Increment count
        if (count == 2){//checks to see if count = 2
            count = 0;//sets count to 0
            PORTA++;                      // Increment PORTA
        }
    }
}

void main(void) 
{ 
    ANSEL = 0x00;   // Set all pins to digital 
  ANSELH = 0x00; 
    TRISA = 0x00;       // Set PORTA all outputs 
    PORTA = 0x00;       // Clear PORTA 
    T1CON= 0x31;        // Timer 1, internal clock, 1:8 prescaler   
    
    Timer1Delay(5);
 
}

