#pragma once
#include "fifo.h"

extern uint32_t* pBeginCh0;
extern uint32_t* pEndCh0;

extern uint32_t currSampleCh0;
extern uint32_t countSampleCh0;
extern uint32_t samplesCh0[32U];

extern bool repeatCh0;

extern struct fifo RS232_RX;

extern bool repeat_ch0;
extern uint8_t parity;

void USART_RX_Handler(uint32_t data);

void TIM0_Handler(void);

bool status_gen(uint8_t channel, bool state);

void AddSample(uint32_t sample);

bool status_repeat(uint8_t channel, bool state);
