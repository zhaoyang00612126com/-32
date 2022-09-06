//exit.c 文件总共包含 4 个函数。一个是外部中断初始化函数 void EXTIX_Init(void)，另外 3个都是中断服务函数。

#include "exti.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "usart.h"


void EXTIX_Init(void)
{
	//RCC2时钟使能
	
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);////外部中断，需要使能 AFIO 时钟
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);
	//配置 GPIO 与中断线的映射关系的函数 GPIO_EXTILineConfig()来实现的
	//将中断线 5 与 GPIOE 映射起来，那么很显然是 GPIOC.5 与 EXTI5 中断线连接了
	//这个怎么挑的？
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line5;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode= EXTI_Mode_Interrupt;//中断和事件怎么选？
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);
	EXTI_InitStruct.EXTI_Line=EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	
	
	//void EXTI0_IRQHandler(void)是外部中断 0 的服务函数，负责 WK_UP 按键的中断检测；
   //void EXTI9_5_IRQHandler (void)是外部中断 5~9 的服务函数，负责 KEY0 按键的中断检测；
   //void EXTI15_10_IRQHandler (void)是外部中断 10~15 的服务函数，负责 KEY1 按键的中断
	
	
	NVIC_InitStruct.NVIC_IRQChannel= EXTI0_IRQn;//使能按键所在的外部中断通道WK_UP
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct  .NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;//使能按键所在的外部中断通道  KEY0
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct  .NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;//使能按键所在的外部中断通道  KEY1
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct  .NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	
}

void EXTI0_IRQHandler(void)//进入中断
{
	if(WK_UP==1)
	{
	  LED0=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //退出中断
}



void EXTI9_5_IRQHandler (void)
{
	if(KEY0_PRES==1)
	{
		 LED1=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line5); 
}




void EXTI15_10_IRQHandler (void)
{
	if(KEY1_PRES==1)
	{
		 LED1=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line15); 
}




