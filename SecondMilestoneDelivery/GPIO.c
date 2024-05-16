#include "io.h"
#include "GPIO.h"
#include "tm4c123gh6pm.h"
// intializes port F
void GPIO_initPORTF(void) {	
SYSCTL_RCGCGPIO_R |= 0x3B;	            // activates clock for port A,B,D,F
while ((SYSCTL_PRGPIO_R & 0x3B) == 0)	// waits for clock to stabalize
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




	//port D for LCD communication
GPIO_PORTB_LOCK_R=0x4C4F434B;
GPIO_PORTB_CR_R |=0xFF;
GPIO_PORTB_AMSEL_R &=~ 0xFF;
GPIO_PORTB_AFSEL_R &=~ 0xFF;
GPIO_PORTB_PCTL_R  &= ~0xFFFFFFFF;
GPIO_PORTB_DIR_R |= 	0xFF;
GPIO_PORTB_DEN_R |= 	0xFF;
GPIO_PORTF_DATA_R	&= ~0xFF;
GPIO_PORTF_PUR_R =0x00	;

}


void led_on(unsigned char led){
GPIO_PORTF_DATA_R |= led;
}

void led_off(unsigned char led){
GPIO_PORTF_DATA_R &= ~led;
} 

