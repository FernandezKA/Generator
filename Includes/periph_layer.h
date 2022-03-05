#pragma once

#include "main.h"

//Definitions block
#define USART_PC USART0

#define GPIO_LED (1U << 13)
#define GPIO_CH0 (1U << 12)
#define GPIO_CH1 (1U << 13)


void CLK_Init(void);

void GPIO_Init(void);

void TIMERS_Init(void);

void USART_Init(void);

void StartGenCh0(void);

void StopGenCh0(void);

void FlashErase(uint32_t* pAddr);

void FlashWrite(uint32_t* pAddr, uint32_t* data);

uint32_t FlashRead(uint32_t* pAddr);

void GPIO_CH0_STATE(bool state);

void IRQ_Enable(void);
