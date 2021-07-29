#include "stm32f407xx.h"
void delay(int);
int main(void)
{
	RCC->AHB1ENR |=0x00000009;
	GPIOD->MODER |=0x55000000;
	GPIOA->MODER &=~0x00000000;
	
	while(1)
	{
		if(GPIOA->IDR &(1<<0))
		{
		GPIOD->ODR |=0x0000F000;
		delay(100);
		}
		else
		{
		GPIOD->ODR &=~ 0x0000F000;
		delay(100);
		}
	}
}
void delay(int delayMS)
{
	int i;
	for(;delayMS>0;delayMS--)
	{
		for(i=0;i<=3195;i++);
	}
}