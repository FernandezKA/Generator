#include "main.h"
//This function make timer1 initializing
void Tim1_Init(void){
	timer_deinit(TIMER1);
	timer_parameter_struct Tim1;
	Tim1.prescaler = 10700U;
	Tim1.alignedmode = TIMER_COUNTER_EDGE;
	Tim1.counterdirection = TIMER_COUNTER_UP;
	Tim1.clockdivision = TIMER_CKDIV_DIV1;
	Tim1.repetitioncounter = 0U;
	timer_struct_para_init(&Tim1);
}
