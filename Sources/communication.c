#include "communication.h"
//User variables


//User function definition



//This function used for print info messages to RS232 serial on PC
void print(unsigned char* pMsg){
	uint8_t countSend = 0;
	char lastChar = 0;
	char currChar = 0;
	bool isEnd = FALSE;
	while(!isEnd && countSend != 0xFF){
		lastChar = currChar;
		currChar = pMsg[countSend++];
		if((lastChar == 0x0A) && (currChar == 0x0D)){
			 isEnd = TRUE;
		}
		else if((lastChar == 0x0D) && (currChar == 0x0A)){
			 isEnd = TRUE;
		}
		while((USART_STAT(USART_PC)&USART_STAT_TBE) != USART_STAT_TBE){__NOP();}
		usart_data_transmit(USART_PC, currChar);
	}
}

//This function parsed input data to command
enum Command GetCommand(unsigned char recData){
	switch(recData){
		case 0x00:
			return stopGeneration;
		case 0x01:
			return startGeneraion;
		case 0x02:
			return repeatGeneration;
		case 0x03:
			return setAutostart;
		case 0x04:
			 return resetAutostart;
		case 0x05:
				return setChNum;
		case 0x06:
			 return startLoad;
		case 0x07:
			 return stopLoad;
		default:
			return undefined;
	}
}

