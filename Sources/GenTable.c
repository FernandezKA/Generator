#include "GenTable.h"

//User variables
Pulse Ch0_array[CH0_SIZE];
Pulse Ch1_array[CH1_SIZE];
Pulse Ch2_array[CH2_SIZE];
Pulse Ch3_array[CH3_SIZE];
//This variables used for load data pair into array
uint16_t countCh0 = 0;
uint16_t countCh1 = 0;
uint16_t countCh2 = 0; 
uint16_t countCh3 = 0;
//This variables used for generate data timings, and navigate at array of pair
uint16_t pCh0 = 0;
uint16_t pCh1 = 0;
uint16_t pCh2 = 0;
uint16_t pCh3 = 0;


void AddPair(bool cState, uint16_t cTime, enum Channel* ch){
	 if(*ch == Ch0) {
		 Ch0_array[pCh0++].state = cState;
		 Ch0_array[pCh0].time = cTime;
	 }
	 else if(*ch == Ch1){
		 Ch1_array[pCh1++].state = cState;
		 Ch1_array[pCh1].time = cTime;		 
	 }
	 else if(*ch == Ch2){
		 Ch2_array[pCh2++].state = cState;
		 Ch2_array[pCh2].time = cTime;
	 }
	 else if(*ch == Ch3){
		 Ch3_array[pCh3++].state = cState;
		 Ch3_array[pCh3].time = cTime;
	 }
	 else{
			print("Undefined behavioral\n\r");
	 }
}

