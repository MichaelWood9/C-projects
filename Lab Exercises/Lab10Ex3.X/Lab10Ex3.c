// Filename: Lab10Ex3.c 
// Version: 1.0 
// Date: <Insert current date> 
// Author: <Insert your name> 
// Purpose: Demonstrates PWM generation on pin RC2 using CCP1 module 
 
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
 
void main(void)      
 { 
   TRISC = 0x00;  // Set PORTC as output 
   PORTC = 0x00;  // Clear PORTC
   TRISB = 0x03;               
   PORTB = 0x00; 
   T1CON= 0x31;
      
   PR2 = 0x63;  // Set PWM period 
   T2CON = 0x04;        // Prescaler= 1:1, Timer 2 ON 
   CCP2CON = 0x0C; // PWM mode selected. Duty cycle LSBs are not used. 
                        // 8 bit PWM resolution available 
   CCPR2L = 0x00;  // Set duty cycle to 0 
   
   OPTION_REGbits.T0CS = 0;    // Set clock source to internal (timer mode) 
   OPTION_REGbits.PSA = 0;     // Set prescaler to Timer 0 
   OPTION_REGbits.PS = 3;      // Set prescaler bits to 011 for 1:16 
   //Interrupt setup 
   //INTCONbits.INTE = 1;
   //INTCONbits.INTF = 0;
   INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
   INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
   IOCBbits.IOCB = 1;          // Enable RBIE on RB0 only  
   INTCONbits.GIE = 1;         // Enable interrupts
    
   unsigned int count_Down = 0;
   while(1) 
    { 
       __delay_ms(50);  // Short delay
       if (count_Down == 0){//checks if count_down is 0
          CCPR2L++;           // Change PWM duty cycle 
       }
       if (count_Down == 1){//checks if count_down is 1
           CCPR2L--; // counts down PWM duty cycle
       }
        
       if(CCPR2L == 100){//checks if duty cycle is 100
           count_Down = 1;//sets count down to 1
       }
    }       
}

void __interrupt() my_ISR(void) 
{ 
    unsigned int count = 0 ;
    if(INTCONbits.RBIF) 
    { 
        if(PORTBbits.RB0){//checks if RB0 triggered the interrupt
            count++;
            if (count == 1){//checks if count is 1
                PR2 = 9;//sets PR2 to set time base to 1 KHZ
            }
            if (count == 2){//checks if count is 2
                PR2 = 49;//sets PR2 to set time base to 5 KHZ
            }
            if (count == 3){//checks if count is 3
                PR2 = 99;//sets PR2 to set time base to 10 KHZ
            }
            if (count == 4){//checks if count is 4
                PR2 = 249;//sets PR2 to set time base to 25 KHZ
            }
            if (count == 5){//checks if count is 5
                PR2 = 499;//sets PR2 to set time base to 50 KHZ
                count = 0;
            }

            PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition (mismatch)
        }
        INTCONbits.RBIF = 0;// Clear interrupt flag
        return;
      
    }
    
} 
