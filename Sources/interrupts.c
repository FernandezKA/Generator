
#include "interrupts.h"

void USART0_IRQHandler(void){
	 if (usart_flag_get(USART_PC, USART_FLAG_RBNE))
	{
		usart_flag_clear(USART_PC, USART_FLAG_RBNE);
		Push(&RS232_RX, (uint8_t)usart_data_receive(USART_PC));
	}
	else
	{
		USART_STAT(USART_PC) = 0;
	}
}


void TIMER1_IRQHandler(void){
	TIMER_INTF(TIMER1) = 0;   //Clear IRQ flags
	if(timer_flag_get(TIMER1, TIMER_FLAG_UP)){
		timer_flag_clear(TIMER1, TIMER_FLAG_UP);
		__NOP();
	}
}

