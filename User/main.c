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
#include "rc522_function.h"
#include "rc522_config.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usbio.h"
#include "usb_desc.h"

extern uint8_t USB_Received_Flag;

extern uint8_t USB_Receive_Buffer[REPORT_COUNT];
extern uint8_t USB_Send_Buffer[REPORT_COUNT];

/**
* @brief  main
* @param  none
* @return none
*/
int main(void)
{
	uint8_t data[REPORT_COUNT];
	Set_System();

	uint8_t ret=0, i=0;
	Set_System();
//	BSP_USART_Init();
//	sprintf((char *)SendData, "Init compled\r\n");
//	USART1_Send(SendData, strlen((char *)SendData));

	USB_Interrupts_Config();
	Set_USBClock();
	USB_Init();
	RC522_Init();     //RC522 Init
	BSP_KEY_Init();
	BSP_LED_Init();
	
	PcdReset();
	M500PcdConfigISOType ( 'A' );
	
	for(i=0;i<64;i++){
		USB_Receive_Buffer[i] = i+6;
	}

	for(i=0;i<64;i++){
		USB_Send_Buffer[i] = i+12;
	}
	
	
	while(1)
	{
		u8 ucArray_ID [ 4 ];                                                                                             //?¨¨o¨®¡ä?¡¤?IC?¡§¦Ì?¨¤¨¤D¨ªo¨ªUID(IC?¡§D¨°¨¢Do?)
		u8 ucStatusReturn;                                                                                               //¡¤¦Ì??¡Á¡ä¨¬?
		if(USB_Received_Flag){
			USB_Received_Flag=0;
			ret = USB_GetData(data, sizeof(data));
			if(data[63] == 'A')
			{
				LED_ON;
			}
			else if(data[63] == 'B')
			{
				LED_OFF;
			}
			USB_SendData(data, sizeof(data));
		}
		
		if ( ( ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID ) ) != MI_OK )                                 
		ucStatusReturn = PcdRequest ( PICC_REQALL, ucArray_ID );		                                               

		if ( ucStatusReturn == MI_OK  )
		{
			if ( PcdAnticoll ( ucArray_ID ) == MI_OK )                                                                  
			{
				data[0] = ucArray_ID [ 0 ];
				data[1] = ucArray_ID [ 1 ];
				data[2] = ucArray_ID [ 2 ];
				data[3] = ucArray_ID [ 3 ];
				USB_SendData(data, sizeof(data));
			}
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



