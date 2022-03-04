#include "main.h"
#include "system_layer.h"
#include "user_layer.h"

uint16_t recTime = 0x0000;
bool msb_received = FALSE;

uint16_t GetSample(uint16_t currIndex){
	uint16_t time = 0x0000;
	
	return time;
}

 void ReceiveSample(uint8_t time_part){
	if(msb_received){
		 recTime |= time_part;
		 msb_received = FALSE;
	}
	else{
		 recTime = (uint16_t) (time_part << 8);
		 msb_received = TRUE;
	}
 }
 