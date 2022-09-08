#ifndef __WWDG_H_
#define __WWDG_H_

void WWDG_Init(int tr,int wr,int fprer);
void WWDG_Set_Counter(int cnt);
void WWDG_NVIC_Init(void);
void WWDG_IRQHandler(void);
#endif


