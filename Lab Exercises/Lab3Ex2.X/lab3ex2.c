// Filename: 	Lab3Ex2.c 
// Version: 	1.0 
// Date:  	<27/03/2022> 
// Author:  	<Michael Wood> 
// 
// Description: Simple demonstration of the LCD custom library functions   
// PIC16F882 Configuration Bit Settings 
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits  
#pragma config WDTE = OFF       // Watchdog Timer Enable bit  #pragma config PWRTE = OFF       
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
     const char myString[]={"Michael"};//creates a constant string variable
     const char myString2[]={"Wood"};//creates a constant string variable
     unsigned short i;
     char x;
     LCD_initialise();// initialise the LCD
     LCD_puts(myString);// displays mystring 
     LCD_cursor(0,1);//moves the cursor to the start of the second line
     LCD_cursor_on();
     
     for (i=0; myString2[i];i++){//loops through mystring2 
         x = myString2[i];//sets x to the current character in the loop
         __delay_ms(1000);//1000ms delay
         LCD_putch(x);//displays x on the LCD
     
     }
}  