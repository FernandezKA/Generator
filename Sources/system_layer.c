#include "system_layer.h"
#include "user_layer.h"

uint32_t* pBeginCh0 = (uint32_t*) 0x08008000;  //Page 32
uint32_t* pEndCh0 = 	(uint32_t*) 0x08010000;  //Page 64
bool repeat_ch0 = FALSE;
uint8_t parity = 0xFF;
uint32_t samplesCh0[32U];

uint32_t currSampleCh0 = 0;
uint32_t countSampleCh0 = 0;

struct fifo RS232_RX;

//IRQ handlers
void USART_RX_Handler(uint32_t data){
	Push(&RS232_RX, (uint8_t) data);
}

void TIM1_Handler(void){
	 if(currSampleCh0 < countSampleCh0 - 1 && countSampleCh0 != 0){
			TIMER_CREP(TIMER1) = (uint16_t) ((GetSample(currSampleCh0++, pBeginCh0) & 0xFFFF0000)>>16); 
			TIMER_CAR(TIMER1) = (uint16_t) (GetSample(currSampleCh0, pBeginCh0) & 0xFFFF);
			//GPIO_CH0_STATE((currSampleCh0%parity) == 0x00);
		  TIMER_CTL0(TIMER1)|=TIMER_CTL0_CEN;
	 }
	 else if(countSampleCh0 - 1 == currSampleCh0 && countSampleCh0 != 0){
		 if(repeat_ch0){
				TIMER_CREP(TIMER1) = (uint16_t) ((GetSample(currSampleCh0++, pBeginCh0) & 0xFFFF0000)>>16); 
				TIMER_CAR(TIMER1) = (uint16_t) (GetSample(currSampleCh0, pBeginCh0) & 0xFFFF);
				currSampleCh0 = 0;
				TIMER_CTL0(TIMER1)|=TIMER_CTL0_CEN;
		 }
		 else{
			 currSampleCh0 = 0;
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

 
 void AddSample(uint32_t sample){
	 if(countSampleCh0%0x20 == 0 && countSampleCh0 != 0){ //Get backup,if we receive one page of data
		 //FlashErase((uint32_t) pBeginCh0 + countSampleCh0*sizeof(uint32_t));
		 FlashWrite((uint32_t) pBeginCh0 + countSampleCh0*sizeof(uint32_t) - 0x80, samplesCh0);
		 ++countSampleCh0;
	 }
	 else{
		samplesCh0[(countSampleCh0++)%0x20] = sample;
	 }
 }
 
 bool status_repeat(uint8_t channel, bool state){
	bool status = FALSE;
	switch(channel){
		case 0x00:
			repeat_ch0 = state;
			status = TRUE;
		break;
		default:
			status = FALSE;
		break;
	}		
	return status;
 }
 
