#include"beep.h"
//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��
//��������ʼ��
void BEEP_Init(void)
{
	RCC->AHB1ENR|=1<<5; //ʹ��PORTFʱ��
	GPIO_Set(GPIOF,PIN8,GPIO_MODE_OUT,GPIO_OTYPE_PP,GPIO_SPEED_100M,
			 GPIO_PUPD_PD);//PF8���ã�����
	BEEP=0;					//�رշ�����
}



