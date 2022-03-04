#include "main.h"
#include "periph_layer.h"
#include "system_layer.h"
#include "user_layer.h"
#include "protocol.h"

static inline void SysInit(void);

int main(){
	SysInit();
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
				 break;
				 
				 case stop:
					 status_gen(recData, FALSE);
				 break;
				 
				 case set_repeat:
					 
				 break;
				 
				 case reset_repeat:
					 
				 break;
				 
				 case set_autostart:
					 
				 break;
				 
				 case reset_autostart:
					 
				 break;
				 
				 case start_load:
					 
				 break;
				 
				 case stop_load:
					 
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
}
