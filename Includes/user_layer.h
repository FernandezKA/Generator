#pragma once
#include "main.h"
#include "system_layer.h"
#include "periph_layer.h"

extern uint16_t indexCh0; 
extern uint16_t recTime;
extern bool msb_received;

#define STOP_TIME 0x0000

uint16_t GetSample(uint16_t currIndex);

bool ReceiveSample(uint8_t time_part);

void print(char* pMsg);
