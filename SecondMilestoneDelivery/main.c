#include "io.h"
#include "GPIO.h"
#include "UART.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "SYSTICK.h"
#include "LCD.h"
#include "GPS.h"
#include "TM4C123.h"
#include "tm4c123gh6pm.h"
// Function to convert an integer to a string
void intToStr(int num, char *str) {
    sprintf(str, "%d", num); // Use sprintf to convert the integer to a string
}

// Function to convert a floating-point number to a string
void floatToStr(float num, char *str) {
    sprintf(str, "%.2f", num); // Use sprintf to convert the floating-point number to a string with two decimal places
}
void UART0_outInt(int num) {
    char str[20]; // Define a buffer to hold the string representation of the integer
    intToStr(num, str); // Convert the integer to a string
    UART0_outString(str); // Print the string over UART
}
unsigned char SW_Input(void) {
    return GPIO_PORTF_DATA_R & 0x11;
}

void RGBClear(unsigned char data) {
    GPIO_PORTF_DATA_R &= data;
}

// declare here the long_final , lat_final values 

 int main() {
    // Declare variables
    double dd;
    char distancs_str[50];
    char latitude[50];
    char longtitude[50];
    float previousLat = currentLat;
    float previousLong = currentLong;
    double total_distance = 0;
    bool first_time = true;
	// char *str="somevalue1234"
    // Initialize the system
    GPIO_initPORTF();
    sysTick_init();
    UART0_init();
    UART2_init();
	// LCD4bits_Init();
    // Start the system
    led_on(RED);
						// // str = "starting";
            // LCD4bits_Cmd(0x01);
           //  LCD4bits_Cmd(0x80);
           //  sysTick_waitxs(100);
          //   LCD_WriteString(str);
           //  sysTick_waitxs(100);
    sysTick_waitxs(10);
    while (total_distance < 100 && !SW1) {
			  RGBClear(~0x0E);
        led_on(BLUE);
        GPS_read2();
        currentLat = GPStoDeg(currentLat);
        currentLong = GPStoDeg(currentLong);
     
        UART0_outString(lat);
        UART0_outString(longi);
        dd = haversine(previousLat, previousLong, currentLat, currentLong );
        if (!first_time && dd > 1)
            total_distance += dd;
        previousLat = currentLat;
        previousLong = currentLong;
         sysTick_waitxs(1);
        first_time = false;
    }
		 if (total_distance >= 100){
    led_on(GREEN);
			 // str = "100m reached";
            // LCD4bits_Cmd(0x01);
           //  LCD4bits_Cmd(0x80);
           //  sysTick_waitxs(100);
          //   LCD_WriteString(str);
           //  sysTick_waitxs(100);
		 }
   
    else {
        //LCD_WriteString("SW1 pressed!");
    }

		return 0;
}