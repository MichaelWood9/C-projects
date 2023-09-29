// Filename:  Lab4Ex4.c 
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
#define _XTAL_FREQ 4000000  // MCU clock speed ? required for delay macros 
 
void one_sec_delay (void);  // Function prototype 

void delay(unsigned short delay_length) 
{ 
    unsigned char preload = 131;     // TMR0 preload variable (derived from Ex2) 
    unsigned short i; // Loop index variable
    unsigned short x = 500*delay_length; //number of loops need to create specfic delay
 
    
   
    
     
    //Timer0 setup 
    OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
    OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
    OPTION_REGbits.PS = 3;      // Set prescaler bits to 111 for 1:256 
     
    for(i=0;i<x;i++)       // Loop to cascade several short delays together 
                            // Number of loops derived from Ex2 
    { 
        TMR0 = preload;             // Preload timer0 
        while(!INTCONbits.TMR0IF);    // Delay loop: Wait until TMR0 overflows 
        INTCONbits.TMR0IF = 0;        // Reset overflow flag, TMR0IF 
    }     
} 
 
void main(void) 
{ 
    // PORTA setup 
    ANSEL = 0x00;     //Set all pins to digital mode 
    ANSELH = 0x00; 
    TRISA = 0x00;               // Set PORTA all outputs 
    PORTA = 0x00;               // Clear PORTA 
     
    while(1)                    // Infinite loop 
    {    
        delay(2);        // Call delay function 
        PORTA++;                // Increment PORTA     
    } 
} 
 

