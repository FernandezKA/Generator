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
	 if(currSampleCh0 < countSampleCh0){
			TIMER_CAR(TIMER1) = GetSample(currSampleCh0++, &samplesCh0[0]);
			//GPIO_CH0_STATE((currSampleCh0%parity) == 0x00);
		  TIMER_CTL0(TIMER1)|=TIMER_CTL0_CEN;
	 }
	 else if(countSampleCh0 != 0){
		 if(repeat_ch0){
				currSampleCh0 = 0;
				TIMER_CAR(TIMER1) = (uint16_t) GetSample(
				TIMER_CREP(TIMER1) = (uint16_t) (GetSample(currSampleCh0++, &samplesCh0[0]) & 0xFFFF);
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
	 if(countSampleCh0%31U == 0){
		 FlashErase(pBeginCh0 + countSampleCh0);
		 FlashWrite(pBeginCh0 + countSampleCh0 - 31U, samplesCh0);
		 ++countSampleCh0;
	 }
	samplesCh0[(countSampleCh0++)%31U] = sample;
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
 
