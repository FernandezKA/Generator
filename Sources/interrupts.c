#include "interrupts.h"
#include "system_layer.h"

void USART0_IRQHandler(void)
{
	volatile uint32_t usart_stat = USART_STAT(USART_PC);
	if ((usart_stat & USART_STAT_TC) == USART_STAT_TC)
	{
		USART_RX_Handler(usart_data_receive(USART_PC));
	}
	else
	{
		USART_STAT(USART_PC) = 0;
	}
}



void TIMER1_IRQHandler(void)
{
	// This part of code used for generate signal
	if (timer_flag_get(TIMER1, TIMER_FLAG_UP))
	{
		timer_flag_clear(TIMER1, TIMER_FLAG_UP);
		TIM1_Handler();
	}
}
