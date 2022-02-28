#include "communication.h"
//User variables

enum PairReceive pairState;
//User function definition



//This function used for print info messages to RS232 serial on PC
void print(char* pMsg){
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
		case 0x01:
			return stopGeneration;
		case 0x02:
			return startGeneraion;
		case 0x03:
			return repeatGeneration;
		case 0x04:
			return setAutostart;
		case 0x05:
			 return resetAutostart;
		case 0x06:
				return setChNum;
		case 0x07:
			 return startLoad;
		case 0x08:
			 return stopLoad;
		default:
			return undefined;
	}
}


bool ReceivePair(struct pulse* cPulse, enum PairReceive* cPairState, unsigned char data){
	if(*cPairState == wait_state){
		 if(data == 0x00){
			 cPulse->state = FALSE;
		 }
		 else if(data == 0xFF){
			 cPulse->state = TRUE;
		 }
		 *cPairState = wait_MSB;
		 return FALSE;
	}
	else if(*cPairState == wait_MSB){
		cPulse->time = (uint16_t) (data << 8);
		*cPairState = wait_LSB;
		return FALSE;
	}
	else if(*cPairState == wait_LSB){
		cPulse-> time |= data & 0xFFU;
		*cPairState = complete;
		return TRUE;
	}
	else{
		 *cPairState = wait_state;
			return FALSE;
	}
	
}
