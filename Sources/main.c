#include "main.h"

// User variable declaration
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
static inline void GpioInit(void);

int main()
{
	SysInit();
	nvic_irq_enable(USART0_IRQn, 1, 1);	   // For UART0_PC
	nvic_irq_enable(TIMER1_IRQn, 2, 2);	   // For led indicate activity
	struct pulse curPulse;
	enum PairReceive curPairState;
	enum Command currCommand = undefined;
	for (;;)
	{
		if (GetSize(&RS232_RX) != 0) // Check RS232_RX buffer size
		{
			if (currCommand == undefined)
			{
				currCommand = GetCommand(Pull(&RS232_RX));
			}
			else // We go to this case only for next received byte
			{
				uint8_t recData = Pull(&RS232_RX); // Get data from rx_buff
				switch (currCommand)
				{
				case stopGeneration:
					switch (recData)
					{
					case 0x00:
						GenerateCh0 = FALSE;
						break;
					case 0x01:
						GenerateCh1 = FALSE;
						break;
					case 0x02:
						GenerateCh2 = FALSE;
						break;
					case 0x03:
						GenerateCh3 = FALSE;
						break;
					case 0x04: // Stop generation for all of channels
						GenerateCh0 = FALSE;
						GenerateCh1 = FALSE;
						GenerateCh2 = FALSE;
						GenerateCh3 = FALSE;
						break;
					default:
						print("Undefined behaviour\n\r");
						currCommand = undefined;
						break;
					}
					currCommand = undefined;
					break;

				case startGeneraion:
					switch (recData)
					{
					case 0x00:
						GenerateCh0 = TRUE;
						break;
					case 0x01:
						GenerateCh1 = TRUE;
						break;
					case 0x02:
						GenerateCh2 = TRUE;
						break;
					case 0x03:
						GenerateCh3 = TRUE;
						break;
					case 0x04: // Start generation for all of channel
						GenerateCh0 = TRUE;
						GenerateCh1 = TRUE;
						GenerateCh2 = TRUE;
						GenerateCh3 = TRUE;
						break;
					default:
						print("Undefined behaviour\n\r");
						break;
					}
					currCommand = undefined;
					break;

				case repeatGeneration:
					switch (recData)
					{
					case 0x00:
						RepeatCh0 = TRUE;
						break;
					case 0x01:
						RepeatCh1 = TRUE;
						break;
					case 0x02:
						RepeatCh2 = TRUE;
						break;
					case 0x03:
						RepeatCh3 = TRUE;
						break;
					case 0x04:
						RepeatCh0 = RepeatCh1 = RepeatCh2 = RepeatCh3 = TRUE;
						break;
					default:
						print("Undefined behavioral\n\r");
						break;
					}
					currCommand = undefined;
					break;

				case setAutostart:
					switch (recData)
					{
					case 0x00:
						autostartCh0 = TRUE;
						break;
					case 0x01:
						autostartCh1 = TRUE;
						break;
					case 0x02:
						autostartCh2 = TRUE;
						break;
					case 0x03:
						autostartCh3 = TRUE;
						break;
					case 0x04:
						autostartCh0 = autostartCh1 = autostartCh2 = autostartCh3 = TRUE;
						break;
					default:
						print("Undefined behavior\n\r");
					}
					currCommand = undefined;
					break;

				case resetAutostart:
					switch (recData)
					{
					case 0x00:
						autostartCh0 = FALSE;
						break;
					case 0x01:
						autostartCh1 = FALSE;
						break;
					case 0x02:
						autostartCh2 = FALSE;
						break;
					case 0x03:
						autostartCh3 = FALSE;
						break;
					case 0x04:
						autostartCh0 = autostartCh1 = autostartCh2 = autostartCh3 = FALSE;
						break;
					default:
						print("Undefined behavior\n\r");
					}
					currCommand = undefined;
					break;

				case startLoad:

					if (GetCommand(recData) != stopLoad && pairState != wait_MSB && pairState != wait_LSB)
					{
						if (!ReceivePair(&curPulse, &curPairState, recData)){
							__NOP();
						}
						else{
							//AddPair(curPulse);
							curPairState = wait_state;
						}
					}
					else{
						currCommand = stopLoad;
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

static inline void SysInit(void)
{
	Tim1_Init();//Used for generate 
	UsartInit();
	GpioInit();
	print("Generator v 0.1 2022-03-01\n\r");
}

static inline void GpioInit(void){
	RCU_APB2EN |= RCU_APB2EN_PCEN;
	gpio_init(GPIOC, GPIO_MODE_OUT_OD, GPIO_OSPEED_10MHZ, GPIO_PIN_13); // It's led for indicate activity
}
