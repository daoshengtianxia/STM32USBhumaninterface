/**
************************************************************
* @file         main.c
* @brief        
* @author       
* @date         
* @version      
* @copyright    
* 
* @note         
*               
*               
*               
*
***********************************************************/
#include "includes.h"
#include "bsp_key.h"
#include "bsp_led.h"


#include "usb_lib.h"
#include "hw_config.h"
#include "usbio.h"
#include "usb_desc.h"

extern uint8_t USB_Received_Flag;
/**
* @brief  main
* @param  none
* @return none
*/
int main(void)
{
	uint8_t dscnt=0;
	uint8_t data[REPORT_COUNT];
//	uint8_t i=0;
	Set_System();
//	BSP_USART_Init();
//	sprintf((char *)SendData, "Init compled\r\n");
//	USART1_Send(SendData, strlen((char *)SendData));

	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	BSP_KEY_Init();
	BSP_LED_Init();
	
	while(1)
	{
		if(USB_Received_Flag){
			USB_Received_Flag=0;
			USB_GetData(data,sizeof(data));
			if(data[1] == 'A')
			{
				LED_ON;
			}
			else if(data[1] == 'B')
			{
				LED_OFF;
			}
//			ret = USB_GetData(data,sizeof(data));
//			printf("usb get data %d byte data\n\r",ret);
//			for(i=0;i<ret;i++){
//				printf("0x%02X ",data[i]);
//			}
//			printf("\n\r");
			if(dscnt<1)
			{
//				for(i=0; i < REPORT_COUNT; i++)
//				{
//					data[i] = '0'+dscnt;
//				}
				dscnt++;
				sprintf((char *)data, "Hello I am STM32 HID AAAAABBBBBBBBBHAHAH                  ERTYUA");
			}
			else
			{
				sprintf((char *)data, "AAAAABBBBBBBBBHAHAH Hello I am STM32 HID                  ABCDFA");
				dscnt = 0;
			}

			
			USB_SendData(data,sizeof(data));
		}
//		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
//		{
//			int delay = 1000;
//			while(delay--);
//			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0)
//			{
//				while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
////				sprintf((char *)SendData, "YOU pressed key Ha Ha Ha Ha Ha Ha Ha Ha Ha Ha\r\n");
//				USB_SendData(data,sizeof(data));
//			}
//		}
	}
}



