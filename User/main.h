
#ifndef __MAIN_H
#define __MAIN_H

#include <stdbool.h>

typedef struct
{
    unsigned char buf[256];
	  int length;
	  bool valid;
	  int type;
}usart_buf_t;

void Clear_L1Mod_Usart(void);

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void test8(void);
void test9(void);
void test10(void);
//void test11(void);
//void test12(void);
//void test13(void);
//void test14(void);
void Task_Choose(uint8_t ID);
extern usart_buf_t g_L1Mod_node;

#endif /* __MAIN_H */


