#include "main.h"
// This function make timer1 initializing
void Tim1_Init(void)
{
	RCU_APB1EN |= RCU_APB1EN_TIMER1EN;
	timer_deinit(TIMER1);
	timer_deinit(TIMER1);
	timer_parameter_struct tim1;
	tim1.prescaler = 107; // 0.01 mS for each step
	tim1.alignedmode = TIMER_COUNTER_EDGE;
	tim1.counterdirection = TIMER_COUNTER_UP;
	tim1.period = 9; // About 0.81 sec per UIF IRQ
	timer_init(TIMER1, &tim1);
	timer_interrupt_enable(TIMER1, TIMER_INT_UP); // Interrrupt at overflow
	timer_enable(TIMER1);
}
