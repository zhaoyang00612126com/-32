#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"



int KEY_Scan(int *dasasmed)//|| ��ʾ���ߵ���˼��&&��ʾ���ҵ���˼����a==b || c==d����˼���ǵ�a==b��c==d������������һ��������������ô����ʽ�Ӿͳ�����
	//a==b &&c==d����˼�ǵ�a==b��c==d����������һ������������ô����ʽ�ӱ㲻�����ˡ�
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
	delay_init(); //��ʱ������ʼ��
	LED_Init(); //��ʼ���� LED ���ӵ�Ӳ���ӿ�
	key_Init();//������ʼ��      ���ﺯ�����Ĵ�СдҪ��.h�ļ������ͳһ
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


//��ָ��(��ַ����)�İ취
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

