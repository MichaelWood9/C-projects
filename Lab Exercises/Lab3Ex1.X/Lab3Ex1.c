// Filename: Lab3Ex1.c
// Version: 1.0
// Date:    <27/02/2022>
// Author: <Michael Wood>
//
// Description: Simple demonstration of the LCD custom library functions  
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
#define _XTAL_FREQ 4000000  // MCU clock speed ? required for delay macros
void main(void)
{
    const char myString[] = {"Embedded Systems"}; // Initialise an array with a string
    unsigned short i;                       // Indexing variable
    LCD_initialise();         // Initialise the LCD ready for use
    LCD_puts(myString);       // Display the myString string  
    LCD_cursor(0,1);          // Move the cursor to the 2nd line  
    LCD_cursor_on();    // Turn flashing cursor ON
     
// Illustration of the putch() function
    __delay_ms(2000);           // Wait 2 seconds
    LCD_putch('A');            // Print character A
    __delay_ms(2000);          // Wait 2 seconds
    LCD_putch('B');            // Print character B
    __delay_ms(2000);          // Wait 2 seconds
    LCD_putch('C');    // Print character C
    __delay_ms(2000);          // Wait 2 seconds
    LCD_cursor_off();    // Turn flashing cursor OFF
    for (i=0; i<1000; i++)      // Set up loop to display counting numerals
    {
        LCD_cursor(4,1);        // Move the cursor to the column 4 on the 2nd line  
        LCD_display_value(i);   // Display the value of x at the cursor position
        __delay_ms(100);        // Short delay
    }
}