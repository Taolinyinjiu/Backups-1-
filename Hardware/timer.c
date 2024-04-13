#include "timer.h"

#define INDEXSIZE 100

#define  B_location 234
#define  C_location 384
#define  D_location 534

extern u8 DataReceivedFlag;
extern u8 DataTemp[INDEXSIZE];
extern u8 a[10];
extern u16 PwmVal;
extern unsigned int counter;
extern unsigned char counter_flag;
extern unsigned int Keep_flag;
extern unsigned char Keep_time;
extern uint8_t Keep_state;


extern float target;
// Actual Pingpong Location Value
float number = 0.0;	

void TIM3_Init(u16 arr, u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInitStructure.TIM_Period = arr;
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void TIM5_calc_init(void) //(5000,84)为0.005s（5ms）//（a，b）T=a*b/84000000
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

	// 下端代码修改计数周期为10ms
	TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 84 - 1;

	// 下段代码修改计数周期为5ms
	//	TIM_TimeBaseInitStruct.TIM_Period=5000-1;
	//	TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStruct);

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM5, ENABLE);
}

/**
 * @brief	Init for TIM6 interrupt init
 *	@note 	none
 * @retval none
 */
void TIM6_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;

	// 下端代码修改计数周期为10ms
	TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 840 - 1;

	// 下段代码修改计数周期为5ms
	//	TIM_TimeBaseInitStruct.TIM_Period=5000-1;
	//	TIM_TimeBaseInitStruct.TIM_Prescaler=84-1;

	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&NVIC_InitStruct);

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM6, ENABLE);
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		//		printf("%d", 1);
		if (counter_flag)
		{
			counter++;
		}
		if(Check_KeepState(Keep_state)){
			Keep_time ++;
		}
		else
			Keep_time = 0;
		printf("counter=%d\r\n", counter);
	}

	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}

//
void TIM5_IRQHandler(void) // 定时器5中断服务函数
{
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) == SET) // 溢出中断
	{
		if (DataReceivedFlag)
		{
			char *start = strchr(DataTemp, '=');
			if (start != NULL)
			{
				start++;
				number = strtof(start, NULL);
				//				printf("num = %.4f\n", number);
				// sprintf(a, "%.4f", number);
				// LCD_Clear(WHITE);
				// LCD_ShowString(30, 40, 210, 24, 24, a);
				//				sprintf(a, "%.4f", number - target);
				//				LCD_Clear(WHITE);
				//				LCD_ShowString(100, 100, 210, 24, 24, a);
				// delay_ms(300);
			}
			//			LCD_ShowString(30, 40, 210, 24, 24, DataTemp);
			memset(DataTemp, 0, sizeof(DataTemp));
			DataReceivedFlag = 0;
		}
		if(number * 1000 > B_location)
			Keep_flag = 0;
		else 
			Keep_flag =1;
		printf("line1=%f,", number * 1000);
		printf("line2=%f,", target);
		printf("line3=%f,", number * 1000 - target);
		PwmVal = pid_location(target, number * 1000);
		TIM_SetCompare1(TIM11, PwmVal);
		// LCD_Clear(WHITE);
		// LCD_ShowNum(150, 150, PwmVal, 4, 24);
		// LCD_ShowNum(20, 30, counter, 2, 24);
		// sprintf(a, "Dis=%.4f", 561 - number * 1000);
		// LCD_ShowString(70, 50, 210, 24, 24, a);
		// PwmVal += 10;
		// if(PwmVal > 100)
		// 	PwmVal = 100;
		// LCD_Clear(WHITE);
		//		sprintf(a, "%d", PwmVal);
		//		LCD_ShowString(30, 40, 210, 24, 24, a);
		// LCD_ShowNum(150, 150, PwmVal, 3, 24);
		// LCD_ShowNum(20, 30, counter, 2, 24);
	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update); // 清除中断标志位
}
//

uint8_t Check_KeepState(uint8_t state){
	if(state == 0){
		if(number * 1000 < B_location)
			return 1;
		else return 0;
	}
	else if(state == 1){
		if(number * 1000 < D_location && number * 1000 > C_location)
			return 1;
		else return 0;
	}
}
