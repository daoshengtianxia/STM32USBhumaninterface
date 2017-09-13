#ifndef BSP_LED_H
#define BSP_LED_H


#include "stm32f10x.h"

#define  LED_Port   GPIOC
#define  LED_Pin    GPIO_Pin_0




#define LED_ON     GPIO_ResetBits(LED_Port, LED_Pin);
#define LED_OFF   GPIO_SetBits(LED_Port, LED_Pin);
void BSP_LED_Init(void);
#endif
