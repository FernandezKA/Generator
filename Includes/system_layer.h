#pragma once
#include "fifo.h"

extern uint32_t* pInfo;
extern uint32_t* pBeginCh0;
extern uint32_t* pEndCh0;

extern volatile uint32_t currSampleCh0;
extern volatile uint32_t countSampleCh0;
extern uint32_t samplesCh0[32U];
extern bool 		autostartCh0;


extern struct fifo RS232_RX;

extern bool repeat_ch0;
extern uint8_t parity;

void USART_RX_Handler(uint32_t data);

void TIM0_Handler(void);

bool status_gen(uint8_t channel, bool state);

void AddSample(uint32_t sample);

bool status_repeat(uint8_t channel, bool state);

void getRestore(volatile uint32_t* cntSamples,volatile bool* repCh0,volatile bool* autostart);

void getBackup(volatile uint32_t* cntSamples,volatile bool* repCh0,volatile bool* autostart);

void getTimerReset(void);

void get_initial_state(void);
static inline void TimReset(void){
	TIMER_CREP(SMP_TIMER) = (uint16_t) 0x00U; 
	TIMER_CAR(SMP_TIMER) = (uint16_t) 0x01U;
}
