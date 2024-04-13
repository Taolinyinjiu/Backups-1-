/****************************************************************************************
* Copyright (C), 2020-2030,MyAntenna Tech. Co.,Ltd.
* 文件名： ASCIIProtocol.h
* 描   述：L1模组的ASCII协议指令定义
* 作   者：pamala           
* 版   本：V1.0
* 日   期: 2020.2.14
*****************************************************************************************/
#ifndef __X_ASCIIPROTOCOL_H_X__
#define __X_ASCIIPROTOCOL_H_X__
#include <stdbool.h>

bool Get_Param_Cmd(unsigned char x);                       //读取模组参数命令                  
bool Set_Param_Cmd(unsigned char x, int y);  //设置模组参数命令
bool Single_Meas_Cmd(void);                                //单次测量命令
bool Conti_Meas_Cmd(void);                                 //连续测量命令
bool Fast_Conti_Meas_Cmd(void);                            //快速连续测量命令
bool Stop_Meas_Cmd(void);                                  //停止测量
bool Laser_Switch_Cmd(unsigned char status);               //激光开启关闭命令

#endif
