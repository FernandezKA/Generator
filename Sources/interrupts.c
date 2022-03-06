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

//Used for indicate activty
void TIMER1_IRQHandler(void){
 timer_interrupt_flag_clear(LED_TIMER, TIMER_INT_FLAG_UP);
 GPIO_OCTL(GPIOC)^=(1<<13);
}
//Used for definition freq. of sampling
void	TIMER0_UP_IRQHandler(void)
{
	timer_interrupt_flag_clear(SMP_TIMER, TIMER_INT_FLAG_UP);
	TIM0_Handler();
}
