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
		 print("Autostart enable\n\r");
	}
	else{
		 status_gen(0, FALSE);
		 print("Autostart disable\n\r");
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
				 print("Set autostart\n\r");
				 getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
				 detCmd = undef;
				 break;
				 
				 case reset_autostart:
				 autostartCh0 = FALSE;
				 print("Reset autostart\n\r");
				 getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
				 detCmd = undef;
				 break;
				 
				 case start_load:
					 if(parity==0xFF){//First byte of packet
							parity = recData;
							if(parity == 0x00){
								 GPIO_OCTL(GPIOB)&=~(1U<<12);
							}
							else{
								 GPIO_OCTL(GPIOB)|=(1U<<12);
							}
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
				 
				 case get_info:
						 if(recData == 0x00){ //For terminal
							 print("Generator v 0.2 2022-03-15\n\r");
							 if(countSampleCh0 == 0){
									 print("Generator don't have samples\n\r");
							 } 
							 
							 if(repeat_ch0){
									print("Repeat enable\n\r");
							 }
							 else{
									print("Repeat disable\n\r");
							 }
							 
							 if(autostartCh0){
								 print("Autostart enable\n\r");
							 }
							 else{
									print("Autostart disable\n\r");
							 }
						 }
						 else{  //For GUI
							 char arrayGui[4];
							 if(repeat_ch0){
									arrayGui[0] = '1';
							 }
							 else{
									arrayGui[0] = '0';
							 }
							 
							 if(autostartCh0){
								 arrayGui[1] = '1';
							 }
							 else{
									arrayGui[1] = '0';
							 }
							 
							 arrayGui[2] = 0x0D;
							 arrayGui[3] = 0x0A;
							 
							 print(arrayGui);
						 }
						 detCmd = undef;
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
