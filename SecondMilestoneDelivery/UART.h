#include "tm4c123gh6pm.h"
#include "BITUTILITIES.h"
#include <stdint.h>

void UART0_init(void);
void UART2_init(void);

char UART0_Read(void);
void UART0_outString(char *pt);
void UART0_outChar(char data);
char UART2_Read(void);
void UART2_outChar(char data);
void UART2_outString(char* pt);

void UART2_interface_singleCharacter(char* command, int len);
void UART2_interface_multipleCharacters(char* command, char stopchar);
void getCommand(char* command, int len);