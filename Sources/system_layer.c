#include "system_layer.h"
#include "user_layer.h"

uint32_t *pInfo = (uint32_t *)0x08007C00;
uint32_t *pBeginCh0 = (uint32_t *)0x08008800; // Page 32
uint32_t *pEndCh0 = (uint32_t *)0x082FFFFF;	  // Page 64
bool repeat_ch0 = FALSE;
bool autostartCh0 = FALSE;
uint8_t parity = 0xFF;
uint32_t samplesCh0[32U];

volatile uint32_t currSampleCh0 = 0;
volatile uint32_t countSampleCh0 = 0;

struct fifo RS232_RX;

void get_initial_state(void)
{
	if (parity == 0xFF)
	{
		GPIO_OCTL(GPIOB) &= ~(1U << 12);
	}
	else
	{
		GPIO_OCTL(GPIOB) |= (1U << 12);
	}
}

// IRQ handlers
void USART_RX_Handler(uint32_t data)
{
	Push(&RS232_RX, (uint8_t)data);
}

void TIM0_Handler(void)
{
	if (currSampleCh0 < countSampleCh0 - 1 && countSampleCh0 != 0)
	{
		GPIO_OCTL(GPIOB) ^= (1 << 12);
		get_div(GetSample(++currSampleCh0, pBeginCh0), &TIMER_CAR(SMP_TIMER), &TIMER_CREP(SMP_TIMER), &TIMER_PSC(SMP_TIMER));
		TIMER_CTL0(SMP_TIMER) |= TIMER_CTL0_CEN;
	}
	else if (countSampleCh0 - 1U == currSampleCh0 && countSampleCh0 != 0) // It's last sample from packet
	{
		if (repeat_ch0)
		{
			/* set time - set initial state - set zero counter*/
			currSampleCh0 = 0x00U;
			get_div(GetSample(currSampleCh0, pBeginCh0), &TIMER_CAR(SMP_TIMER), &TIMER_CREP(SMP_TIMER), &TIMER_PSC(SMP_TIMER));
			get_initial_state();
			TIMER_CTL0(SMP_TIMER) |= TIMER_CTL0_CEN;
		}
		else // Repeat flag isn't set
		{
			GPIO_OCTL(GPIOB) ^= (1 << 12);
			currSampleCh0 = 0;
			StopGenCh0();
		}
		//get_initial_state();
	}
}

bool status_gen(uint8_t channel, bool state)
{
	bool status = FALSE;
	switch (channel)
	{
	case 0:
		if (state)
		{
			TIMER_CTL0(SMP_TIMER) |= TIMER_CTL0_CEN;
		}
		else
		{
			TIMER_CTL0(SMP_TIMER) &= ~TIMER_CTL0_CEN;
		}
		status = TRUE;
		break;

	default:
		status = FALSE;
		break;
	}
	return status;
}

void AddSample(uint32_t sample)
{
	if (countSampleCh0 % 0x20 == 0x1F && countSampleCh0 != 0)
	{
		samplesCh0[countSampleCh0++ % 0x20] = sample;
		FlashWrite((uint32_t)pBeginCh0 + (countSampleCh0) * sizeof(uint32_t) - 0x80, samplesCh0);
	}
	else
	{
		samplesCh0[countSampleCh0++ % 0x20] = sample;
	}
}
//
bool status_repeat(uint8_t channel, bool state)
{
	bool status = FALSE;
	switch (channel)
	{
	case 0x00:
		repeat_ch0 = state;
		status = TRUE;
		break;
	default:
		status = FALSE;
		break;
	}
	return status;
}

static inline uint32_t bool_to_uint32_t(bool state)
{
	if (state)
	{
		return 0xF0F0F0F0;
	}
	else
	{
		return 0;
	}
}

static inline bool uint32_t_to_bool(uint32_t value)
{
	if (value == 0xF0F0F0F0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void getRestore(volatile uint32_t *cntSamples, volatile bool *repCh0, volatile bool *autostart)
{
	if (FlashRead(pInfo) != 0xFFFFFFFF)
	{
		*cntSamples = FlashRead(pInfo);
	}
	*repCh0 = uint32_t_to_bool(pInfo[1]);
	*autostart = uint32_t_to_bool(pInfo[2]);
}

void getBackup(volatile uint32_t *cntSamples, volatile bool *repCh0, volatile bool *autostart)
{
	static uint32_t tmpArray[32U];
	tmpArray[0] = *cntSamples;
	tmpArray[1] = bool_to_uint32_t(*repCh0);
	tmpArray[2] = bool_to_uint32_t(*autostart);
	FlashErase((uint32_t)pInfo);
	FlashWrite((uint32_t)pInfo, tmpArray);
}

void getTimerReset(void)
{
	TIMER_CTL0(SMP_TIMER) &= ~TIMER_CTL0_CEN;
	TIMER_CREP(SMP_TIMER) = (uint16_t)0x00U;
	TIMER_CAR(SMP_TIMER) = (uint16_t)0x01U;
	TIMER_CTL0(SMP_TIMER) |= TIMER_CTL0_CEN;
}
