#include "protocol.h"

enum command DetectCommand(uint8_t data){
	enum command recCmd = undef;
	switch(data){
		case 0x01:
			 recCmd = start;
		break;
		
		case 0x02:
			 recCmd = stop;
		break;
		
		case 0x03:
			 recCmd = set_repeat;
		break;
		
		case 0x04:
			 recCmd = reset_repeat;
		break;
		
		case 0x05:
			 recCmd = set_autostart;
		break;
		
		case 0x06:
			 recCmd = reset_autostart;
		break;
		
		case 0x07: 
			 recCmd = start_load;
		break;
		
		default:
			 recCmd = undef;
		break;
	}
	return recCmd;
}
