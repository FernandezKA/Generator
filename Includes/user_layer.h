#pragma once
#include "main.h"
#include "system_layer.h"
#include "periph_layer.h"

extern uint16_t arrayCh0[64U];  //Temp array for page of flash
extern uint16_t countBlocks;	  //This variable show aviable page of samples

extern uint16_t indexCh0; 

extern uint16_t recTime;
extern bool msb_received;

uint16_t GetSample(uint16_t currIndex);

void ReceiveSample(uint8_t time_part);

