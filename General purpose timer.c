#include "stm32f407xx.h"
void Timer_Init(void);
void delay(int delayMS);
int main()
{
	RCC->AHB1ENR |= (1<<3); // GPIOD Clock Enable
	GPIOD->MODER |= (1<<26);
	Timer_Init();
	while(1)
	{
		while(!(TIM2->SR & (1<<0))){}
		
		TIM2->SR&=~1;
		GPIOD->ODR ^= (1<<13);
	
	}
}
void Timer_Init()
{
	RCC->APB1ENR |= (1<<0); //Timer 2 Clock Enable
	TIM2->PSC |= 16000-1;   //  16000000/ 16000 =1000
	TIM2->ARR |= 4000-1;  // 1000/1000 => 1Hz
	/*
	
	
	
	*/

	TIM2->CNT  = 0;
	TIM2->CR1 |= (1<<0); // Counter Enable
}
void delay(int delayMS)
{
	int i;
	for(;delayMS>0;delayMS--)
	for(i=0;i<3194;i++);
}
