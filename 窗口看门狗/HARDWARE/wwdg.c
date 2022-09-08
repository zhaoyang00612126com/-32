#include "wwdg.h"
#include "led.h"

u8 WWDG_CNT=0x7f;

void WWDG_Init(int tr,int wr,int fprer)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//WWDG 时钟使能
	WWDG_SetPrescaler(fprer);//设置预分频
	WWDG_SetWindowValue(wr);////设置窗口值
	WWDG_Enable(tr);////使能看门狗 , 设置 counter .
	WWDG_ClearFlag();//清除提前唤醒中断标志位
	WWDG_NVIC_Init();////初始化窗口看门狗 NVIC
	WWDG_EnableIT();//开启窗口看门狗中断

}
void WWDG_Set_Counter(int cnt)//重设置 WWDG 计数器的值,WWDG为上窗口的值，中断服务函数中调用
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
void WWDG_IRQHandler(void)//窗口看门狗中断服务程序
{
	// Update WWDG counter
	WWDG_SetCounter(0x7F); //当禁掉此句后,窗口看门狗将产生复位
	// Clear EWI flag */
	
	LED1=!LED1;
	
	WWDG_ClearFlag(); //清除提前唤醒中断标志位
	// Toggle GPIO_Led pin 7 */
	

}





	
	
