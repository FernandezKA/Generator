#pragma once
#include "main.h"
#include "communication.h"
#define CH0_SIZE 64U
#define CH1_SIZE 64U
#define CH2_SIZE 4U
#define CH3_SIZE 4U

// User type definition
struct pulse
{
	bool state;
	uint16_t time;
};

typedef struct pulse Pulse;

// User variables
extern Pulse Ch0_array[CH0_SIZE];
extern Pulse Ch1_array[CH1_SIZE];
extern Pulse Ch2_array[CH2_SIZE];
extern Pulse Ch3_array[CH3_SIZE];

extern uint16_t countCh0;
extern uint16_t countCh1;
extern uint16_t countCh2;
extern uint16_t countCh3;

extern uint16_t pCh0;
extern uint16_t pCh1;
extern uint16_t pCh2;
extern uint16_t pCh3;

void AddPair(bool cState, uint16_t cTime, uint8_t ch);
// User function definition
