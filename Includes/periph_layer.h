#pragma once

#include "main.h"

//Definitions block
#define USART_PC USART0

void CLK_Init(void);

void GPIO_Init(void);

void TIMERS_Init(void);

void USART_Init(void);

void StartGenCh0(void);

void StopGenCh0(void);

void FlashErase(uint32_t* pAddr);

void FlashWrite(uint32_t* pAddr, uint16_t* data);

uint16_t FlashHalfRead(uint32_t* pAddr);

uint32_t FlashWordRead(uint32_t* pAddr);
