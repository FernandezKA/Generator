#pragma once
#include "fifo.h"

extern uint32_t* pInfo;
extern uint32_t* pBeginCh0;
extern uint32_t* pEndCh0;

extern uint32_t currSampleCh0;
extern uint32_t countSampleCh0;
extern uint32_t samplesCh0[32U];
extern bool 		autostartCh0;


extern struct fifo RS232_RX;
extern struct fifo RS232_TX;

extern bool repeat_ch0;
extern uint8_t parity;

void USART_RX_Handler(uint32_t data);

void TIM0_Handler(void);

bool status_gen(uint8_t channel, bool state);

void AddSample(uint32_t sample);

bool status_repeat(uint8_t channel, bool state);

void getRestore(uint32_t* cntSamples, bool* repCh0, bool* autostart);

void getBackup(uint32_t* cntSamples, bool* repCh0, bool* autostart);
