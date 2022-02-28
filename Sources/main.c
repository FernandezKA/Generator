#include "main.h"

//User variable declaration
FIFO RS232_RX;

bool GenerateCh0;
bool RepeatCh0;
bool LoadCh0;
bool autostartCh0;

bool GenerateCh1;
bool RepeatCh1;
bool LoadCh1;
bool autostartCh1;

bool GenerateCh2;
bool RepeatCh2;
bool LoadCh2;
bool autostartCh2;

bool GenerateCh3;
bool RepeatCh3;
bool LoadCh3;
bool autostartCh3;

enum Channel currChannel;

static inline void SysInit(void);

int main(){
	SysInit();
	enum Command currCommand = undefined;
	for(;;){
		if(GetSize(&RS232_RX)!= 0){
			if(currCommand == undefined){
				currCommand = GetCommand(Pull(&RS232_RX));
			}
			else{
				switch(currCommand){
					
					
					case stopGeneration:
						Pull(&RS232_RX);
						switch(currChannel){
							 case Ch0:
								 GenerateCh0 = FALSE;
							 break;
							 case Ch1:
								 GenerateCh1 = FALSE;
							 break;
							 case Ch2:
								 GenerateCh2 = FALSE;
							 break;
							 case Ch3:
								 GenerateCh3 = FALSE;
							 break;
						}
						currCommand = undefined;
					break;
						
						
					case startGeneraion:
						Pull(&RS232_RX);
					switch(currChannel){
							 case Ch0:
									GenerateCh0 = TRUE;
							 break;
							 case Ch1:
									GenerateCh1 = TRUE;
							 break;
							 case Ch2:
								  GenerateCh2 = TRUE;
							 break;
							 case Ch3:
								 GenerateCh3 = TRUE;
							 break;
						}
					currCommand = undefined;
					break;
					
						
					case repeatGeneration:
						Pull(&RS232_RX);
					switch(currChannel){
							 case Ch0:
								 RepeatCh0 = TRUE;
							 break;
							 case Ch1:
								 RepeatCh1 = TRUE;
							 break;
							 case Ch2:
								 RepeatCh2 = TRUE;
							 break;
							 case Ch3:
								 RepeatCh3 = TRUE;
							 break;
						}
					currCommand = undefined;
					break;
						
						
					case setAutostart:
						Pull(&RS232_RX);
						switch(currChannel){
							 case Ch0:
								 autostartCh0 = TRUE;
							 break;
							 case Ch1:
								 autostartCh1 = TRUE;
							 break;
							 case Ch2:
									autostartCh2 = TRUE;
							 break;
							 case Ch3:
								 autostartCh3 = TRUE;
							 break;
						}
						currCommand = undefined;
						break;
						
						
					case resetAutostart:
						Pull(&RS232_RX);
						switch(currChannel){
							 case Ch0:
								 autostartCh0 = FALSE;
							 break;
							 case Ch1:
								 autostartCh1 = FALSE;
							 break;
							 case Ch2:
								 autostartCh2 = FALSE;
							 break;
							 case Ch3:
								 autostartCh3 = FALSE;
							 break;
						}
						currCommand = undefined;
						break;
						
						
					case setChNum:
						currChannel = Pull(&RS232_RX);
					break;
					case startLoad:
						switch(currChannel){
							 case Ch0:
								 LoadCh0 = TRUE; 
								 LoadCh1 = FALSE;
								 LoadCh2 = FALSE;
								 LoadCh3 = FALSE;
							 break;
							 case Ch1:
								 LoadCh0 = FALSE; 
								 LoadCh1 = TRUE;
								 LoadCh2 = FALSE;
								 LoadCh3 = FALSE;
							 break;
							 case Ch2:
								 LoadCh0 = FALSE; 
								 LoadCh1 = FALSE;
								 LoadCh2 = TRUE;
								 LoadCh3 = FALSE;
							 break;
							 case Ch3:
								 LoadCh0 = FALSE; 
								 LoadCh1 = FALSE;
								 LoadCh2 = FALSE;
								 LoadCh3 = TRUE;
							 break;
						}
						currCommand = undefined;
						break;
						
						
					case stopLoad:
						Pull(&RS232_RX);
						switch(currChannel){
							 case Ch0:
								 LoadCh0 = FALSE;
							 break;
							 case Ch1:
								 LoadCh1 = FALSE;
							 break;
							 case Ch2:
								 LoadCh2 = FALSE;
							 break;
							 case Ch3:
								 LoadCh3 = FALSE;
							 break;
						}
						currCommand = undefined;
						break;
						
						
					case undefined:
						Pull(&RS232_RX);
						__NOP();
					break;
					
				}
			}
		}
	}
}

static inline void SysInit(void){
	Tim1_Init();
}
