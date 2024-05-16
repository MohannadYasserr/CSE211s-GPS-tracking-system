#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "SYSTICK.h"
void sysTick_init(){
NVIC_ST_CTRL_R=0;
NVIC_ST_RELOAD_R=0x00FFFFFF;
NVIC_ST_CURRENT_R =0;
NVIC_ST_CTRL_R=0x05;	

}
void sysTick_wait(int delay){
NVIC_ST_RELOAD_R=delay-1;
NVIC_ST_CURRENT_R =0;	
while((NVIC_ST_CTRL_R&0x00010000)==0);	
}
//wait multiples of 1sec
void sysTick_waitxs(int delay){
unsigned long i;
for (i=0 ; i<delay ; i++){
	sysTick_wait(16000000);
}	}