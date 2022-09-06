//exit.c �ļ��ܹ����� 4 ��������һ�����ⲿ�жϳ�ʼ������ void EXTIX_Init(void)������ 3�������жϷ�������

#include "exti.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "usart.h"


void EXTIX_Init(void)
{
	//RCC2ʱ��ʹ��
	
	NVIC_InitTypeDef NVIC_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);////�ⲿ�жϣ���Ҫʹ�� AFIO ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);
	//���� GPIO ���ж��ߵ�ӳ���ϵ�ĺ��� GPIO_EXTILineConfig()��ʵ�ֵ�
	//���ж��� 5 �� GPIOE ӳ����������ô����Ȼ�� GPIOC.5 �� EXTI5 �ж���������
	//�����ô���ģ�
	
	
	EXTI_InitStruct.EXTI_Line=EXTI_Line5;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode= EXTI_Mode_Interrupt;//�жϺ��¼���ôѡ��
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
	
	
	//void EXTI0_IRQHandler(void)���ⲿ�ж� 0 �ķ����������� WK_UP �������жϼ�⣻
   //void EXTI9_5_IRQHandler (void)���ⲿ�ж� 5~9 �ķ����������� KEY0 �������жϼ�⣻
   //void EXTI15_10_IRQHandler (void)���ⲿ�ж� 10~15 �ķ����������� KEY1 �������ж�
	
	
	NVIC_InitStruct.NVIC_IRQChannel= EXTI0_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��WK_UP
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct  .NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��  KEY0
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct  .NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��  KEY1
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct  .NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	
}

void EXTI0_IRQHandler(void)//�����ж�
{
	if(WK_UP==1)
	{
	  LED0=0;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); //�˳��ж�
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




