#include <string.h>
#include "hal_drivers.h"
#include "lcd.h"

static volatile unsigned short fac_us = 0;  //时钟us计时变量
static volatile unsigned short fac_ms = 0;  //时钟ms计时变量

/**
 * @brief  Init_Drivers 
 * @param  void
 * @retval void
 **/
void Init_Drivers(void)
{
    Init_SysTick();
    Init_L1_Usart();
    Init_Debug_Usart();
}

void Init_SysTick(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SystemCoreClock / 8000000;
    fac_ms = fac_us * 1000;
}

// void Init_L1_Usart(void)
// {
//     USART_InitTypeDef USART_InitStructure;
//     GPIO_InitTypeDef GPIO_InitStructure;
//     NVIC_InitTypeDef NVIC_InitStructure;

//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//     RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

//     GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
//     GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOB, &GPIO_InitStructure);

//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//     GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_Init(GPIOB, &GPIO_InitStructure);

//     NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//     NVIC_Init(&NVIC_InitStructure);

//     USART_InitStructure.USART_BaudRate = 115200;
//     USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//     USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
//     USART_InitStructure.USART_Parity = USART_Parity_No;
//     USART_InitStructure.USART_StopBits = USART_StopBits_1;
//     USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//     USART_Init(L1MOD_USART, &USART_InitStructure);

//     USART_ITConfig(L1MOD_USART, USART_IT_RXNE, ENABLE);
//     USART_Cmd(L1MOD_USART, ENABLE);
// }

void Init_L1_Usart(void)
{
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(L1MOD_USART, &USART_InitStructure);

    USART_ITConfig(L1MOD_USART, USART_IT_RXNE, ENABLE);
    USART_Cmd(L1MOD_USART, ENABLE);
}

/**
 * @brief  Init Debug Usart 
 * @param  None
 * @retval None
 **/
void Init_Debug_Usart(void)
{
    GPIO_InitTypeDef GPIO_uInitStructure;
    USART_InitTypeDef USART_uInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    GPIO_uInitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    GPIO_uInitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_uInitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_uInitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_uInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_uInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_uInitStructure.USART_BaudRate   = 115200;
    USART_uInitStructure.USART_Parity     = USART_Parity_No;
    USART_uInitStructure.USART_StopBits   = USART_StopBits_1;
    USART_uInitStructure.USART_WordLength = USART_WordLength_8b;
    USART_uInitStructure.USART_Mode       = USART_Mode_Rx | USART_Mode_Tx;
    USART_uInitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(DEBUG_USART, &USART_uInitStructure);
    
    USART_ITConfig(DEBUG_USART, USART_IT_RXNE,ENABLE);
    USART_Cmd(DEBUG_USART, ENABLE);
}

void Usart_Write_Bytes(USART_TypeDef* USARTx, unsigned char *pdata, int length)
{
    int i = 0;
    for(i = 0; i < length; i++)
    {
        USART_SendData(USARTx, pdata[i]);
        
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
        {}
        // printf("Send Success");
    }
}

/*****************************************************
* 函数名：Usart_PutString
* 参  数：
*    str[in]:字符串
* 返回值：void
* 描  述：通过调试串口发送字符串
* 作  者：pamala， 2020.2.16
*****************************************************/
void Usart_PutString(char *str)
{
	  int i = 0;
	  int length = strlen(str);
    for(i = 0; i < length; i++)
    {
        USART_SendData(DEBUG_USART, str[i]);
        while(USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET)
        {}
    }
}

/*****************************************************
* 函数名：delay_ms
* 参  数：
*    ms[in]:毫秒数
* 返回值：void
* 描  述：延时ms毫秒
* 作  者：pamala， 2020.2.16
*****************************************************/
//void delay_ms(unsigned short ms)
//{
//    uint32_t temp = 0;
//    SysTick->LOAD = (uint32_t)ms*fac_ms;
//    SysTick->VAL  = 0X00;
//    SysTick->CTRL = 0x01;
//    do
//    {
//        temp = SysTick->CTRL;
//    }while ((temp &0x01)&&(!(temp & (1<<16))));
//    SysTick->CTRL = 0x00;
//    SysTick->VAL  = 0X00;
//}

/*****************************************************
* 函数名：delay_us
* 参  数：
*    us[in]:微秒数
* 返回值：void
* 描  述：延时us微秒
* 作  者：pamala， 2020.2.16
*****************************************************/
//void delay_us(unsigned short us)
//{
//    uint32_t temp = 0;
//    SysTick->LOAD = (uint32_t)us*fac_us;
//    SysTick->VAL  = 0X00;
//    SysTick->CTRL = 0x01;
//    do
//    {
//        temp = SysTick->CTRL;
//    }while ((temp &0x01)&&(!(temp & (1<<16))));
//    SysTick->CTRL = 0x00;
//    SysTick->VAL  = 0X00;
//}

/*****************************************************
* 函数名：delay_test
* 参  数：void
* 返回值：void
* 描  述：延时函数
* 作  者：pamala， 2020.2.16
*****************************************************/
//void delay_test(void)
//{
//	  int i,j;
//	  for(i = 0; i < 65535; i++)
//	  {
//			 for(j = 0; j<200; j++)
//			 {
//				  asm("nop");
//			 }
//		}
//}


