/****************************************************************************************
* Copyright (C), 2020-2030,MyAntenna Tech. Co.,Ltd.
* 文件名： ASCIIProtocol.h
* 描   述：L1模组的ASCII协议指令的实现
* 作   者：pamala           
* 版   本：V1.0
* 日   期: 2020.2.14
*****************************************************************************************/
#include <stdio.h>
#include <string.h>
#include "ASCIIProtocol.h"
#include "hal_drivers.h"
#include "main.h"
#include "delay.h"

/***********************************************************
* 函数名：Get_Param_Cmd
* 参数：
*    x[in]: 命令类型
* 返回值：成功返回ture，失败返回false
* 描述：根据不同的命令类型，读取L1模组的参数值
* 作者：pamala, 2020.2.15
************************************************************/
bool Get_Param_Cmd(unsigned char x)
{
    unsigned char cmd[16] = {0};
		
	sprintf((char*)cmd, "iGET:%d", x);
	// printf("%s", cmd);
	Clear_L1Mod_Usart();
	// printf("%d", 1);
    Usart_Write_Bytes(L1MOD_USART, cmd, strlen((char*)cmd));	
	// printf("%d", 123);	
	delay_ms(200);
	if(strstr((char*)g_L1Mod_node.buf, "OK")!= NULL)
	{
			return true;
	}
	else
	{
			return false;
	}
}

/***********************************************************
* 函数名：Set_Param_Cmd
* 参数：
*    x[in]: 命令类型
*    y[in]: 设置参数值
* 返回值：成功返回true，失败返回false
* 描述：根据不同的命令类型，设置L1模组的参数值
* 作者：pamala, 2020.2.15
************************************************************/
bool Set_Param_Cmd(unsigned char x, int y)
{
    unsigned char cmd[32] = {0};
	sprintf((char*)cmd, "iSET:%d,%d", x, y);
	
	Clear_L1Mod_Usart();
	Usart_Write_Bytes(L1MOD_USART, cmd, strlen((char*)cmd));
	delay_ms(200);
	if(strstr((char*)g_L1Mod_node.buf, "OK")!= NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************
* 函数名：Single_Meas_Cmd
* 参  数：void
* 返回值：成功返回true，失败返回false
* 描  述：发送单次测量命令
* 作者：pamala, 2020.2.15
************************************************************/
bool Single_Meas_Cmd(void)
{
	Clear_L1Mod_Usart();
	Usart_Write_Bytes(L1MOD_USART, (unsigned char*)"iSM", 3);
//		delay_test();
	delay_ms(200);
	if(strstr((char*)g_L1Mod_node.buf, "D=")!= NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
    
}

/***********************************************************
* 函数名：Conti_Meas_Cmd
* 参  数：void
* 返回值：成功返回true，失败返回false
* 描  述：发送连续测量命令
* 作者：pamala, 2020.2.15
************************************************************/
bool Conti_Meas_Cmd(void)
{
    Clear_L1Mod_Usart();
	g_L1Mod_node.type = 1;
	Usart_Write_Bytes(L1MOD_USART, (unsigned char*)"iACM", 4);
	return true;
}

/***********************************************************
* 函数名：Fast_Conti_Meas_Cmd
* 参  数：void
* 返回值：成功返回true，失败返回false
* 描  述：发送快速连续测量命令
* 作者：pamala, 2020.2.15
************************************************************/
bool Fast_Conti_Meas_Cmd(void)
{
    Clear_L1Mod_Usart();
	g_L1Mod_node.type = 1;
	Usart_Write_Bytes(L1MOD_USART, (unsigned char*)"iFACM", 5);
	return true;
}

/***********************************************************
* 函数名：Stop_Meas_Cmd
* 参  数：void
* 返回值：成功返回true，失败返回false
* 描  述：发送停止测量命令
* 作者：pamala, 2020.2.15
************************************************************/
bool Stop_Meas_Cmd(void)
{
    Clear_L1Mod_Usart();
	Usart_Write_Bytes(L1MOD_USART, (unsigned char*)"iHALT", 5);
	delay_ms(100);
	if(strstr((char*)g_L1Mod_node.buf, "STOP")!= NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************
* 函数名：Laser_Switch_Cmd
* 参  数：void
* 返回值：成功返回true，失败返回false
* 描  述：发送激光开启关闭命令
* 作者：pamala, 2020.2.15
************************************************************/
bool Laser_Switch_Cmd(unsigned char status)
{
    unsigned char cmd[5] = {0};
    sprintf((char*)cmd, "iLD:%d", status);
    
	Clear_L1Mod_Usart();
	Usart_Write_Bytes(L1MOD_USART, cmd, strlen((char*)cmd));
	delay_ms(100);
	if(strstr((char*)g_L1Mod_node.buf, "LASER")!= NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

