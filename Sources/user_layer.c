#include "main.h"
#include "system_layer.h"
#include "user_layer.h"

uint32_t recTime = 0x0000;
uint8_t part_received = 0x00;

uint32_t GetSample(uint32_t currIndex, uint32_t* pTable){
	uint32_t data = FlashRead((uint32_t*) ((uint32_t) pTable + (currIndex) * sizeof(uint32_t)));
	if(data > 1){
		 data--;
	}
	return data;
}

bool ReceiveSample(uint8_t time_part){
	if(part_received == 0x03U){
		 recTime |= time_part;
		 if(recTime != 0){
		 AddSample(recTime);
		 }
		 part_received = 0x00;
		 return TRUE;
	}
	else{
		if(part_received == 0){
			 recTime = 0;
		}
		recTime |= (uint32_t) (time_part <<  (32 - ((part_received + 1) * 8)));
		++part_received;
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
//		while((USART_STAT(USART_PC)&USART_STAT_TBE) != USART_STAT_TBE){__NOP();}
//		usart_data_transmit(USART_PC, currChar);
		 Push(&RS232_TX, currChar);
	}
}

