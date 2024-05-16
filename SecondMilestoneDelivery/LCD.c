#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
#include "GPS.h"
#include "UART.h"
#include "LCD.h"
#include "SYSTICK.h"

#define RS 0x01        // Bit mask for LCD RS pin
#define RW 0x02        // Bit mask for LCD RW pin
#define EN 0x04        // Bit mask for LCD EN pin
// Initialize the LCD by setting up the necessary GPIO pins and sending initialization commands to the LCD
void LCD4bits_Init(void)
{
       // Send initialization commands to the LCD
    LCD4bits_Cmd(0x28);          // 2 lines and 5x7 character (4-bit data, D4 to D7)
    LCD4bits_Cmd(0x06);          // Automatic Increment cursor (shift cursor to right)
    LCD4bits_Cmd(0x01);					 // Clear display screen
    LCD4bits_Cmd(0x0F);          // Display on, cursor blinking
}

// Write a 4-bit command or data to the LCD
void LCD_Write4bits(unsigned char data, unsigned char control)
{
    data &= 0xF0;                       // clear lower nibble for control 
    control &= 0x0F;                    // clear upper nibble for data
    GPIO_PORTD_DATA_R = data | control;         // Include RS value (command or data ) with data 
    GPIO_PORTD_DATA_R = data | control | EN;    // pulse EN
    sysTick_waitxs(1);													// delay for pulsing EN
    GPIO_PORTD_DATA_R = data | control;					// Turn off the pulse EN
    GPIO_PORTD_DATA_R = 0;                      // Clear the Data 
}

// Write a null-terminated string to the LCD
void LCD_WriteString(char* str)
{
    volatile int i = 0;          // volatile is important 

    // Write each character of the string until the end of the string
    while (*(str + i) != '\0')
    {
        LCD4bits_Data(*(str + i));    // Write each character of the string
        i++;                        // Increment for next character
    }
}

// Send a command to the LCD
void LCD4bits_Cmd(unsigned char command)
{
    // Send the upper nibble of the command first, followed by the lower nibble
    LCD_Write4bits((command & 0xF0)>>1, 0);    // upper nibble first
    LCD_Write4bits(command << 3, 0);			 // then lower nibble

    // Delay after certain commands
    if (command < 4)
        sysTick_waitxs(2);       // commands 1 and 2 need up to 1.64ms
    else
        sysTick_waitxs(40);      // all others need a 40us delay
}

// Send data to the LCD
void LCD4bits_Data(unsigned char data)
{
    // Send the upper nibble of the data first, followed by the lower nibble
    LCD_Write4bits((data & 0xF0)>>1, RS);   // upper nibble first
    LCD_Write4bits(data << 3, RS);     // then lower nibble

    // Delay for the LCD (MCU is faster than LCD)
    sysTick_waitxs(40);
}