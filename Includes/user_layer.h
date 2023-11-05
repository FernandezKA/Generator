#pragma once
#include "main.h"
#include "system_layer.h"
#include "periph_layer.h"

extern uint32_t indexCh0; 
extern uint32_t recTime;
extern uint8_t part_received;

#define STOP_TIME 0x00000000

uint32_t GetSample(uint32_t currIndex, uint32_t* pTable);

bool ReceiveSample(uint8_t time_part);

void print(char* pMsg);
