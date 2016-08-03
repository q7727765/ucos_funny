#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "includes.h"
#include "key.h"
#include "beep.h"

#define START_PRIO 			10
#define START_STK_SIZE 	128
OS_STK START_SKT[START_STK_SIZE];
void start_task(void *pdata);


#define LED0_PRIO 			5
#define LED0_STK_SIZE 	64
OS_STK LED0_SKT[LED0_STK_SIZE];
void led0_task(void *pdata);


#define LED1_PRIO 			6
#define LED1_STK_SIZE 	64
OS_STK LED1_SKT[LED1_STK_SIZE];
void led1_task(void *pdata);


#define KEY_PRIO 			7
#define KEY_STK_SIZE 	128
OS_STK KEY_SKT[KEY_STK_SIZE];
void key_task(void *pdata);





OS_EVENT *sem0;
OS_EVENT *sem1;

//
int main()
{
	//SystemInit();
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);
	uart_init(168,115200);
	LED_Init();
	KEY_Init();
	BEEP_Init();
	
	OSInit();
	
	OSTaskCreate(start_task,(void*)0,(OS_STK*)&START_SKT[START_STK_SIZE-1],START_PRIO);
	
	OSStart();
}


void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr = 0;
	pdata = pdata;
	
	sem0 = OSSemCreate(1);
	sem1 = OSSemCreate(1);
	
	OSStatInit();
	
	OS_ENTER_CRITICAL();
	OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_SKT[LED0_STK_SIZE-1],LED0_PRIO);
	OSTaskCreate(led1_task,(void*)0,(OS_STK*)&LED1_SKT[LED1_STK_SIZE-1],LED1_PRIO);
	OSTaskCreate(key_task,(void*)0,(OS_STK*)&KEY_SKT[KEY_STK_SIZE-1],KEY_PRIO);
	OSTaskSuspend(START_PRIO);
	OS_EXIT_CRITICAL();
}

void led0_task(void *pdata)
{
	pdata = pdata;
	while(1)
	{
		if(OSTaskDelReq(OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ)
		{
			OSTaskDel(OS_PRIO_SELF);
		}else{
			//OSSemPend(sem0,0,NULL);
			LED0 = 0;
			delay_ms(200);
			LED0 = 1;
			delay_ms(200);
			//OSSemPost(sem1);
			//delay_ms(1000);
			
		}
		
	}
}


void led1_task(void *pdata)
{
	pdata = pdata;
	while(1)
	{
		if(OSTaskDelReq(OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ)
		{
			OSTaskDel(OS_PRIO_SELF);
		}else{
			LED1 = 0;
			delay_ms(1000);
			LED1 = 1;
			delay_ms(1000);
			
		}
//		OSSemPend(sem1,0,NULL);
		//OSSemAccept(sem1);
		
		//OSSemPost(sem0);
		//delay_ms(1000);
		
	}		
	//OSTaskDelReq
	//OSSemDel(sem1,OS_DEL_NO_PEND,0);
}

void key_task(void *pdata)
{
	char key = 0;
	OS_TCB tcb;
	OS_TCB *ptcb;
	INT8U sta;
	
	ptcb = &tcb;
	while(1)
	{
		key = KEY_Scan(0);
		switch(key)
		{
			
		case KEY0_PRES:
				sta = OSTaskQuery(5,ptcb);
				printf("bx:%#x,by:%#x,x:%d,y:%d\r\n",ptcb->OSTCBBitX,ptcb->OSTCBBitY,ptcb->OSTCBX,ptcb->OSTCBY);
				printf("dly:%d,prio:%d,taskname:%s,stksize:%d\r\n",ptcb->OSTCBDly,ptcb->OSTCBPrio,ptcb->OSTCBTaskName,ptcb->OSTCBStkSize);
				//printf("sata:%d\r\n",sizeof(OS_TCB));
				//OSSemPost(sem0);
				//OSTaskDelReq(5);
		printf("hello1\r\n");
				break;
		
		case KEY1_PRES:
			printf("hello2\r\n");
				//OSTaskDelReq(6);
				//OSSemPost(sem1);
				break;
		}
		
		delay_ms(20);
	}
}


