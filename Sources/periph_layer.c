#include "periph_layer.h"


void CLK_Init(void){
	//RCU_APB2EN |= RCU_APB2EN_USART0EN;
	RCU_APB2EN |= RCU_APB2EN_PAEN | RCU_APB2EN_PBEN | RCU_APB2EN_PCEN;
	RCU_APB1EN |= RCU_APB1EN_TIMER1EN;
	RCU_APB2EN |= RCU_APB2EN_TIMER0EN;
	rcu_periph_clock_enable(RCU_USBD);
	rcu_ckout0_config(RCU_CKOUT0SRC_CKSYS);
	rcu_usb_clock_config(RCU_CKUSB_CKPLL_DIV1_5);
}

void GPIO_Init(void){
	//This gpio used for USART_PC
	gpio_afio_deinit();
	//gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9); //PA9 as TX
	//gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);  //PA10 as RX
	
	//This gpio used for led indicated
	gpio_init(GPIOC, GPIO_MODE_OUT_OD, GPIO_OSPEED_10MHZ, GPIO_PIN_13);
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11);  //usb
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);  //usb
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_8); //CLK OUT
	//Used for generation
	gpio_init(GPIOB, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_12);
}

void TIMERS_Init(void){
	//TODO: ADD timer for led indicate
	
	//Timer for CH1
	timer_deinit(SMP_TIMER);
	timer_parameter_struct tim0;
	tim0.prescaler = 719; // 10uS for each step
	tim0.alignedmode = TIMER_COUNTER_EDGE;
	tim0.counterdirection = TIMER_COUNTER_UP;
	tim0.period = 9;
	timer_init(SMP_TIMER, &tim0);
	timer_interrupt_enable(SMP_TIMER, TIMER_INT_UP); // Interrrupt at overflow
	TIMER_CTL0(SMP_TIMER)|=TIMER_CTL0_SPM;
	
	timer_deinit(LED_TIMER);
	timer_parameter_struct tim1;
	tim1.prescaler = 0xFFFF; // 10uS for each step
	tim1.alignedmode = TIMER_COUNTER_EDGE;
	tim1.counterdirection = TIMER_COUNTER_UP;
	tim1.period = 500;
	timer_init(LED_TIMER, &tim1);
	timer_interrupt_enable(LED_TIMER, TIMER_INT_UP); // Interrrupt at overflow
	timer_enable(LED_TIMER);
}

void USART_Init(void){
	usart_deinit(USART_PC);
	usart_baudrate_set(USART_PC, 115200UL);
	usart_parity_config(USART_PC, USART_PM_NONE);
	usart_transmit_config(USART_PC, USART_TRANSMIT_ENABLE);
	usart_receive_config(USART_PC, USART_RECEIVE_ENABLE);
	// usart_interrupt_enable(USART0, USART_INT_TBE);
	usart_interrupt_enable(USART_PC, USART_INT_RBNE);
	usart_enable(USART_PC);
}

void StartGenCh0(void){
	 TIMER_CTL0(SMP_TIMER)|=TIMER_CTL0_CEN;
}

void StopGenCh0(void){
	 TIMER_CTL0(SMP_TIMER)&=~TIMER_CTL0_CEN;
}

void FlashErase(uint32_t pAddr){
	 FMC_KEY0 = 0x45670123;
	 FMC_KEY0 = 0xCDEF89AB;
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
	 FMC_CTL0|= FMC_CTL0_PER;
	 FMC_ADDR0 = (uint32_t) pAddr;
	 FMC_CTL0|=FMC_CTL0_START;
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
}

void FlashWrite(uint32_t pAddr, uint32_t* data){
	 FMC_KEY0 = 0x45670123;
	 FMC_KEY0 = 0xCDEF89AB;
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
	 FMC_CTL0|=FMC_CTL0_PG;
	 for(uint8_t i = 0; i < 32; ++i){
		 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
		 *((uint32_t*)(pAddr + i * sizeof(uint32_t))) = data[i];
	 }
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
	 FMC_CTL0&=~FMC_CTL0_PG;
	 FMC_CTL0&=~FMC_CTL0_LK;
	 return;
}

uint32_t FlashRead(uint32_t* pAddr){
	return (uint32_t) *pAddr;
}

void GPIO_CH0_STATE(bool state){
	if(state){
		GPIO_OCTL(GPIOB)|=GPIO_CH0;
	}
	else{
		GPIO_OCTL(GPIOB)&=~GPIO_CH0;
	}
}

void IRQ_Enable(void){
	#ifdef USART
	nvic_irq_enable(USART0_IRQn, 2, 1); // For UART0_PC
	#else 
	nvic_priority_group_set(NVIC_PRIGROUP_PRE1_SUB3);
	nvic_irq_enable(USBD_LP_CAN0_RX0_IRQn, 1, 0);
	#endif
	nvic_irq_enable(TIMER1_IRQn, 3, 3);
	nvic_irq_enable(TIMER0_UP_IRQn, 2, 2);
}
