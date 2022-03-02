#pragma once

#include "main.h"
#include "uart.h"
#include "GenTable.h"

enum Command{
	undefined = 0, 
	stopGeneration, 
	startGeneraion, 
	repeatGeneration, 
	setAutostart, 
	resetAutostart, 
	setChNum, 
	startLoad, 
	stopLoad
};

enum PairReceive{
wait_state,
wait_MSB, 
wait_LSB, 
complete
};

extern enum PairReceive pairState;

void print(char* pMsg);

enum Command GetCommand(unsigned char recData);

bool ReceivePair(struct pulse* cPulse, enum PairReceive* cPairState, unsigned char data);
