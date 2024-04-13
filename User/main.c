/*
				   _ooOoo_
				  o8888888o
				  88" . "88
				  (| -_- |)
				  O\  =  /O
			   ____/`---'\____
			 .'  \\|     |//  `.
			/  \\|||  :  |||//  \
		   /  _||||| -:- |||||-  \
		   |   | \\\  -  /// |   |
		   | \_|  ''\---/''  |   |
		   \  .-\__  `-`  ___/-. /
		 ___`. .'  /--.--\  `. . __
	  ."" '<  `.___\_<|>_/___.'  >'"".
	 | | :  `- \`.;`\ _ /`;.`/ - ` : | |
	 \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
				   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	 佛祖保佑       永无BUG				调参全对
*/
#include "stm32f4xx.h" // Device header
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "ASCIIProtocol.h"
#include "HEXProtocol.h"
#include "hal_drivers.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pid.h"
#include "pwm.h"
#include "timer.h"
#include "key.h"

#include "Menu_UI.h"
#include "Switch.h"

#define INDEXSIZE 100
// #include "stm32f4xx_usart.h"

// void TIM3_CH1_PWM_Init(u16 per,u16 psc);

usart_buf_t g_L1Mod_node;

unsigned char a[10] = {0};

static unsigned int gresult = 0;
static bool fstatus = false;
static unsigned int gdistance = 0;
static int gbytes = 0;
static unsigned char gcmd[32] = {0};
u8 DataTemp[INDEXSIZE] = {0};
u16 PwmVal = 0;
int flag = 0;
float target = 999;
float C_bisic = 384;
float target_Height = 0;
unsigned int counter = 0;
unsigned char counter_flag = 0;
unsigned int task_time = 0;
extern float number;
extern unsigned char PID_Sub;
// static unsigned int t1 = 0;

uint8_t Task_id = 0;
int Key_input = 0;
unsigned char DataReceivedFlag = 0;
u8 index_Data = 0;

void Task1_2(float *p, unsigned char *sub);
void Task3(float *p, unsigned char *sub);
void Task4(float *p, unsigned char *sub);
void Task6(float *p, unsigned char *sub);

void E5_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;		   // GPIOF6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	   // 复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	   // 推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	   // 上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);			   // 初始化PF6
}

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断优先级分�?�?�?
	delay_init(168);
	Init_Drivers();
	// uart1_init(115200);
	Menu_Init();
	Switch_Init();
	Key_Init();
	TIM11_PWM_Init(2000 - 1, 3 - 1);
	TIM3_Init(5000 - 1, 8400 - 1);
	TIM5_calc_init();
	TIM6_Init();
	E5_Init();
	GPIO_ResetBits(GPIOF, GPIO_Pin_6);
	// POINT_COLOR = RED;

	Clear_L1Mod_Usart();
	Fast_Conti_Meas_Cmd();
	// delay_ms(1000);
	TIM_SetCompare1(TIM11, 1105);
	//	LCD_ShowString(30, 50, 210, 24, 24, "Dis=");

	//

	while (1)
	{
		Task_Choose(Task_id);
		//		LCD_Clear(WHITE);
		//		LCD_ShowNum(150, 150, PwmVal, 4, 24);
		//		LCD_ShowNum(20, 30, counter, 2, 24);
		//		sprintf(a, "%.4f", number);
		//		LCD_ShowString(70, 50, 210, 24, 24, a);
		//			delay_ms(500);
		//				Task1(&target);
		//				TIM_SetCompare1(TIM11, PwmVal);
	}
}

void Clear_L1Mod_Usart()
{
	g_L1Mod_node.length = 0;
	g_L1Mod_node.valid = false;
	g_L1Mod_node.type = 0;
	memset(g_L1Mod_node.buf, 0, 256);
}

void Task1_2(float *p, unsigned char *sub)
{
	static uint8_t tick = 0;
	if (tick == 1)
		return;
	counter = 0;
	*p = 309;
	*sub = 0;
	counter_flag = 1;
	tick++;
	//	TIM_SetCompare1(TIM11, PwmVal);
}

void Task3(float *p, unsigned char *sub)
{
	static uint8_t tick = 0;
	if (tick == 0)
	{
		counter = 0;
		*p = 999;
	}
	counter_flag = 1;
	*sub = 3;
	if (Key_Read() == 1)
	{
		delay_ms(100);
		if (Key_Read() == 1)
			Key_input += 1;
	}
	else if (Key_Read() == 2)
	{
		delay_ms(100);
		if (Key_Read() == 2)
			Key_input -= 1;
	}
	else if (Key_Read() == 4)
	{		delay_ms(20);
		if (Key_Read() == 4)
		{
		}
		//			*p = target_Height;
	}
	else if (Key_Read() == 8)
	{
		delay_ms(500);
		if (Key_Read() == 8)
			*p = C_bisic - Key_input;
	}
	tick = 1;
}

