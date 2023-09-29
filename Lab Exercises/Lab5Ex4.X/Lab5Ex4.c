// Filename:  Lab5Ex4.c 
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
#include "LCDdrive882.h"    // Header file needed to access to LCD custom library

char firstName[]={"Michael"};//creates a string
unsigned int display_name = 1;
 
void main(void) 
{ 
    //GPIO setup 
    ANSEL = 0x00;     // Set all pins to digital 
  ANSELH = 0x00; 
    TRISA = 0x00;               // Set PORTA all outputs 
    PORTA = 0x00;               // Clear PORTA 
    TRISB = 0x03;               // Set RB0 (SW0) as input 
    PORTB = 0x00; 
    //Timer0 setup 
    OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
    OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
    OPTION_REGbits.PS = 3;      // Set prescaler bits to 011 for 1:16 
    //Interrupt setup 
    INTCONbits.T0IE = 1;
    INTCONbits.T0IF=  0;
    INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
    INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
    IOCBbits.IOCB = 3;          // Enable RBIE on RB0 only  
    INTCONbits.GIE = 1;         // Enable interrupts 
    while(1){ 
        LCD_initialise();
        
        if(display_name == 1){//only execute if display name = 1
            LCD_puts(firstName);//displays name on LCD
            display_name = 0;//sets display_name to 0
        }
    
    }
     
     
} 
 
void __interrupt() my_ISR(void) 
{ 
  static unsigned short count = 0;
    if(INTCONbits.RBIF) 
    { 
        if(PORTBbits.RB0){
          PORTA++;//increments PORTA(LEDS)
          PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition  
          
        }
        if(PORTBbits.RB1){
           PORTA--; //decreases PORTA(LEDS)
           PORTBbits.RB1 = 0;  // Write PORTB to clear interrupt condition (mismatch) 
          
        }
        
    INTCONbits.RBIF = 0;// Clear interrupt flag
    
    }
    
   if(INTCONbits.T0IF) // Check if interrupt has occurred 
    { 
        TMR0 = 131;     // Preload Timer 0 
        count++;        // Increment count variable 
        if (count == 200) // If x counts have been reached, execute background task 
        { 
            LCD_clear();//clears LCD
            display_name = 1;//sets display_name to 1
            count = 0;  // Reset counter for next time 
        } 
        INTCONbits.T0IF = 0;    // Reset interrupt floag 
        return; 
    } 
    
}
