
//#include "wwdg.h"

//#include "led.h"
//#include "sys.h"

//#include "delay.h"
//#include "usart.h"




//int main()
//{
//	
//	
//	LED_Init();
//	delay_init();
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	 LED0=0;
//	LED1=1;	
//	WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);

//	delay_ms(300);
//	while(1)
//	{
//		LED0=1;

//	}		
//	
//}


#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "wwdg.h"


 int main()
 {
	
		delay_init();	    
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
		uart_init(9600);
		LED_Init(); 
		LED0=0;
	
		delay_ms(300);	  
		WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);   
		while(1)
	{
		LED0=1;			  	   
	}	 
 }










