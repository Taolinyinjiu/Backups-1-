#ifndef __TIMER_H
#define __TIMER_H

#include "sys.h"
#include "encode_init.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pid.h"

void TIM3_Init(u16 arr, u16 psc);
void TIM5_calc_init(void);//(5000,84)Ϊ0.005s��5ms��
void TIM6_Init(void);
uint8_t Check_KeepState(uint8_t state);

#endif





















