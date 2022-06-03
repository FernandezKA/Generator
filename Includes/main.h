#pragma once
#include <stdint.h>
//#include <stdbool.h>

//#define TRUE true
//#define FALSE false
	
#define USB_VCP

#include "gd32f10x.h"
#include "gd32f10x_usart.h"
#include "gd32f10x_gpio.h"
#include "gd32f10x_timer.h"

// User includes
#include "fifo.h"
#define CH_1 0x00U
#define FMC_PAGE_SIZE           ((uint16_t)0x400U)
static inline void get_div(uint32_t num, volatile uint32_t *CCR, volatile uint32_t *CREP, volatile uint32_t *PSC)
{
	if (num < 0xFFFF) //mS, that less 0xFFFF 
	{
		if(num == 0x01){
			*CCR = num;
		}
		else{
			*CCR = num - 1U;
		}
		*CREP = 0U;
		*PSC = 719; //(Fclk/ (psc * ARR_val)
	}
	else
	{
		*CCR = num / 100U - 1U;
		*CREP = 9U;
		*PSC = 7199; //(Fclk/ARR * REP * PSC)
	}
}

#define USART_PC USART0
#define LED_TIMER TIMER1
#define SMP_TIMER TIMER0

extern uint8_t initial_state; 
