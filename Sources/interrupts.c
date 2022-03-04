#include "interrupts.h"
#include "system_layer.h"

#define GPIO_LED (1U << 13)
#define GPIO_CH0 (1U << 12)
#define GPIO_CH1 (1U << 13)

void USART0_IRQHandler(void)
{
	if (usart_flag_get(USART_PC, USART_FLAG_RBNE))
	{
		usart_flag_clear(USART_PC, USART_FLAG_RBNE);
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
	}
}
