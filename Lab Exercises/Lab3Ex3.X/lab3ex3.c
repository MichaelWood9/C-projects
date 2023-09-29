// Filename: 	Lab3Ex3.c 
// Version: 	1.0 
// Date:  	<27/03/2022> 
// Author:  	<Michael Wood> 
//   
// PIC16F882 Configuration Bit Settings 
#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits  
#pragma config WDTE = OFF       // Watchdog Timer Enable bit  #pragma config PWRTE = OFF      // Power?up Timer Enable bit  
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
     unsigned short num = 0x01;//stores the number
     
     LCD_initialise();
     while(1){
         if (num%2==0){//checks if the number is even
             num++;// increases num by 1
             
         }
         if(num==100){// checks to see num is 100
             break;//exits the loop
         }
         else{
             LCD_clear();//clears the LCD display
             
             LCD_display_value(num);//displays the odd number
             num++;// increases num by 1
             __delay_ms(500);//500ms delay
            
         }
         
     }
     
}  

