
#include "interrupts.h"

void USART0_IRQHandler(void){
	 if (usart_flag_get(USART_PC, USART_FLAG_RBNE))
	{
		usart_flag_clear(USART_PC, USART_FLAG_RBNE);
		Push(&RS232_RX, (uint8_t)usart_data_receive(USART_PC));
	}
	else if (usart_flag_get(USART_PC, USART_FLAG_TBE))
	{
		if (GetSize(&RS232_RX) != 0)
		{
			usart_data_transmit(USART_PC, Pull(&RS232_RX));
		}
		else
		{
			usart_interrupt_disable(USART_PC, USART_INT_TBE);
		}
	}
	else
	{
		USART_STAT(USART_PC) = 0;
	}
}
