#ifndef __KEY_H
#define __KEY_H
#include"sys.h"
#define KEY0	PEin(4)	//PE4
#define KEY1	PEin(3)	//PE3
#define KEY2	PEin(2)	//PE2
#define WK_UP	PAin(0)	//PA0
/*
*上述4句可以替换成下列
*#define KEY0 (1<<4)
*#define KEY1 (1<<3)
*#define KEY2 (1<<2)
*#define WK_UP (1<<0)
*
*#define KEY0_GETO((GPIOE->IDR&(KEY0))?1:0)
*#define KEY1_GETO((GPIOE->IDR&(KEY1))?1:0)
*#define KEY2_GETO((GPIOE->IDR&(KEY2))?1:0)
*#define WK_UP_GETO((GPIOA->IDR&(WK_UP))?1:0)
*/
#define KEY0_PRES 1 //KEY按下
#define KEY1_PRES 2 //KEY按下
#define KEY2_PRES 3 //KEY按下
#define WKUP_PRES 4 //KEY_UP按下
void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);	//按键扫描函数
#endif



