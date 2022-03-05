#include "main.h"
#include "periph_layer.h"
#include "system_layer.h"
#include "user_layer.h"
#include "protocol.h"

static inline void SysInit(void);

int main(){
	SysInit();
	print("Generator v 0.1 2022-03-04\n\r");
	enum command detCmd = undef;
	 for(;;){
		 if(GetSize(&RS232_RX) != 0){
			 uint8_t recData = Pull(&RS232_RX);
			 switch(detCmd){
				 case undef:
					 detCmd = DetectCommand(recData);
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
					 print("Reapeat set\n\r");
					 detCmd = undef;
				 break;
				 
				 case reset_repeat:
					 status_repeat(recData, FALSE);
					 print("Repeat resaet\n\r");
					 detCmd = undef;
				 break;
				 
				 case set_autostart:
					 __NOP();
				 break;
				 
				 case reset_autostart:
					 __NOP();
				 break;
				 
				 case start_load:
					 if(parity==0xFF){//First byte of packet
							parity = recData;
						  print("Pulse state is selected\n\r");
					 }
					 else{
					 if(ReceiveSample(recData)){  //Detect stop only for full time added
						if(recTime == STOP_TIME){
								print("Load ended\n\r");
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
