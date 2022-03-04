#include "system_layer.h"

struct fifo RS232_RX;

//IRQ handlers
void USART_RX_Handler(uint32_t data){
	Push(&RS232_RX, (uint8_t) data);
}

void TIM1_Handler(void){
	 
}

