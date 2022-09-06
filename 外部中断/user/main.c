


#include "exti.h"
#include "sys.h"
#include "key.h"
#include "led.h"
#include "delay.h"
#include "usart.h"




int t=0;

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	LED_Init();
	EXTIX_Init();
	key_Init();
	
	while(1)
	{
		
	}
	
}





