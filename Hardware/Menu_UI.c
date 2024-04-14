#include "Menu_UI.h"

uint8_t Menu_State = 17;

void Menu_Init(void){
	LCD_Init();
	LCD_Display_Dir(1);
	LCD_Clear(BLACK);
	delay_ms(100);
	LCD_Clear(WHITE);
	LCD_ShowString(56,0,12*20,24,24,(uint8_t *)"Xupt Choose Test");
	LCD_ShowString(0,24*1+5,12*12,24,24,(uint8_t *)"Basic Test :");
	LCD_ShowString(0,24*2+10,12*14,24,24,(uint8_t *)"Task 1 to Test");
	LCD_ShowString(0,24*3+15,12*14,24,24,(uint8_t *)"Task 2 to Test");
	LCD_ShowString(0,24*4+20,12*14,24,24,(uint8_t *)"Task 3 to Test");
	LCD_ShowString(0,24*5+25,12*14,24,24,(uint8_t *)"Task 4 to Test");
}

void Check_Menu(uint8_t State){
	switch(State){
		case 0:	Menu_Task_Choose();break;
		case 1: Menu_Task_1_2();break;
		case 2: Menu_Task_3();break;
		case 8 :Menu_Task_4();break;
		case 4: Menu_Task_6();break;
		default : LCD_ShowNum(0,24*6+30,State,2,32);break;
	}
}

void Menu_Task_1_2(void){
	if(Menu_State != 1){
	LCD_Clear(WHITE);
	LCD_ShowString(32,0,16*20,32,32,(uint8_t *)"Task 1&2 to Test");
	LCD_ShowString(0,32,16*19,32,32,(uint8_t *)"Aim Location:B & C");
	LCD_ShowString(0,32*2+10,16*15,32,32,(uint8_t *)"Aim H: 253 mm");
	LCD_ShowString(0,32*3+10,16*9,32,32,(uint8_t *)"Actual H:");
	LCD_ShowString(0,32*4+20,16*10,32,32,(uint8_t *)"Time (s):");
//	Task_Choose(1);
		Task_id = 1;
	}
	if(DataReceivedFlag == 0){
	sprintf(a, " %.2f mm",562 - number * 1000);
	}
	LCD_ShowString(16*9,32*3+10,16*10,32,32,(uint8_t *)a);
	LCD_ShowNum(16*11,32*4+20,counter/2,2,32);
	Menu_State = 1;
}

void Menu_Task_3(void){
	if(Menu_State != 2){
	LCD_Clear(WHITE);
	LCD_ShowString(56,0,16*20,32,32,(uint8_t *)"Task 3 to Test");
	LCD_ShowString(0,32,16*16,32,32,(uint8_t *)"Keybord input : ");
	LCD_ShowString(0,32*2+10,16*15,32,32,(uint8_t *)"Aim H:     mm");
	LCD_ShowString(0,32*3+10,16*9,32,32,(uint8_t *)"Actual H:");
	LCD_ShowString(0,32*4+20,16*10,32,32,(uint8_t *)"Time (s):");
	LCD_ShowString(0,32*5+25,16*10,32,32,(uint8_t *)"Key State:");
//	Task_Choose(3);
		Task_id = 3;
	}
	if(DataReceivedFlag == 0){
	sprintf(a, " %.2f mm",354 - number * 1000);
	}
	//LCD_ShowNum(16*6, 32*2+10, target - 354 + Key_input, 4, 32);
	if(counter_flag == 0){
		LCD_ShowNum(16*6, 32*2+10, Key_input, 4, 32);
	}
	LCD_ShowString(16*9,32*3+10,16*10,32,32,(uint8_t *)a);
	if(Key_input >= 0){
		LCD_ShowChar(16*15,32,' ',32,0);
		LCD_ShowNum(16*16,32,Key_input,3,32);}
	else{
		LCD_ShowChar(16*15,32,'-',32,0);
		LCD_ShowNum(16*16,32,-Key_input,3,32);}
	LCD_ShowNum(16*11,32*4+20,counter/2,2,32);
	LCD_ShowNum(16*11,32*5+25,Key_Read(),2,32);
	Menu_State = 2;
}

void Menu_Task_4(void){
	if(Menu_State != 3){
	LCD_Clear(WHITE);
	LCD_ShowString(56,0,16*20,32,32,(uint8_t *)"Task 4 to Test");
	LCD_ShowString(0,32,16*19,32,32,(uint8_t *)"Keybord input : ");
	LCD_ShowString(0,32*2+10,16*15,32,32,(uint8_t *)"Aim H:  488mm");
	LCD_ShowString(0,32*3+10,16*9,32,32,(uint8_t *)"Actual H:");
	LCD_ShowString(0,32*4+20,16*10,32,32,(uint8_t *)"Time (s):");
//	Task_Choose(4);
		Task_id = 4;
	}
	if(DataReceivedFlag == 0){
	sprintf(a, " %.2f mm",562 - number * 1000);
	}
	LCD_ShowString(16*9,32*3+10,16*10,32,32,(uint8_t *)a);
	LCD_ShowNum(16*11,32*4+20,counter/2,2,32);
	Menu_State = 3;
}

void Menu_Task_6(void){
	if(Menu_State != 4){
	LCD_Clear(WHITE);
	LCD_ShowString(56,0,16*20,32,32,(uint8_t *)"Task 6 to Test");
	LCD_ShowString(0,32,16*19,32,32,(uint8_t *)"Keybord input : ");
	LCD_ShowString(0,32*2+10,16*15,32,32,(uint8_t *)"Aim H:     mm");
	LCD_ShowString(0,32*3+10,16*9,32,32,(uint8_t *)"Actual H:");
	LCD_ShowString(0,32*4+20,16*15,32,32,(uint8_t *)"Total Time (s):");
	LCD_ShowString(0,32*5+25,16*15,32,32,(uint8_t *)"Keep  Time (s):");
//	Task_Choose(6);
		Task_id = 6;
	}
	if(DataReceivedFlag == 0){
	sprintf(a, " %.2f mm",562 - number * 1000);
	}
	LCD_ShowNum(16*6, 32*2+5, 562 - target, 4, 32);
	LCD_ShowString(16*9,32*3+10,16*10,32,32,(uint8_t *)a);
	LCD_ShowNum(16*16,32*4+20,counter/2,2,32);
	LCD_ShowNum(16*16,32*5+25,Keep_time/2,2,32);
	Menu_State = 4;
}

void Menu_Task_Choose(void){
	if(Menu_State != 0){
	LCD_Clear(WHITE);
	LCD_ShowString(56,0,12*20,24,24,(uint8_t *)"Xupt Choose Test");
	LCD_ShowString(0,24*1+5,12*12,24,24,(uint8_t *)"Basic Test :");
	LCD_ShowString(0,24*2+10,12*14,24,24,(uint8_t *)"Task 1 to Test");
	LCD_ShowString(0,24*3+15,12*14,24,24,(uint8_t *)"Task 2 to Test");
	LCD_ShowString(0,24*4+20,12*14,24,24,(uint8_t *)"Task 3 to Test");
	LCD_ShowString(0,24*5+25,12*14,24,24,(uint8_t *)"Task 4 to Test");
//	Task_Choose(0);
		Task_id = 0;
	}
	Menu_State = 0;
}

void TIM6_DAC_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) == SET)
	{
		Check_Menu(Switch_read());
	}
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
}
