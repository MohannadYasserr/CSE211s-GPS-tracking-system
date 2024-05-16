#include "UART.h"
#include "SYSTICK.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"

// Initialize UART0 and PORTA for the serial communication between the PC and the TivaC
void UART0_init(void){
	SYSCTL_RCGCUART_R |=0x0001;       //Activate UART0 
	
//port A for UART0 communication
GPIO_PORTA_LOCK_R=0x4C4F434B;
	GPIO_PORTA_AFSEL_R |= 0x03;   //enable alt function PA0, PA1
	GPIO_PORTA_PCTL_R = ( GPIO_PORTA_PCTL_R & 0xFFFFFF00 ) + 0x00000011;   //configure UART for PA0,PA1
	GPIO_PORTA_DEN_R |= 0x03;	       //enable digital I/O on PA0, PA1
	GPIO_PORTA_AMSEL_R &= ~0x03;	  //disable analog function on PA0, PA1
	
	UART0_CTL_R &= ~(0x0001);	       //Disable UART0
	UART0_IBRD_R = 0x68;            //IBRD=int(160000000/(16*9600)) = 104
	UART0_FBRD_R = 0xB;	           //FBRD = int(0.166*64 +0.5) = 11
	UART0_LCRH_R = 0x0070;	      // 8-bit word length, enable FIFO 001110000
	UART0_CTL_R = 0x0301;        //enable RXE , TXE and UART 001100000001
	
}


// Initialize UART2 and PORTD for the serial communication between the GPS module and the TivaC
void UART2_init(void){
	SYSCTL_RCGCUART_R |=0x0004;       //Activate UART2 

//port D for UART0 communication
GPIO_PORTD_LOCK_R=0x4C4F434B;
	GPIO_PORTD_CR_R |= 0xC0;
	GPIO_PORTD_AFSEL_R |= 0xC0;   //enable alt function PD6, PD7
	GPIO_PORTD_PCTL_R = ( GPIO_PORTA_PCTL_R & 0x00FFFFFF ) + 0x11000000;   //configure UART for 
	GPIO_PORTD_DEN_R |= 0xC0;	       //enable digital I/O 
	GPIO_PORTD_AMSEL_R &= ~0xC0;	  //disable analog function 
	
	UART2_CTL_R &= ~(0x0001);	       //Disable UART2
	UART2_CC_R = 0;        // use system clock
	UART2_IBRD_R = 0x68;            //IBRD=int(160000000/(16*9600)) = 104
	UART2_FBRD_R = 0xB;	           //FBRD = int(0.166*64 +0.5) = 11
	UART2_LCRH_R = 0x0070;	      // 8-bit word length, enable FIFO 001110000
	UART2_CTL_R = 0x0301;        //enable RXE , TXE and UART 001100000001
	
}

    	


 //recieving a char from UART0
char UART0_Read(void) {
	while((UART0_FR_R & 0x0010) != 0);    // check if the buffer is empty
return UART0_DR_R; 	// return the first 8 bits (Data)
}
//write UART0 data

void UART0_outChar(char data){
while(((UART0_FR_R&0x20)!=0));
UART0_DR_R=data;
}
void UART0_outString(char *pt){
while(*pt){
UART0_outChar(*pt);
pt++;	
}
}

//recieving a char from UART0
char UART2_Read(void) {
	while ((UART2_FR_R & 0x0010) != 0);    // check if the buffer is empty
	return UART2_DR_R; 	// return the first 8 bits (Data)
}

//write UART0 data

void UART2_outChar(char data) {
	while (((UART2_FR_R & 0x20) != 0));
	UART2_DR_R = data;
}
void UART2_outString(char* pt) {
	while (*pt) {
		UART2_outChar(*pt);
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
UART0_outChar(character);
}
else if (character!=0x0D || i==len) break;
} 
}


// Function to read a command from UART with a specified length
void UART2_interface_singleCharacter(char* command, int len) {
	char character;
	int i;
	for (i = 0; i < len; i++) {
		character = UART2_Read(); // Read a character from the UART
		if (character != '\r') {    // Check if the character is not the carriage return character
			command[i] = character; // Store the character in the given buffer
			UART2_outChar(command[i]); // Output the character back to the UART
		}
		else if (character == '\r' || i == len) {
			break;  // If the character is the carriage return character or the length of the buffer is reached, break out of the loop
		}
	}
}

// Function to read a command from UART until a specified character is encountered
void UART2_interface_multipleCharacters(char* command, char stopchar) {
	char character[1];
	int i = 0;
	while (1) {
		UART2_interface_singleCharacter(character, 1);   // Read a character from the UART
		if (character[0] != stopchar) {
			command[i] = character[0]; // Store the character in the given buffer
			UART2_outChar(command[i]); // Output the character back to the UART
			i++;
		}
		else if (character[0] == stopchar) {
			command[i]='\0';
			break;  // If the character is the stop character, break out of the loop
		}
	}
}


