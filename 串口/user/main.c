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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为2
	uart_init(9600);
	LED_Init();
	LED0=0;
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("您发送的消息为:");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];//USART1->DR 串口1的数据寄存器，这里是通过串口循环发送USART_RX_BUF数据
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else                         //times%5000==0      times%200==0 这个会一直显示     times%30==0这个会一直显示
		{
			times++;
			
			printf("快点输入\r\n");  
//			if(times%30==0)
//				LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}	 
}
