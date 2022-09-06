#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"



int KEY_Scan(int *dasasmed)//|| 表示或者的意思，&&表示并且的意思。如a==b || c==d，意思就是当a==b，c==d这两个条件有一个条件成立，那么整个式子就成立。
	//a==b &&c==d，意思是当a==b，c==d这两个中有一个不成立，那么整个式子便不成立了。
{
	if(KEY0==0)
	{
		 *dasasmed=KEY0_PRES;
			
	}
	else if(KEY1==0)//KEY1==0||WK_UP==1
	{
		
		*dasasmed=KEY1_PRES;
	}
	else if(WK_UP==1)
	{
		
		*dasasmed=WKUP_PRES;
	}
	return 0;
}



int main()
{
	
	int t=0;
	delay_init(); //延时函数初始化
	LED_Init(); //初始化与 LED 连接的硬件接口
	key_Init();//按键初始化      这里函数名的大小写要和.h文件里面的统一
	LED0=1;
	LED1=1;
	while(1)
	{
//			KEY_Scan(&t);
//		
//			if(t==1)
//		{
//			
//		}
//		else if(t==2)
//		{
//			LED1=0;
//		}		
//		else if(t==3)
//			
//		{
//			LED0=0;
//			LED1=0;
//		}
		LED0=KEY0;
		LED1=KEY1;
		
	}	
	
	
	
}


//用指针(地址传递)的办法
//#include<stdio.h>
//int fun(int*x)
//{
//    *x=9;
//}
//int main(void)
//{
//    int t=1;
//    fun(&t);
//    printf("t = %d\n",t);
//}

