#include "GenTable.h"

// User variables
Pulse Ch0_array[CH0_SIZE];
Pulse Ch1_array[CH1_SIZE];
Pulse Ch2_array[CH2_SIZE];
Pulse Ch3_array[CH3_SIZE];
// This variables used for load data pair into array
uint16_t countCh0 = 0;
uint16_t countCh1 = 0;
uint16_t countCh2 = 0;
uint16_t countCh3 = 0;
// This variables used for generate data timings, and navigate at array of pair
uint16_t pCh0 = 0;
uint16_t pCh1 = 0;
uint16_t pCh2 = 0;
uint16_t pCh3 = 0;

void AddPair(bool cState, uint16_t cTime, uint8_t ch)
{
	if (ch == 0)
	{
		if (countCh0 == CH0_SIZE)
		{
			countCh0 = 0;
		}
		Ch0_array[countCh0].state = cState;
		Ch0_array[countCh0++].time = cTime;
	}
	else if (ch == 1)
	{
		if (countCh1 == CH1_SIZE)
		{
			countCh1 = 0;
		}
		Ch1_array[countCh1].state = cState;
		Ch1_array[countCh1++].time = cTime;
	}
	else if (ch == 2)
	{
		if (countCh2 == CH2_SIZE)
		{
			countCh2 = 0;
		}
		Ch2_array[countCh2].state = cState;
		Ch2_array[countCh2++].time = cTime;
	}
	else if (ch == 3)
	{
		if (countCh3 == CH3_SIZE)
		{
			countCh3 = 0;
		}
		Ch3_array[countCh3].state = cState;
		Ch3_array[countCh3++].time = cTime;
	}
	else
	{
		print("Undefined behavioral\n\r");
	}
}
