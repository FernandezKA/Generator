
#include "interrupts.h"

static uint16_t counterCh0 = 0;
static uint16_t counterCh1 = 0;
static uint16_t counterCh2 = 0;
static uint16_t counterCh3 = 0;

void USART0_IRQHandler(void)
{
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

void TIMER1_IRQHandler(void)
{
	GPIO_OCTL(GPIOC)^=(1<<13);
	if (timer_flag_get(TIMER1, TIMER_FLAG_UP))
	{
		timer_flag_clear(TIMER1, TIMER_FLAG_UP);
		if (GenerateCh0)
		{
			if (pCh0 != countCh0)
			{ // Check for end of list
				if (counterCh0 != Ch0_array[pCh0].time)
				{
					++counterCh0;
				}
				else
				{
					counterCh0 = 0;
					pCh0++;
				}
			}
			else
			{
				if (RepeatCh0)
				{ // Get circle generation
					pCh0 = 0;
				}
				else
				{ // Disable generation because all of sample is generated
					GenerateCh0 = FALSE;
				}
			}
		}

		if (GenerateCh1)
		{
			if (pCh1 != countCh1)
			{ // Check for end of list
				if (counterCh1 != Ch1_array[pCh1].time)
				{
					++counterCh1;
				}
				else
				{
					counterCh1 = 0;
					pCh1++;
				}
			}
			else
			{
				if (RepeatCh1)
				{ // Get circle generation
					pCh1 = 0;
				}
				else
				{ // Disable generation because all of sample is generated
					GenerateCh1 = FALSE;
				}
			}
		}

		if (GenerateCh2)
		{
			if (pCh2 != countCh2)
			{ // Check for end of list
				if (counterCh2 != Ch2_array[pCh2].time)
				{
					++counterCh2;
				}
				else
				{
					counterCh2 = 0;
					pCh2++;
				}
			}
			else
			{
				if (RepeatCh2)
				{ // Get circle generation
					pCh2 = 0;
				}
				else
				{ // Disable generation because all of sample is generated
					GenerateCh2 = FALSE;
				}
			}
		}

		if (GenerateCh3)
		{
			if (pCh3 != countCh3)
			{ // Check for end of list
				if (counterCh3 != Ch3_array[pCh3].time)
				{
					++counterCh3;
				}
				else
				{
					counterCh3 = 0;
					pCh3++;
				}
			}
			else
			{
				if (RepeatCh3)
				{ // Get circle generation
					pCh3 = 0;
				}
				else
				{ // Disable generation because all of sample is generated
					GenerateCh3 = FALSE;
				}
			}
		}
	}
}
