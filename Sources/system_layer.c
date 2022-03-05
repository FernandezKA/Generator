#include "system_layer.h"
#include "user_layer.h"

uint32_t* pBeginCh0 = (uint32_t*) 0x1FFF0000;
uint32_t* pEndCh0 = 	(uint32_t*) 0x1FFF77FF;
bool repeat_ch0 = FALSE;
uint8_t parity = 0xFF;
uint16_t samplesCh0[64U];

uint16_t currSampleCh0 = 0;
uint16_t countSampleCh0 = 0;

bool repeatCh0 = TRUE;

struct fifo RS232_RX;

//IRQ handlers
void USART_RX_Handler(uint32_t data){
	Push(&RS232_RX, (uint8_t) data);
}

void TIM1_Handler(void){
	 if(currSampleCh0 < countSampleCh0){
			TIMER_CAR(TIMER1) = GetSample(currSampleCh0++);
			GPIO_CH0_STATE((currSampleCh0%parity) == 0x00);
	 }
	 else{
		 if(repeat_ch0){
				currSampleCh0 = 0;
		 }
		 else{
			 StopGenCh0(); 
		 }
	 }
}

bool status_gen(uint8_t channel, bool state){
	bool status = FALSE;
	 switch(channel){
		 case 0:
			 if(state){
					TIMER_CTL0(TIMER1)|= TIMER_CTL0_CEN;
			 }
			 else{
				 TIMER_CTL0(TIMER0)&=~TIMER_CTL0_CEN;
			 }
			 status = TRUE;
		 break;
		 
		 default:
			 status = FALSE;
		 break;
	 }
	 return status;
}

 
 void AddSample(uint16_t sample){
	 if(countSampleCh0 == 64U){
		 //TODO: goto the next page
		 countSampleCh0 = 0;
	 }
	samplesCh0[countSampleCh0++] = sample;
 }
 
 bool status_repeat(uint8_t channel, bool state){
	 bool status = FALSE;
	switch(channel){
		case 0x00:
			repeatCh0 = state;
			status = TRUE;
		break;
		default:
			status = FALSE;
		break;
	}		
	return status;
 }
 
