#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "stm32f4xx.h"                  // Device header
#include "delay.h"

void Switch_Init(void);
uint8_t Read_Switch_single_Pin(uint8_t Pin_Id);
uint8_t Switch_read(void);



#endif
