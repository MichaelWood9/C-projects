// Filename: 	Lab2Ex1.c 
// Version: 	1.0 
// Date:  	<Insert current date> 
// Author:  	<Insert your name> 
// 
// Description: A simple program to produce a repeating sequence on PORTB on a 
// PIC16F882 
 
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits  
#pragma config WDTE = OFF       // Watchdog Timer Enable bit  #pragma config PWRTE = OFF      // Power?up Timer Enable bit  
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit  
#pragma config CP = OFF         // Code Protection bit  
#pragma config CPD = OFF        // Data Code Protection bit 
#pragma config BOREN = OFF      // Brown Out Reset Selection bits 
#pragma config IESO = OFF       // Internal External Switchover bit 
#pragma config FCMEN = OFF      // Fail?Safe Clock Monitor Enabled bit 
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 
#pragma config BOR4V = BOR40V   // Brown?out Reset Selection bit 
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
 
#include <xc.h>             // Required by compiler, PIC specific definitions #define _XTAL_FREQ 4000000  // MCU clock speed ? required for delay macros  
void main (void) 
{  	
    ANSEL = 0x00;        ANSELH = 0x00; 	// Set all analogue pins to digital mode 
    TRISA = 0x00;    	// Make all of PORTA output (LEDs) 
    PORTA = 0x00;  	// Clear PORT A (known state)TRISD=0x01;  	 
    TRISB = 0x01;    	// Make all of PORTB output except RB0 (SW0) 
    PORTB = 0x00;  
     
    while(1) 
    { 	// Clear PORTB (known state) TRISD=0x01;  	 
        if (PORTBbits.RB0==1)      // Is SW0 high?  
            PORTA=0xAA;  // Light alternate PORTA LEDs: 0xAA = 0b10101010         
        else 
            PORTA=0x55;  // Invert the PORTA LED pattern: 0x55 = 0b01010101  
    } 
}  

