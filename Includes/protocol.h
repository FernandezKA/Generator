#pragma once 

#include "main.h"

enum command {
	undef = 0,
	start,
	stop, 
	set_repeat,  
	reset_repeat, 
	set_autostart, 
	reset_autostart, 
	start_load
};

enum command DetectCommand(uint8_t data);
