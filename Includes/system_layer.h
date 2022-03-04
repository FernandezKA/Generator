#pragma once
#include "fifo.h"

extern uint32_t pBeginCh0;
extern uint32_t pEndCh0;

extern struct fifo RS232_RX;

void USART_RX_Handler(uint32_t data);

void TIM1_Handler(void);

bool status_gen(uint8_t channel, bool state);


