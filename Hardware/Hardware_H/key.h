#ifndef __KEY_H__
#define __KEY_H__	 

#include "stm32f4xx.h"                  // Device header

void Key_Init(void);
uint8_t Read_Key_Signle(uint8_t Key_Id);
uint8_t Key_Read(void);

#endif
