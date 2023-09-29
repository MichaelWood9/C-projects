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
unsigned int sec = 0;
unsigned int running = 0;






void Timer1Delay(unsigned char t){
    count = 0;
    while(1){
        time = t*2;
       TMR1 = 3036;       // Preload  
        while(!PIR1bits.TMR1IF);      // Delay routine ? wait for overflow 
        PIR1bits.TMR1IF = 0;          // Reset overflow flag 
        count++;//increments count
        if (count == 2){//checks if count is 2
            count = 0;
            break;//exits loop
        }
    }
}

void startClock(void){
   
    while(1){
        
        Timer1Delay(1);//calls delay function
        PORTA++;
        if(running == 1){// checks if running is 1
            sec++;//increments sec
            LCD_clear();//clears LCD
            LCD_display_value(sec/60);//displays the mins
            LCD_putch(':');//displays :
            LCD_display_value(sec%60);//displays the seconds
        }
        

        
    }

}



void main(void) 
{ 
    ANSEL = 0x00;   // Set all pins to digital 
  ANSELH = 0x00; 
    TRISA = 0x00;       // Set PORTA all outputs 
    PORTA = 0x00;       // Clear PORTA 
    TRISB = 0x07;               // Set RB0 (SW0) as input
    PORTB = 0x00; 
    T1CON= 0x31;        // Timer 1, internal clock, 1:8 prescaler 
    
    OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
        OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
        OPTION_REGbits.PS = 3;      // Set prescaler bits to 011 for 1:16 
        //Interrupt setup 

        INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
        INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
        IOCBbits.IOCB = 7;          // Enable RBIE on RB0 only  
        INTCONbits.GIE = 1;         // Enable interrupts
    
    
    
    LCD_initialise();//initialised LCD
    
    startClock();//calls the stark clock function 
        
}


void __interrupt() my_ISR(void) 
{ 
    if(INTCONbits.RBIF) 
    { 
        if(PORTBbits.RB0){//checks if RB0 triggered the interrupt
            running = 1;//sets running to 1 to start the stopwatch

            PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition (mismatch)
        }
        else if(PORTBbits.RB1){//checks if RB1 triggered the interrupt
            running = 0;//sets running to 1 to pause the stopwatch
            PORTBbits.RB1 = 0;  // Write PORTB to clear interrupt condition (mismatch)
            
        }
        else if(PORTBbits.RB2){//checks if RB2 triggered the interrupt
            sec = 0;//sets sec to 0 to reset the clock
            running = 0;//sets running t0 0 to stop the clock
            LCD_clear();//clears the LCD
            LCD_putch('0');//displays 0
            LCD_putch(':');
            LCD_putch('0');//displays 0
            PORTBbits.RB2 = 0;  // Write PORTB to clear interrupt condition (mismatch)
        }
        
        PORTB;
        INTCONbits.RBIF = 0;// Clear interrupt flag
        return;
      
    }
    
} 
