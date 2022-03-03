#include "uart.h"

void UsartInit(void)
{
	// Enable clocking
	RCU_APB2EN |= RCU_APB2EN_USART0EN;
	RCU_APB2EN |= RCU_APB2EN_PAEN;
	usart_deinit(USART_PC);
	usart_baudrate_set(USART_PC, BAUDRATE);
	usart_parity_config(USART_PC, USART_PM_NONE);
	usart_transmit_config(USART_PC, USART_TRANSMIT_ENABLE);
	usart_receive_config(USART_PC, USART_RECEIVE_ENABLE);
	// usart_interrupt_enable(USART_PC, USART_INT_TBE);
	usart_interrupt_enable(USART_PC, USART_INT_RBNE);
	gpio_afio_deinit();
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);
	gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);
	usart_enable(USART_PC);
	// Set main parameters
}
