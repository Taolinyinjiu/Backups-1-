#ifndef __X_ASCIIPROTOCOL_H_X__
#define __X_ASCIIPROTOCOL_H_X__
#include <stdbool.h>

bool Get_Param_Cmd(unsigned char x);                       //��ȡģ���������                  
bool Set_Param_Cmd(unsigned char x, int y);  //����ģ���������
bool Single_Meas_Cmd(void);                                //���β�������
bool Conti_Meas_Cmd(void);                                 //������������
bool Fast_Conti_Meas_Cmd(void);                            //����������������
bool Stop_Meas_Cmd(void);                                  //ֹͣ����
bool Laser_Switch_Cmd(unsigned char status);               //���⿪���ر�����



#endif

