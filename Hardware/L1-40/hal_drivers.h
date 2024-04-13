#ifndef __X_HAL_DRIVERS_H_X__
#define __X_HAL_DRIVERS_H_X__

#include "stm32f4xx_usart.h"

// #define L1MOD_USART (USART3)        //L1模组串口号
#define L1MOD_USART (USART6)        //L1模组串口号
#define DEBUG_USART (USART1)        //调试串口号

void Init_Drivers(void);            //初始化驱动
void Init_SysTick(void);            //初始化时钟
void Init_L1_Usart(void);           //初始化串口参数
void Init_Debug_Usart(void);        //初始化调试串口
void Usart_Write_Bytes(USART_TypeDef* USARTx, unsigned char *pdata, int length);    //串口发送数据
void Usart_PutString(char *str);
// void delay_ms(unsigned short ms);  //毫秒延时函数
//void delay_us(unsigned short us);  //微秒延时函数
//void delay_test(void);             //延时函数


#endif
