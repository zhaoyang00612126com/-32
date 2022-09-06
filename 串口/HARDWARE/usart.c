#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//重定义fputc函数 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
#endif 

 
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
//u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
//u16 USART_RX_STA=0;       //接收状态标记	  
  


void UART_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//①串口时钟使能，GPIO 时钟使能，复用时钟使能:使能 USART1,GPIOA 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2串口复位
	USART_DeInit(USART1);
	//3、PA9io端口使能，GPIO参数初始化
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //模式  看表
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //放后面
	
	//3、PA10io端口使能
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //模式  看表
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	//4、串口参数初始化
	USART_InitStructure.USART_BaudRate=9600; 
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity= USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure); //GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	//5、中断优先级   初始化
	 NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//?
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
		NVIC_Init(&NVIC_InitStructure);//GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//6、开启中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
	
	//7、使能串口
	
	USART_Cmd(USART1, ENABLE);
	
}




void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	
		
		//回车：回到当前行行首，不会回到下一行，如果接着输入则会覆盖本行以前的内容。0x0d  \r
		//换行：换到当前位置的下一行，而不会回到首行。  0x0a  \n
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
			Res =USART_ReceiveData(USART1);	//读取接收到的数据
		                                        //USART_RX_STA&0x8000若为1表示bit15为1，USART_RX_STA的二进制首数字为1，则表明接收到了0x0a，可以结束，
			                                    //同理0x4000表示接收到了0x0d，可以结束
			                                    //正常的结束应该先接受到0x0a,再接收到0x0d，表示先换到下一行的当前位置，再回到这一行的行首
			if((USART_RX_STA&0x8000)==0)//接收未完成，
			{
				if(USART_RX_STA&0x4000)//接收到了0x0d
				{
					if(Res!=0x0a)
						USART_RX_STA=0;//接收错误,重新开始
					else 
						USART_RX_STA=USART_RX_STA|0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
					if(Res==0x0d)
						USART_RX_STA=USART_RX_STA|0x4000;//结果
					else
					{
						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;//USART_RX_STA&0x3fff接收到的数据长度,一直在接收
						USART_RX_STA++;//这边可以循环？
						if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;//接收数据错误,重新开始接收	  
					}						
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntExit();  											 
#endif
} 
#endif	





