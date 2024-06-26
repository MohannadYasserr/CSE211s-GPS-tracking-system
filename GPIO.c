#include "io.h"
#include "GPIO.h"

// intializes port F
void GPIO_initPORTF(void) {	
SYSCTL_RCGCGPIO_R |= 0X20;	            // activates clock for port F
while ((SYSCTL_PRGPIO_R & 0X20) == 0)	// waits for clock to stabalize
;
;
;
;
GPIO_PORTF_LOCK_R=0x4C4F434B;
GPIO_PORTF_CR_R |=0x1F;
GPIO_PORTF_AMSEL_R &=~ 0x1F;
GPIO_PORTF_AFSEL_R &=~ 0x1F;
GPIO_PORTF_PCTL_R  &= ~0x000FFFFF;
GPIO_PORTF_DIR_R |= 	0x0E;
GPIO_PORTF_DEN_R |= 	0x1F;
GPIO_PORTF_DATA_R	&= ~0x1F;
GPIO_PORTF_PUR_R =0x11	;
/*
    GPIO_PORTF_LOCK_R = 0x4C4F434B ;     // unlocks port F
    GPIO_PORTF_CR_R = 0X0E;             // enables changes to port F
    GPIO_PORTF_AMSEL_R = 0;		    // disable analog function on port F
    GPIO_PORTF_PCTL_R = 0;	    // diables alternate function config on port F
    GPIO_PORTF_DIR_R = 0X0E;	        // sets pins 1,2,3 to output - pins 0,4 to input
    GPIO_PORTF_AFSEL_R = 0;	        // disabels alternate functions on port F
    GPIO_PORTF_DEN_R = 0X0E;		    // enables digital data on all pins
    GPIO_PORTF_DATA_R &= ~0x0E;         // intialiazes all data to 0 on the pins
*/
}


void led_on(unsigned char led){
GPIO_PORTF_DATA_R |= led;
}

void led_off(unsigned char led){
GPIO_PORTF_DATA_R &= ~led;
} 

