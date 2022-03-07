#include "main.h"
#include "periph_layer.h"
#include "system_layer.h"
#include "user_layer.h"
#include "protocol.h"

static inline void SysInit(void);

int main(){
	SysInit();
	getRestore(&countSampleCh0, &repeat_ch0, &autostartCh0);
	if(autostartCh0){
		 status_gen(0, TRUE);
	}
	else{
		 status_gen(0, FALSE);
	}
	print("Generator v 0.1 2022-03-04\n\r");
	enum command detCmd = undef;
	 for(;;){
		 if(GetSize(&RS232_RX) != 0){
			 uint8_t recData = Pull(&RS232_RX);
			 switch(detCmd){
				 case undef:
					 detCmd = DetectCommand(recData);
					 if(detCmd == start_load){
						 countSampleCh0 = 0;//Reset all data for new samples
						 currSampleCh0 = 0;
						 parity=0xFF;
						 status_gen(recData, FALSE);
					 }
				 break;
				 
				 case start:
					 status_gen(recData, TRUE);
					 print("Start generation\n\r");
					 detCmd = undef;
				 break;
				 
				 case stop:
					 status_gen(recData, FALSE);
					 print("Stop generation\n\r");
					 detCmd = undef;				 				 
				 break;
				 
				 case set_repeat:
					 status_repeat(recData, TRUE);
					 print("Reapeat flag set\n\r");
					 getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
					 detCmd = undef;
				 break;
				 
				 case reset_repeat:
					 status_repeat(recData, FALSE);
					 print("Repeat flag reset\n\r");
					getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
					 detCmd = undef;
				 break;
				 
				 case set_autostart:
					 autostartCh0 = TRUE;
					getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
				 break;
				 
				 case reset_autostart:
					 autostartCh0 = FALSE;
					 getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
				 break;
				 
				 case start_load:
					 if(parity==0xFF){//First byte of packet
							parity = recData;
						  FlashErase((uint32_t) pBeginCh0 - countSampleCh0%0x20);
						  countSampleCh0 = 0;
						  print("Pulse state is selected\n\r");
					 }
					 else{
					 if(ReceiveSample(recData)){  //Detect stop only for full time added
						if(recTime == (uint32_t) 0UL){
							if(countSampleCh0 < 0x20){
								FlashWrite((uint32_t) pBeginCh0, samplesCh0);
							}
							else{
								FlashWrite((uint32_t) pBeginCh0 + ((countSampleCh0/0x20))*0x20*sizeof(uint32_t), &samplesCh0[0]);
							}

								getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
								print("Load is ended\n\r");
								detCmd = undef;
						}
					 }
				 }
				 break;
			 }
		 }
	 }
}


static inline void SysInit(void){
	 CLK_Init();
	 GPIO_Init();
	 TIMERS_Init();
	 USART_Init();
	 IRQ_Enable();
}
