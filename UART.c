#include "UART.h"

// Initialize UART0 and PORTA
void UART0_init(void){
	SYSCTL_RCGCUART_R |=0x0001;       //Activate UART0
	SYSCTL_RCGCGPIO_R |=0x0001;      //Activate PortB
	while(GET_BIT(SYSCTL_PRGPIO_R,0)==0 );	
	;
	;
	;
	UART0_CTL_R &= ~(0x0001);	       //Disable UART0
	UART0_IBRD_R = 0x68;            //IBRD=int(160000000/(16*9600)) = 104;
	UART0_FBRD_R = 0xB;	           //FBRD = int(0.166*64 +0.5) = 11
	UART0_LCRH_R = 0x0070;	      // 8-bit word length, enable FIFO 001110000
	UART0_CTL_R = 0x0301;        //enable RXE , TXE and UART 001100000001
	GPIO_PORTA_AFSEL_R |= 0x03;   //enable alt function PA0, PA1
	GPIO_PORTA_PCTL_R = ( GPIO_PORTA_PCTL_R & 0xFFFFFF00 ) + 0x00000011;   //configure UART for PA0,PA1
	GPIO_PORTA_DEN_R |= 0x03;	       //enable digital I/O on PA0, PA1
	GPIO_PORTA_AMSEL_R &= ~0x03;	  //disable analog function on PA0, PA1
}

//recieving a char from UART0
char UART0_Read(void) {
	while((UART0_FR_R & 0x0010) != 0);    // check if the buffer is empty
return UART0_DR_R; 	// return the first 8 bits (Data)
}
//write UART data

void UART_outChar(char data){
while(((UART0_FR_R&0x20)!=0));
UART0_DR_R=data;
}
void UART_outString(char *pt){
while(*pt){
UART_outChar(*pt);
pt++;	
}
}
//asking user input on UART but won't be called in main yet for first milestone just having it ready

void getCommand(char * command , int len){
char character;
int i;
	for(i=0;i<len;i++){
character=UART0_Read();
if(character!=0x0D){		
command[i]=character;
UART_outChar(character);
}
else if(character!=0x0D || i==len) break;
} 
}
