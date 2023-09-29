// Filename:  Lab9Ex1.c 
// Version:  1.0 
// Date:  <Insert current date> 
// Author: <Insert your name> 
// Purpose: Test ADC library  
 
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
#include "LCDdrive882.h"    // Header file needed to access to LCD custom library 
#include "ADClib882.h"   // Header file for ADC library 
 
#define _XTAL_FREQ 4000000  // MCU clock speed ? required for delay macros 
 
void main(void) { 
    ANSEL = 0x00;   // Set all pins to digital IO mode 
    ANSELH = 0x00;   
    TRISA = 0x00;   // Set all PORTA to outputs (for LEDs) 
    PORTA = 0x00; 
    TRISC = 0x00;   // Set all PORTC to outputs (for LCD) 
    PORTC = 0x00; 
     
    LCD_initialise(); 
    ADC_initialise(); 
     
    while(1) 
    { 
        LCD_cursor(0,0); 
        LCD_putsc("ADC: POT =      "); 
        ADC_channel_select(9); 
        LCD_cursor(11,0); 
        LCD_display_value(ADC_read()); 
        __delay_ms(500); 
    } 
} 
