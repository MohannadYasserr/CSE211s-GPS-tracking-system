#include "tm4c123gh6pm.h"
#include "BITUTILITIES.h"
#include <stdint.h>

#ifndef LCD_INTERFACE
#define LCD_INTERFACE


void LCD4bits_Init(void);
void LCD_Write4bits(unsigned char data, unsigned char control);
void LCD_WriteString(char* str);
void LCD4bits_Cmd(unsigned char command);
void LCD4bits_Data(unsigned char data);




#endif 