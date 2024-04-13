#include "Switch.h"
#include "sys.h"


/**
  * @brief 	Init function for Switch interface
	*	@note 	无
  * @retval 无
  */
void Switch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	   
	GPIO_Init(GPIOF, &GPIO_InitStructure);			   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	   
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);		   

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	   
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);		   
}

uint8_t Read_Switch_single_Pin(uint8_t Pin_Id){
	switch (Pin_Id) {
		case 0 : return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4); break;
		case 1 : return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15); break;
		case 2 : return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2); break;
		case 3 : return GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3); break;
		default : return 0;
	}
}

uint8_t Switch_read(void){
	uint8_t value = 0;
	for(uint8_t i = 0;i<4;i++){
		if(Read_Switch_single_Pin(i) == 1){
			value |= 1<<i;
		}
	}
	return value;
}
