#include "periph_layer.h"


void CLK_Init(void){
	RCU_APB2EN |= RCU_APB2EN_USART0EN;
	RCU_APB2EN |= RCU_APB2EN_PAEN;
	RCU_APB2EN |= RCU_APB2EN_PCEN;
	RCU_APB1EN |= RCU_APB1EN_TIMER1EN;
}

void GPIO_Init(void){
	//This gpio used for USART_PC
	gpio_afio_deinit();
	gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9); //PA9 as TX
	gpio_init(GPIOA, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, GPIO_PIN_10);  //PA10 as RX
	//This gpio used for led indicated
	gpio_init(GPIOC, GPIO_MODE_OUT_OD, GPIO_OSPEED_10MHZ, GPIO_PIN_13);
	
}

void TIMERS_Init(void){
	//TODO: ADD timer for led indicate
	
	//Timer for CH1
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
	 TIMER_CTL0(TIMER1)|=TIMER_CTL0_CEN;
}

void StopGenCh0(void){
	 TIMER_CTL0(TIMER1)&=~TIMER_CTL0_CEN;
}

void FlashErase(uint32_t* pAddr){
	 FMC_KEY0 = 0x45670123;
	 FMC_KEY0 = 0xCDEF89AB;
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
	 FMC_CTL0|= FMC_CTL0_PER;
	 FMC_ADDR0 = (uint32_t) pAddr;
	 FMC_CTL0|=FMC_CTL0_START;
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
}

void FlashWrite(uint32_t* pAddr, uint16_t* data){
	 FMC_KEY0 = 0x45670123;
	 FMC_KEY0 = 0xCDEF89AB;
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
	 FMC_CTL0|=FMC_CTL0_PG;
	 for(uint8_t i = 0; i < 0x40U; ++i){
		 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
		 *((uint32_t*) (pAddr + i * sizeof(uint16_t))) = *(data + i);
	 }
	 while((FMC_STAT0 & FMC_STAT0_BUSY) == FMC_STAT0_BUSY){__NOP();}//Wait while flash is busy
	 return;
}

uint16_t FlashHalfRead(uint32_t* pAddr){
	return (uint16_t) *(pAddr);
}

uint32_t FlashWordRead(uint32_t* pAddr){
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
	nvic_irq_enable(USART0_IRQn, 2, 1); // For UART0_PC
	nvic_irq_enable(TIMER1_IRQn, 2, 2);
}
