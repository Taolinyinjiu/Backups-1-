#ifndef __MENU_UI_H__
#define __MENU_UI_H__

#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "LCD.h"
#include "delay.h"
#include "Switch.h"
#include "key.h"

extern unsigned char a[10];
extern unsigned char DataReceivedFlag;
extern unsigned int counter ;
extern float number ;
extern uint8_t Task_id;
extern float target;
extern float target_Height;
extern int Key_input;
extern unsigned int Keep_flag;
extern unsigned char Keep_time;
extern unsigned char counter_flag ;

void Menu_Init(void);
void Check_Menu(uint8_t State);
void Menu_Task_1_2(void);
void Menu_Task_3(void);
void Menu_Task_4(void);
void Menu_Task_Choose(void);
void Menu_Task_6(void);
#endif
