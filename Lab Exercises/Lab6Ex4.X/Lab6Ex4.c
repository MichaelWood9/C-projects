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
#include "LCDdrive882.h"    // Header file needed to access to LCD custom library
#define _XTAL_FREQ 4000000

unsigned int count = 0;
unsigned int time = 0;
unsigned int secs = 0;
unsigned int mins = 0;




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
            break;    //exits loop
        }
    }
}



void main(void) 
{ 
    ANSEL = 0x00;   // Set all pins to digital 
  ANSELH = 0x00; 
    TRISA = 0x00;       // Set PORTA all outputs 
    PORTA = 0x00;       // Clear PORTA 
    TRISB = 0x03;               // Set RB0 (SW0) as input
    PORTB = 0x00; 
    T1CON= 0x31;        // Timer 1, internal clock, 1:8 prescaler 
    
    OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
        OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
        OPTION_REGbits.PS = 3;      // Set prescaler bits to 011 for 1:16 
        //Interrupt setup 
        INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
        INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
        IOCBbits.IOCB = 1;          // Enable RBIE on RB0 only  
        INTCONbits.GIE = 1;         // Enable interrupts
    
    
    
    LCD_initialise();
    
    while(1){
        Timer1Delay(1);
        secs++;//increments secs
            if(secs%60==0){ //checks if 60 secs have passed
                mins++;//increments mins
                secs = 0;//sets secs to 0
            }
            
        LCD_clear();
        LCD_display_value(mins);//displays mins on LCD
        LCD_putch(':');
        LCD_display_value(secs);//displays secs on LCD
        
        }
    }
        
        
        
    
    
    


void __interrupt() my_ISR(void) 
{ 
    
    if(INTCONbits.RBIF) //checks for RBIF interrupt
    { 
        secs = 0;//sets secs to 0
        mins = 0;//sets mins to 0
    }
    PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition (mismatch) 
    INTCONbits.RBIF = 0;// Clear interrupt flag
        return;

} 


