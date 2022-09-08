#include "wwdg.h"
#include "led.h"

u8 WWDG_CNT=0x7f;

void WWDG_Init(int tr,int wr,int fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//WWDG ʱ��ʹ��
	WWDG_SetPrescaler(fprer);//����Ԥ��Ƶ
	WWDG_SetWindowValue(wr);////���ô���ֵ
	WWDG_Enable(tr);////ʹ�ܿ��Ź� , ���� counter .
	WWDG_ClearFlag();//�����ǰ�����жϱ�־λ
	WWDG_NVIC_Init();////��ʼ�����ڿ��Ź� NVIC
	WWDG_EnableIT();//�������ڿ��Ź��ж�

}
void WWDG_Set_Counter(int cnt)//������ WWDG ��������ֵ,WWDGΪ�ϴ��ڵ�ֵ���жϷ������е���
{
	WWDG_Enable(cnt);
}

void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_Init(&NVIC_InitStructure);
	
}
void WWDG_IRQHandler(void)//���ڿ��Ź��жϷ������
{
	// Update WWDG counter
	WWDG_SetCounter(0x7F); //�������˾��,���ڿ��Ź���������λ
	// Clear EWI flag */
	
	LED1=!LED1;
	
	WWDG_ClearFlag(); //�����ǰ�����жϱ�־λ
	// Toggle GPIO_Led pin 7 */
	

}





	
	
