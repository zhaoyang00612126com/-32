#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"

int main(void)
{
	int t=0;
	int len=0; 
	int times=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ2
	uart_init(9600);
	LED_Init();
	LED0=0;
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("�����͵���ϢΪ:");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];//USART1->DR ����1�����ݼĴ�����������ͨ������ѭ������USART_RX_BUF����
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else                         //times%5000==0      times%200==0 �����һֱ��ʾ     times%30==0�����һֱ��ʾ
		{
			times++;
			
			printf("�������\r\n");  
//			if(times%30==0)
//				LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}	 
}
