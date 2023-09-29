// File:   main.c, Author: H. Martin, Created: 12/1/22 
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
 
void main(void) { 
 
    // Configure GPIO ports 
    TRISA = 0x00;   // Set all PORTA to outputs (for LEDs) 
    ANSEL = 0x00;   // Set all PORTA to digital IO mode 
    PORTA = 0x00; 
    TRISB = 0x07;   // Set RB0-2 as inputs (for pushbuttons) 
    PORTB = 0x00; 
    ANSELH = 0x00;  // Set all PORTB to digital IO mode 
     
    while (1)    // Infinite (endless) loop 
    { 
        if (RB0==1)  // Has SW0 switch on PORTD been pressed? 
        { 
            PORTA=0xff; // Turn all PORTB LEDs ON 
        } 
        else  
        { 
            PORTA=0x00; // Otherwise switch all PORTB LEDs OFF 
           
        } 
    }           
}
