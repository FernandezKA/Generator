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



void TIMER1_IRQHandler(void){
 
};
void	TIMER0_UP_IRQHandler(void)
{
	timer_interrupt_flag_clear(TIMER0, TIMER_INT_FLAG_UP);
	TIM0_Handler();
}
