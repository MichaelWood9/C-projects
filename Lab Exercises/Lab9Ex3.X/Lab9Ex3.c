// Filename:  Lab9Ex2.c 
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
 
long mv;
long read;
unsigned short res = 488;
int low = 0;
int high = 0;


void config(void);
void displayadc(void);

void main(void) {
    
    config();//runs config function
    LCD_initialise(); 
    ADC_initialise(); 
    ADC_channel_select(9);
    high = ADC_read();
    low = ADC_read();
    
    displayadc();//runs display adc function

}

void config(void) 
{ 
     ANSEL = 0x00;   // Set all pins to digital IO mode 
    ANSELH = 0x00;   
    TRISA = 0x00;   // Set all PORTA to outputs (for LEDs) 
    PORTA = 0x00;
    TRISB = 0x03;               
    PORTB = 0x00; 
    T1CON = 0x31;        
    TRISC = 0x00;   // Set all PORTC to outputs (for LCD) 
    PORTC = 0x00; 
    
        OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
        OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
        OPTION_REGbits.PS = 3;      // Set prescaler bits to 011 for 1:16 
        
        //Interrupt setup 
        INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
        INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
        IOCBbits.IOCB = 3;          // Enable RBIE on RB0,RB1
        INTCONbits.GIE = 1;         // Enable interrupts   

}

void displayadc(void){
        while(1) 
    { 
        LCD_cursor(0,0);//puts the cursor at the start of the top line 
         
        ADC_channel_select(9); //selects the ADC channel
        read = ADC_read();//reads the ADC and sets it as a varable 
        mv = read*res/100; //calulates POT in MV
        
        LCD_display_value (mv); //displays the POT in MV
        
        if(read > high){
            high = read;//set high to read
        
        }
        if(read < low){
            low = read;//sets low to read
         
        }
        LCD_cursor(0,1);
        LCD_display_value(high);// displays the highest POT since start.
        LCD_cursor(9,1);
        LCD_display_value(low);// displays the lowest POT since start.
        __delay_ms(1000); // 1000 ms delay
    } 
}

void __interrupt() my_ISR(void) 
{ 
    if(INTCONbits.RBIF) 
    { 
        if(PORTBbits.RB0){//checks to see id SWO caused the intterupt
            low = ADC_read();//sets low to current POT value

            PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition 
        }
        else if(PORTBbits.RB1){//checks to see id SW1 caused the intterupt
            high = ADC_read();//sets high to current POT value
            PORTBbits.RB1 = 0;// Write PORTB to clear interrupt condition 
        }
        INTCONbits.RBIF = 0;// Clear interrupt flag
        return;
      
    }
    
} 