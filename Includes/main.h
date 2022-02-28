#pragma once
#include <stdint.h>
//#include <stdbool.h>

#include "gd32f10x.h"
#include "gd32f10x_usart.h"
#include "gd32f10x_gpio.h"
#include "gd32f10x_timer.h"

//User includes
#include "fifo.h"
#include "communication.h"

extern struct fifo RS232_RX;

extern bool GenerateCh0;
extern bool RepeatCh0;
extern bool LoadCh0;

extern bool GenerateCh1;
extern bool RepeatCh1;
extern bool LoadCh1;

extern bool GenerateCh2;
extern bool RepeatCh2;
extern bool LoadCh2;

extern bool GenerateCh3;
extern bool RepeatCh3;
extern bool LoadCh3;

enum Channel {
Ch0,
Ch1, 
Ch2, 
Ch3
};

extern enum Channel currChannel;



