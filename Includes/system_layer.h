#pragma once

#include "fifo.h"

extern struct fifo RS232_RX;

void USART_RX_Handler(uint32_t data);

void TIM1_Handler(void);
