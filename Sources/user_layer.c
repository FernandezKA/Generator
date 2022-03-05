#include "main.h"
#include "system_layer.h"
#include "user_layer.h"

uint16_t recTime = 0x0000;
bool msb_received = FALSE;

uint16_t GetSample(uint16_t currIndex){
	uint16_t time = 0x0000;
	time = FlashHalfRead((uint32_t*) ((uint32_t) currIndex + (uint32_t) pBeginCh0));
	return time;
}

 bool ReceiveSample(uint8_t time_part){
	if(msb_received){
		 recTime |= time_part;
		 AddSample(recTime);
		 msb_received = FALSE;
		 return TRUE;
	}
	else{
		 recTime = (uint16_t) (time_part << 8);
		 msb_received = TRUE;
		 return FALSE;
	}
 }

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

