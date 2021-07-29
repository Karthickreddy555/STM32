
#include"stm32f4xx.h"
void delayMS(int delay);
int	main(void)
{
	RCC->AHB1ENR |= (1<<3);
	GPIOD->MODER |= (1<<24);
	
	while(1)
	{
		GPIOD-> ODR &= ~(1<<12);
		delayMS(100);
		GPIOD-> ODR |=  (1<<12);
		delayMS(100);
		
	}
	
	
}

void delayMS(int delay)
{
	int i;
	for( ; delay>0; delay--)
	for(i=0; i<=3195; i++);
	
}
