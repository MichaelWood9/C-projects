// Filename:  Lab5Ex3.c 
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
    INTCONbits.INTE = 1;
    INTCONbits.INTF = 0;
    INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
    INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
    IOCBbits.IOCB = 3;          // Enable RBIE on RB0 only  
    INTCONbits.GIE = 1;         // Enable interrupts 
     
    while(1);                   // Infinite loop                   
} 
 
void __interrupt() my_ISR(void) 
{ 
    if(INTCONbits.RBIF) 
    { 
        if(PORTBbits.RB0){
          PORTA++;//increments PORTA(LEDS)
          PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition  
          
        }
        if(PORTBbits.RB1){
           PORTA--; //decreases PORTA(LEDS)
           PORTBbits.RB1 = 0;  // Write PORTB to clear interrupt condition 
          
        }
        
    INTCONbits.RBIF = 0;// Clear interrupt flag
    
    }
    
} 
