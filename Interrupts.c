#include "stm32f4xx.h"
// led : PD12
// Button : PA0
void Systickdelay(int delayMS);
//int count = 0;
int main()
{
	__disable_irq();	//Disable IRQs at first
	RCC->AHB1ENR |=0x00000009; //PORT D and Port A  clock enable
	RCC->APB2ENR |= (1<<14); //SYSCFG Clock Enable
	
	GPIOD->MODER &= ~(1<<24);
	GPIOD->MODER |= (1<<24);
	SYSCFG->EXTICR[0] |= 0x00000000; // select the source input for the external Interrupt (PA0=0000)
	EXTI->IMR |= 0x00000001;	// Interrupt request from line 0 is masked.
	EXTI->FTSR |= 0x00000001;	//Falling trigger selection for PA0.
	NVIC_EnableIRQ(EXTI0_IRQn);		//EXTI0_IRQn is the interrupt we are using for the switch
	__enable_irq();	//Enable IRQs after the setup
	
	while(1)
	{
			Systickdelay(1000);
	}
	if((GPIOA->BSRR & (1<<0))==1)
	{
		GPIOD->BSRR |= (1<<13);
	}
	else
	{
		GPIOD->BSRR |= (1<<29);
	}
}
void EXTI0_IRQHandler(void)
{
	GPIOD->BSRR |= (1<<12);
	Systickdelay(300);
	GPIOD->BSRR |= (1<<28);
	Systickdelay(300);
	GPIOD->BSRR |= (1<<12);
	Systickdelay(300);
	GPIOD->BSRR |= (1<<28);
	Systickdelay(300);
	EXTI->PR |=(1<<0);	//Pending register. (Selected trigger request occured)
}
void Systickdelay(int delayMS)
	{
		int i;
		SysTick->LOAD = 2000-1;	//Reload value =2000 for 1ms
		/*
		clock cycle is 2 Mhz
		2 000 000 in one second
		in one second 1000 ms
		in 1 ms 2 000 000 / 1000 = 2 000 -1
		*/
		SysTick->VAL = 0;
		SysTick->CTRL =(1<<2);	//	Clock source enable
		SysTick->CTRL =(1<<0);	// Counter enable
		for(i=0;i<=delayMS;i++)
		{
			while((SysTick->CTRL &(1<<16))==0);
		}
		SysTick->CTRL = 0;
	}
