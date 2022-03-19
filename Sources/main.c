#include "main.h"
#include "periph_layer.h"
#include "system_layer.h"
#include "user_layer.h"
#include "protocol.h"
#include "cdc_core.h"


usbd_core_handle_struct usb_device_dev =
	{
		.dev_desc = (uint8_t *)&device_descriptor,
		.config_desc = (uint8_t *)&configuration_descriptor,
		.strings = usbd_strings,
		.class_init = cdc_acm_init,
		.class_deinit = cdc_acm_deinit,
		.class_req_handler = cdc_acm_req_handler,
		.class_data_handler = cdc_acm_data_handler};
	
		
extern uint8_t packet_sent, packet_receive;
extern uint32_t receive_length;
extern uint8_t usb_data_buffer[CDC_ACM_DATA_PACKET_SIZE];
		
//static inline void print(char* pData){
//	uint8_t countSend = 0;
//	char lastChar = 0;
//	char currChar = 0;
//	bool isEnd = FALSE;
//	while(!isEnd && countSend != 0xFF){
//		lastChar = currChar;
//		currChar = pData[countSend++];
//		if((lastChar == 0x0A) && (currChar == 0x0D)){
//			 isEnd = TRUE;
//		}
//		else if((lastChar == 0x0D) && (currChar == 0x0A)){
//			 isEnd = TRUE;
//		}
//		usb_data_buffer[countSend] = currChar;
//	}
//	if (USBD_CONFIGURED == usb_device_dev.status){
//	cdc_acm_data_send(&usb_device_dev, countSend + 1);
//	}
//}

static inline void SysInit(void);

int main()
{
	SysInit();
	getRestore(&countSampleCh0, &repeat_ch0, &autostartCh0);
	print("Generator v 1.0 2022-03-19\n\r");
	if (autostartCh0)
	{
		status_gen(0, TRUE);
		print("Autostart enable\n\r");
	}
	else
	{
		status_gen(0, FALSE);
		print("Autostart disable\n\r");
	}
	enum command detCmd = undef;
	for (;;)
	{
		if (USBD_CONFIGURED == usb_device_dev.status)
		{
			if (1 == packet_receive && 1 == packet_sent)
			{
				packet_sent = 0;
				/* receive datas from the host when the last packet datas have sent to the host */
				cdc_acm_data_receive(&usb_device_dev);
			}
			else
			{
				if (0 != receive_length)
				{
					/* send receive datas */
//					for(uint8_t i = 0; i < receive_length; ++i){
//						 Push(&RS232_RX, usb_data_buffer[i]);
//						 cdc_acm_data_send(&usb_device_dev, 1);
//					}
					cdc_acm_data_send(&usb_device_dev, receive_length);
					receive_length = 0;
				}
			}
		}
		
//		if(GetSize(&RS232_TX) != 0){
//			 uint8_t size = GetSize(&RS232_TX);
//			 for(uint8_t i = 0; i < GetSize(&RS232_TX); ++i){
//				 usb_data_buffer[i] = Pull(&RS232_TX);
//			 }
//			 cdc_acm_data_send(&usb_device_dev, size);
//		}
		/*******************************************************************************/
		if (GetSize(&RS232_RX) != 0)
		{
			uint8_t recData = Pull(&RS232_RX);
			switch (detCmd)
			{
			case undef:
				detCmd = DetectCommand(recData);
				if (detCmd == start_load)
				{
					countSampleCh0 = 0; // Reset all data for new samples
					currSampleCh0 = 0;
					parity = 0xFF;
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
				print("Repeat flag set\n\r");
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
				if (parity == 0xFF)
				{ // First byte of packet
					parity = recData;
					if (parity == 0x00)
					{
						GPIO_OCTL(GPIOB) &= ~(1U << 12);
					}
					else
					{
						GPIO_OCTL(GPIOB) |= (1U << 12);
					}
					FlashErase((uint32_t)pBeginCh0 - countSampleCh0 % 0x20);
					countSampleCh0 = 0;
					print("Pulse state is selected\n\r");
				}
				else
				{
					if (ReceiveSample(recData))
					{ // Detect stop only for full time added
						if (recTime == (uint32_t)0UL)
						{
							if (countSampleCh0 < 0x20)
							{
								FlashWrite((uint32_t)pBeginCh0, samplesCh0);
							}
							else
							{
								FlashWrite((uint32_t)pBeginCh0 + ((countSampleCh0 / 0x20)) * 0x20 * sizeof(uint32_t), &samplesCh0[0]);
							}
							getBackup(&countSampleCh0, &repeat_ch0, &autostartCh0);
							print("Load is ended\n\r");
							detCmd = undef;
						}
					}
				}
				break;

			case get_info:
				if (recData == 0x00)
				{ // For terminal
					print("Generator v 0.2 2022-03-15\n\r");
					if (countSampleCh0 == 0)
					{
						print("Generator don't have samples\n\r");
					}
					else
					{
						print("Generator have samples \n\r");
					}

					if (repeat_ch0)
					{
						print("Repeat enable\n\r");
					}
					else
					{
						print("Repeat disable\n\r");
					}

					if (autostartCh0)
					{
						print("Autostart enable\n\r");
					}
					else
					{
						print("Autostart disable\n\r");
					}
				}
				else
				{ // For GUI
					char arrayGui[6];
					if (repeat_ch0)
					{
						arrayGui[0] = 0xFF;
					}
					else
					{
						arrayGui[0] = 0x00;
					}

					if (autostartCh0)
					{
						arrayGui[1] = 0xFF;
					}
					else
					{
						arrayGui[1] = 0x00;
					}
					arrayGui[2] = (uint8_t)((countSampleCh0 >> 8) & 0xFF);
					arrayGui[3] = (uint8_t)(countSampleCh0 & 0xFF);

					arrayGui[4] = 0x0D;
					arrayGui[5] = 0x0A;

					print(arrayGui);
				}
				detCmd = undef;
				break;
			}
		}
	}
}

static inline void SysInit(void)
{
	CLK_Init();
	GPIO_Init();
	TIMERS_Init();
	usbd_core_init(&usb_device_dev);
	// USART_Init();
	IRQ_Enable();
}
