// Filename:  Lab2Ex1.c 
// Version:  1.0 
// Date:    <19/02/2022> 
// Author:   <Michael Wood> 
// 
// Description: A simple program to produce a repeating sequence on PORTB on a 
// PIC16F882 
 
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
 
void main(void) 
{ 
    ANSEL = 0x00;       // Set all analogue pins to digital mode 
    ANSELH = 0x00; 
    TRISA=0x00;          // Make all of PORTB output 
    PORTA = 0x00;   // Clear PORT A (known state) 
while(1) 
    { 
        PORTA=0xf0;           // Turn ms nibble on 
        __delay_ms(700);   // Wait 200 msecs 
        PORTA=0x0f;           // Turn ls nibble on 
        __delay_ms(300);       // Wait 200 msecs 
    } 
} 
