#pragma once

#include "main.h"
#include "uart.h"

enum Command{
	undefined, 
	stopGeneration, 
	startGeneraion, 
	repeatGeneration, 
	setAutostart, 
	resetAutostart, 
	setChNum, 
	startLoad, 
	stopLoad
};


void print(unsigned char* pMsg);

enum Command GetCommand(unsigned char recData);
