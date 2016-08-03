#include"beep.h"
//初始化PB8为输出口.并使能这个口的时钟
//蜂鸣器初始化
void BEEP_Init(void)
{
	RCC->AHB1ENR|=1<<5; //使能PORTF时钟
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,
			 GPIO_PUPD_PD);//PF8设置，下拉
	BEEP=0;					//关闭蜂鸣器
}



