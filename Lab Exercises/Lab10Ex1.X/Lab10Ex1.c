// Filename: Lab10Ex1.c 
// Version: 1.0 
// Date: <Insert current date> 
// Author: <Insert your name> 
// Purpose: Demonstrates PWM generation on pin RC2 using CCP1 module 
 
// PIC16F882 Configuration Bit Settings 
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits  
#pragma config WDTE = OFF       // Watchdog Timer Enable bit  
#pragma config PWRTE = OFF      // Power-up Timer Enable bit  
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit  
#pragma config CP = OFF         // Code Protection bit  
#pragma config CPD = OFF        // Data Code Protection bit 
#pragma config BOREN = OFF      // Brown Out Reset Selection bits 
#pragma config IESO = OFF       // Internal External Switchover bit 
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit 
#pragma config LVP = OFF        // Low Voltage Programming Enable bit 
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit 
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits 
 
#include <xc.h>             // Required by compiler, PIC specific definitions 
#define _XTAL_FREQ 4000000  // MCU clock speed - required for delay macros 
 
void main(void)      
 { 
   TRISC = 0x00;  // Set PORTC as output 
   PORTC = 0x00;  // Clear PORTC 
      
   PR2 = 0x63;  // Set PWM period 
   T2CON = 0x04;        // Prescaler= 1:1, Timer 2 ON 
   CCP2CON = 0x0C; // PWM mode selected. Duty cycle LSBs are not used. 
                        // 8 bit PWM resolution available 
   CCPR2L = 0x00;  // Set duty cycle to 0 
    
   while(1) 
    { 
      __delay_ms(50);  // Short delay  
   CCPR2L++;           // Change PWM duty cycle 
    }       
} 