void Task4(float *p, unsigned char *sub)
{
	static uint8_t tick = 0;
	if (tick == 1)
		return;
	counter = 0;
	*p = 84;
	*sub = 1;
	counter_flag = 1;
	tick++;
	//	TIM_SetCompare1(TIM11, PwmVal);
}

void Task6(float *p, unsigned char *sub)
{
	static uint8_t tick = 0;
	if (tick == 1)
		return;
	unsigned int time_temp = 0;
	counter = 0;
	*sub = 2;
	counter_flag = 1;
	*p = 159;
	time_temp = counter;
	while (counter - time_temp <= 9)
		;
	*p = 459;
	time_temp = counter;
	while (counter - time_temp <= 9)
		;
	*p = 159;
	time_temp = counter;
	while (counter - time_temp <= 9)
		;
	*p = 459;
	time_temp = counter;
	while (counter - time_temp <= 9)
		;
	*p = 0;
	tick++;
}

char buffer_test = 0;
// u8 count = 0;

void USART6_IRQHandler(void)
{
	unsigned char ch = 0;
	int length = 0;

	if (USART_GetITStatus(L1MOD_USART, USART_IT_RXNE) != RESET)
	{
		ch = USART_ReceiveData(L1MOD_USART);
		//		printf("ch = %c", ch);
		//		if(g_L1Mod_node.type == 1)//ASCII连续测量和快速连续测�?
		//		{
		DataTemp[index_Data] = ch;
		index_Data++;
		if (ch == '\n' || index_Data >= INDEXSIZE - 1)
		//			if(index == 8)
		{
			DataTemp[index_Data] = '\0';
			printf("%s", DataTemp);
			DataReceivedFlag = 1;
			index_Data = 0;
		}
		USART_ClearITPendingBit(L1MOD_USART, USART_IT_RXNE);
		// Usart_Write_Bytes(DEBUG_USART, &ch, 1);
		//		}
		//		else if(g_L1Mod_node.type == 2)//HEX连续测量和快速连续测�?
		if (g_L1Mod_node.type == 2) // HEX连续测量和快速连续测�?
		{
			if (!fstatus)
			{
				gresult = gresult | ch;
				if ((gresult & 0xffffff) == 0XB46903) // 帧头是B4 69 03
				{
					fstatus = true; // 找到帧头�?
					gresult = 0;
				}
				else
				{
					gresult = gresult << 8;
				}
			}
			else
			{
				gbytes++;
				gdistance = gdistance | ch;
				if (gbytes != 4)
				{
					gdistance = gdistance << 8;
				}
				else
				{
					sprintf((char *)gcmd, "D=%f", gdistance / 10000.0);
					// printf("%s", gcmd);
					Usart_Write_Bytes(DEBUG_USART, gcmd, strlen((char *)gcmd));
					gbytes = 0;
					gdistance = 0;
					fstatus = false;
				}
			}
		}
		else // 其他
		{
			length = g_L1Mod_node.length;
			g_L1Mod_node.buf[length++] = ch;
			g_L1Mod_node.length = length % 256;
		}
	}
	if (USART_GetFlagStatus(L1MOD_USART, USART_FLAG_ORE) == SET)
	{
		USART_ClearFlag(L1MOD_USART, USART_FLAG_ORE);
		USART_ReceiveData(L1MOD_USART);
	}
}

// 调试串口中断服务函数
void USART1_IRQHandler(void)
{
	if (USART_GetITStatus(DEBUG_USART, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(DEBUG_USART, USART_IT_RXNE);
		USART_ReceiveData(DEBUG_USART);
	}

	if (USART_GetFlagStatus(L1MOD_USART, USART_FLAG_ORE) == SET)
	{
		USART_ClearFlag(DEBUG_USART, USART_FLAG_ORE);
		USART_ReceiveData(DEBUG_USART);
	}
}

void Task_Choose(uint8_t ID)
{
	switch (ID)
	{
	case 0:
		target = 999;
		break;
	case 1:
		Task1_2(&target, &PID_Sub);
		break;
	case 3:
		Task3(&target, &PID_Sub);
		break;
	case 4:
		Task4(&target, &PID_Sub);
		break;
	case 6:
		Task6(&target, &PID_Sub);
		break;
	default:
		break;
	}
}
