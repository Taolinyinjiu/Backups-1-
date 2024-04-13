#include "key.h"
#include "delay.h"

// ������ʼ������
void Key_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE); // ʹ��GPIOA,GPIOEʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5; // KEY0 KEY1 KEY2��Ӧ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		   // ��ͨ����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	   // 100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	   // ����

	GPIO_Init(GPIOF, &GPIO_InitStructure); // ��ʼ��GPIOE2,3,4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // WK_UP��Ӧ����PA0
	GPIO_Init(GPIOG, &GPIO_InitStructure);				   // ��ʼ��GPIOA0
}

uint8_t Read_Key_Signle(uint8_t Key_Id)
{
	switch (Key_Id)
	{
	case 0: return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4);break;
	case 1: return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_5);break;
	case 3: return GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_6);break;
	case 2: return GPIO_ReadInputDataBit(GPIOG, GPIO_Pin_7);break;
	default:
		return 0;
	}
}
/**
  * @brief  read four Key Value
  * @param none
  * @retval retuen 1,2,4,8;
  */
uint8_t Key_Read(void){
	uint8_t value = 0;
	for(uint8_t i = 0;i<4;i++){
		if(Read_Key_Signle(i) == 0){
			value |= 1<<i;
		}
	}
	return value;
}