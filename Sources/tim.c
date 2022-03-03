#include "main.h"
// This function make timer1 initializing
void Tim1_Init(void)
{
	RCU_APB1EN |= RCU_APB1EN_TIMER1EN;
	timer_deinit(TIMER1);
	timer_parameter_struct tim1;
	tim1.prescaler = 999; // 10uS for each step
	tim1.alignedmode = TIMER_COUNTER_EDGE;
	tim1.counterdirection = TIMER_COUNTER_UP;
	tim1.period = 10;
	timer_init(TIMER1, &tim1);
	timer_interrupt_enable(TIMER1, TIMER_INT_UP); // Interrrupt at overflow
	TIMER_CTL0(TIMER1)|=TIMER_CTL0_SPM;
	timer_enable(TIMER1);
}
