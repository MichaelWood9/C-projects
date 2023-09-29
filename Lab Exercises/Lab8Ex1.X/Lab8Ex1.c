// Filename: Lab8Ex1.c
// Version: 1.0
// Date: <Insert current date>
// Author: <Insert your name>
//
// Description: Implements a Timer1 peripheral interrupt and uses it to
// toggle RB7 at a rate of 2 Hz
// PIC16F882 Configuration Bit Settings
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits
#pragma config WDTE = OFF // Watchdog Timer Enable bit
#pragma config PWRTE = OFF // Power-up Timer Enable bit
#pragma config MCLRE = ON // RE3/MCLR pin function select bit
#pragma config CP = OFF // Code Protection bit
#pragma config CPD = OFF // Data Code Protection bit
#pragma config BOREN = OFF // Brown Out Reset Selection bits
#pragma config IESO = OFF // Internal External Switchover bit
#pragma config FCMEN = OFF // Fail-Safe Clock Monitor Enabled bit
#pragma config LVP = OFF // Low Voltage Programming Enable bit
#pragma config BOR4V = BOR40V // Brown-out Reset Selection bit
#pragma config WRT = OFF // Flash Program Memory Self Write Enable bits
#include <xc.h> // Required for all MPLAB XC8 source files
#define _XTAL_FREQ 4000000
void config(void); // Configuration function
void main(void)
{
    config(); // Call configuration function
    while(1) // Endless loop
    {
            PORTA = PORTA^0x02; // Toggle RA7
            __delay_ms(100);
    }
}
// Function to carry out configuration routines. Is called once at the start of
// execution and helps to keep the main() function clean and tidy.
void config(void)
{
    INTCONbits.GIE = 0; // Disable interrupts during configuration
    ANSEL = 0x00; // All pins as digital outputs
    ANSELH = 0x00;
    TRISA = 0x00; // Configure PORTA
    PORTA = 0x00;
    T1CON = 0x30; // Timer1 OFF, Prescaler 1:8
    T1CONbits.TMR1ON = 0; // Turn Timer 1 OFF
    TMR1 = 3036; // Preload for 500 ms @ Pre=1:8, 4 MHz
    PIE1bits.TMR1IE = 1; // Enable TIMER1 interrupt ONLY
    PIR1bits.TMR1IF = 0; // Clear Timer1 interrupt flag
    INTCONbits.PEIE =1; // Enable PEIE and GIE
    INTCONbits.GIE=1;
    T1CONbits.TMR1ON = 1; // Turn Timer 1 ON
}
// Interrupt service routine (ISR)
void __interrupt() myISR(void)
{
    if(PIR1bits.TMR1IF)
    {
        T1CONbits.TMR1ON = 0; // Turn Timer 1 OFF
        TMR1 = 3036; // Preload for 500 ms @ Pre=1:8, 4 MHz
        T1CONbits.TMR1ON = 1; // Turn Timer 1 ON
        PORTA=PORTA^0x01; // Toggle RA0 led
        PIR1bits.TMR1IF = 0; // Clear interrupt flag (IMPORTANT)
    }
}
