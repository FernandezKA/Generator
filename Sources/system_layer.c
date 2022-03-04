#include "system_layer.h"

uint32_t pBeginCh0 = 0x1FFF0000;
uint32_t pEndCh0 = 	0x1FFF77FF;

struct fifo RS232_RX;

//IRQ handlers
void USART_RX_Handler(uint32_t data){
	Push(&RS232_RX, (uint8_t) data);
}

void TIM1_Handler(void){
	
}

bool status_gen(uint8_t channel, bool state){
	bool status = FALSE;
	 switch(channel){
		 case 0:
			 if(state){
					
			 }
			 else{
				 
			 }
			 status = TRUE;
		 break;
		 
		 default:
			 status = FALSE;
		 break;
	 }
	 return status;
}


