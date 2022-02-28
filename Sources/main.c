#include "main.h"

//User variable declaration
FIFO RS232_RX;

bool GenerateCh0;
bool RepeatCh0;
bool LoadCh0;

bool GenerateCh1;
bool RepeatCh1;
bool LoadCh1;

bool GenerateCh2;
bool RepeatCh2;
bool LoadCh2;

bool GenerateCh3;
bool RepeatCh3;
bool LoadCh3;


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
						switch(currChannel){
							 case Ch0:
								 
							 break;
							 case Ch1:
								 
							 break;
							 case Ch2:
								 
							 break;
							 case Ch3:
								
							 break;
						}
					case startGeneraion:
						
					switch(currChannel){
							 case Ch0:
								 
							 break;
							 case Ch1:
								 
							 break;
							 case Ch2:
								 
							 break;
							 case Ch3:
								
							 break;
						}
					
					case repeatGeneration:
					switch(currChannel){
							 case Ch0:
								 
							 break;
							 case Ch1:
								 
							 break;
							 case Ch2:
								 
							 break;
							 case Ch3:
								
							 break;
						}
					break;
						
					case setAutostart:
						switch(currChannel){
							 case Ch0:
								 
							 break;
							 case Ch1:
								 
							 break;
							 case Ch2:
								 
							 break;
							 case Ch3:
								
							 break;
						}
						break;
					case resetAutostart:
						switch(currChannel){
							 case Ch0:
								 
							 break;
							 case Ch1:
								 
							 break;
							 case Ch2:
								 
							 break;
							 case Ch3:
								
							 break;
						}
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
						break;
					case stopLoad:
						switch(currChannel){
							 case Ch0:
								 
							 break;
							 case Ch1:
								 
							 break;
							 case Ch2:
								 
							 break;
							 case Ch3:
								
							 break;
						}
						break;
					case undefined:
							__NOP();
					break;
					
				}
			}
		}
	}
}

static inline void SysInit(void){
	
}
