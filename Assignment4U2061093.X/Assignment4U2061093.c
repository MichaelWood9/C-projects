// Filename:  Assignment4u2061093.c 
// Version:  1.0 
// Date:  <26/04/2022> 
// Author: <Michael Wood> 
// Purpose: Read, display and convert temperature   
 
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
#include "LCDdrive882.h"    // Header file needed to access to LCD custom library
#include "ADClib882.h"
#include "ThermistorConv.h"

void config(void);          // Configuration function 
void tempDisplay(void);// Tempature display function
short convertToF(short t);//convert to F
void HighLow(void);//function to get highest and lowested temp since start or reset
void ledBarChartC(void);//function for LED bar chart
void displayHighLow(short,short);//displays high and low temp.


char convert = 0;
char updateScreen = 1;
char count = 0;
short temp;
short high;
short low = 200;
short lowF;
short highF;
char  count2;
char  result;
char bar ;



 
void main(void) 
{ 
    config();                    // Call configuration function 
   
    LCD_initialise();//initialise LCD for use
    ADC_initialise();//initialise ADC for use
    


    while(1){//while loop
        tempDisplay();//runs the program
    }
    

} 

void config(void) 
{ 
    INTCONbits.GIE = 0;      // Disable interrupts during configuration 
     
    ANSEL = 0x00;   // All pins as digital outputs 
    ANSELH = 0x00;  
    TRISA = 0x00;           // Configure PORTA 
    PORTA = 0x00;
    TRISB = 0x03;
    PORTB = 0x00;     
    T1CON = 0x30;           // Timer1 OFF, Prescaler 1:8 

    T1CONbits.TMR1ON = 0;   // Turn Timer 1 OFF 
    TMR1 = 3036;            // Preload for 500 ms @ Pre=1:8, 4 MHz 
     
    PIE1bits.TMR1IE = 1;    // Enable TIMER1 interrupt ONLY 
    PIR1bits.TMR1IF = 0;    // Clear Timer1 interrupt flag 
     
    INTCONbits.PEIE =1;     // Enable PEIE and GIE 
    INTCONbits.GIE=1;         
    T1CONbits.TMR1ON = 1;   // Turn Timer 1 ON 
    
        
        INTCONbits.RBIE = 1;        // Enable Timer0 overflow interrupt 
        INTCONbits.RBIF = 0;        // Clear Timer0 overflow interrupt 
        IOCBbits.IOCB = 3;          // Enable RBIE on RB0 and RB1
} 

void tempDisplay(void){
    if (updateScreen == 1){//checks if screen update = 1
        LCD_clear();//clears LCD
        updateScreen = 0;
        LCD_cursor(0,0);//sets cursor to the start of the first line
    
        ADC_channel_select(11);//select the ADC channel
        temp = GetThermistorTemp(ADC_read());//gets the ADC value converts it to temperature and sets to to the variable 'temp'
        if (convert == 1){//checks if convert = 1
            
            LCD_putsc("Temp = ");//displays a string
            temp = convertToF(temp); //converts temp to f
            LCD_display_value(temp);//displays temp
            LCD_cursor(10,0);//moves cursor to top line 10 spaces.
            LCD_putsc("deg F");//displays 'deg C' on LCD
        
        }
        else{
            LCD_putsc("Temp = ");//displays a string
            LCD_display_value(temp);//displays temp
            LCD_cursor(10,0);//moves cursor to top line 10 spaces .
            LCD_putsc("deg C");//displays 'deg C' 
        }
        HighLow();//gets high low temp
        ledBarChartC();//runs the LED bar graph

    }    
}

short convertToF(short t){//converts to F
    short converted;
    converted = ((t*18)/10)+32;//converts to F
    return converted;
}

void HighLow(void){//gets high low
    if(GetThermistorTemp(ADC_read())>high){//checks if current temp is < than high temp
        high = GetThermistorTemp(ADC_read());//updates the high temp for new high
    }
    if(GetThermistorTemp(ADC_read())<low){//checks if current temp is > than low temp
        low = GetThermistorTemp(ADC_read());//updates the low temp for new low
    }
    if(convert == 1){//checks if convert = 1
        displayHighLow(convertToF(low),convertToF(high));//displays the high and low in F

    
    }
    else{
        displayHighLow(low,high);//displays high and low temp in C

    }
    
}

void ledBarChartC(void){//makes the LED a temp bar chart in C
    
    result = GetThermistorTemp(ADC_read());//gets the current temp
    result = result/10;//divides temp by 10

    while(1){
        bar = (bar*2)+1;//calulates the number to make the bar chart
        count2++;//increments count
        if(count2 == result){//checks if count = result     
            PORTA = bar;//sets port a to bar
            bar = 0;
            count2 = 0;
            break;//breaks the loop
        }
    }    
}

void displayHighLow( short min ,short max){//display high and low temp takes the high and low temps as parameters
        LCD_cursor(0,1);///sets LCD cursor to the second line
        LCD_putsc("min=");//prints out a string
        LCD_display_value(min);//displays the min temp
        LCD_cursor(9,1);//moves the cursor to the second line 9 character along
        LCD_putsc("max=");//prints out a string
        LCD_display_value(max);//displays the max temp.
    
}

void __interrupt() myISR(void) 
{ 
    if(PIR1bits.TMR1IF) //checks for timer 1 interrupt
    { 
        
        T1CONbits.TMR1ON = 0;     // Turn Timer 1 OFF 
        TMR1 = 3036;              // Preload for 500 ms @ Pre=1:8, 4 MHz 
        T1CONbits.TMR1ON = 1;     // Turn Timer 1 ON 
        
        count++;//increments count
        if (count == 2){//checks if count = 2
            count = 0;
            updateScreen = 1;//set updateScreen to 1 so the screen updates
        }
        
        
        PIR1bits.TMR1IF = 0;    // Clear interrupt flag  
    } 
    if(INTCONbits.RBIF) 
    { 
        if(PORTBbits.RB0){//check if RB0 cause the interrupt
            convert++;//increments converts
            if (convert>1){//checks if convert greater than 1
                convert = 0;
            }
            PORTBbits.RB0 = 0;  // Write PORTB to clear interrupt condition 
        }
        else if(PORTBbits.RB1){//check if RB0 cause the interrupt
           high = temp;//resets high temp value
           low = temp;//resets low temp value
            
            PORTBbits.RB1 = 0;  // Write PORTB to clear interrupt condition 
        }

        INTCONbits.RBIF = 0;// Clear interrupt flag
    }
}