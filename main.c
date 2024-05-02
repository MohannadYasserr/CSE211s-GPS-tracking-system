#include "io.h"
#include "GPIO.h"
#include "UART.h"
#include "stdint.h"
#include "string.h"

#define CR 0x0D



unsigned char SW_Input(void){ 
return GPIO_PORTF_DATA_R & 0x11; 
}

void RGBClear(unsigned char data){
GPIO_PORTF_DATA_R&=data;
}
int button_in;
int main() {
const int len = 10;
char command[len]={0};
GPIO_initPORTF();
UART0_init();

	
while (1) {
button_in=SW_Input();	
	if(button_in==0x01 || button_in==0x10){
led_on(RED);	// Turn On The Red LED
	}
	else {
	RGBClear(~0x0E);
	}
 
}
}