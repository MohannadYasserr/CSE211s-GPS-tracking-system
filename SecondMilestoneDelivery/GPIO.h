 #include "BITUTILITIES.h"
#include "tm4c123gh6pm.h"
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08
#define SW1 !(GPIO_PORTF_DATA_R & 0x10)
#define SW2 !(GPIO_PORTF_DATA_R & 0x01)
void led_off(unsigned char led);
void led_on(unsigned char led);
void GPIO_initPORTF(void);
void SW1_Init(void);
void SW2_Init(void);

