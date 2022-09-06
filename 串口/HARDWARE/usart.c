#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif

//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//_sys_exit(int x) 
//{ 
//	x = x; 
//} 
//�ض���fputc���� 
//int fputc(int ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
#endif 

 
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
//u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
//u16 USART_RX_STA=0;       //����״̬���	  
  


void UART_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	//�ٴ���ʱ��ʹ�ܣ�GPIO ʱ��ʹ�ܣ�����ʱ��ʹ��:ʹ�� USART1,GPIOA ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//2���ڸ�λ
	USART_DeInit(USART1);
	//3��PA9io�˿�ʹ�ܣ�GPIO������ʼ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; //ģʽ  ����
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //�ź���
	
	//3��PA10io�˿�ʹ��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; //ģʽ  ����
	GPIO_InitStructure.GPIO_Pin= GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	//4�����ڲ�����ʼ��
	USART_InitStructure.USART_BaudRate=9600; 
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity= USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure); //GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	
	//5���ж����ȼ�   ��ʼ��
	 NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//?
	    NVIC_InitStructure.NVIC_IRQChannelSubPriority=3;
		NVIC_Init(&NVIC_InitStructure);//GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//6�������ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
	
	//7��ʹ�ܴ���
	
	USART_Cmd(USART1, ENABLE);
	
}




void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	
		
		//�س����ص���ǰ�����ף�����ص���һ�У��������������Ḳ�Ǳ�����ǰ�����ݡ�0x0d  \r
		//���У�������ǰλ�õ���һ�У�������ص����С�  0x0a  \n
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
			Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		                                        //USART_RX_STA&0x8000��Ϊ1��ʾbit15Ϊ1��USART_RX_STA�Ķ�����������Ϊ1����������յ���0x0a�����Խ�����
			                                    //ͬ��0x4000��ʾ���յ���0x0d�����Խ���
			                                    //�����Ľ���Ӧ���Ƚ��ܵ�0x0a,�ٽ��յ�0x0d����ʾ�Ȼ�����һ�еĵ�ǰλ�ã��ٻص���һ�е�����
			if((USART_RX_STA&0x8000)==0)//����δ��ɣ�
			{
				if(USART_RX_STA&0x4000)//���յ���0x0d
				{
					if(Res!=0x0a)
						USART_RX_STA=0;//���մ���,���¿�ʼ
					else 
						USART_RX_STA=USART_RX_STA|0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
					if(Res==0x0d)
						USART_RX_STA=USART_RX_STA|0x4000;//���
					else
					{
						USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;//USART_RX_STA&0x3fff���յ������ݳ���,һֱ�ڽ���
						USART_RX_STA++;//��߿���ѭ����
						if(USART_RX_STA>(USART_REC_LEN-1))
						USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}						
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	





