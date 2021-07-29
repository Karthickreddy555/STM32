#include "stm32f407xx.h"
#include <stdio.h>
void USART2_Init(void);
void USART2_Write(int ch);
void delay(int delayMS);
char USART2_Read(void);
//uint32_t USART_BRR( uint32_t clock, uint32_t baud );
int main(void)
{
	char c;
	RCC->AHB1ENR |= (1<<0);
	GPIOA->MODER |= (1<<24);
	USART2_Init();
	while(1)
	{
//		USART_BRR(16000000,9600);
		c=USART2_Read();
		if(c == 'a')
		{
				GPIOA->BSRR |= (1<<12); //Led on
		}
		else if(c == 'b')
		{
			GPIOA->BSRR |= (1<<28);  //Led off
		}
		
		USART2_Write('H');
		USART2_Write('E');
		USART2_Write('L');
		USART2_Write('L');
		USART2_Write('O');	
		delay(100);
		
		
	}
}

void USART2_Init(void)
{
	RCC->AHB1ENR |= (1<<0);
	RCC->APB1ENR |= (1<<17);
	USART2->CR1 |= (1<<13);  //USART Enable
	USART1->BRR = 0x104;    //Set Baudrate. 16000000/(16*9600) output in hex 
	GPIOA->AFR[0] |=0x00007700; 	
	GPIOA->MODER |= (1<<5);  //PA2 ad TX
	GPIOA->MODER |= (1<<7);	//PA3 as RX
	USART2->CR1 |= (1<<3); // TX Enable
	USART1->CR1 |= (1<<2); // RX enable


}

uint32_t USART_BRR( uint32_t clock, uint32_t baud )
{
  uint64_t clcok_x = clock * 10000ULL;
  uint64_t brr = ( ( clcok_x / baud ) + 5000ULL ) / 10000ULL;
  return brr;
}

void USART2_Write(int ch)
{
	while(!(USART2->SR & (1<<7)));
		USART2->DR = (ch&0xFF);
}

char USART2_Read(void)
{
	while(!(USART2->SR & (1<<5))){}
	  return USART2->DR;
}

void delay(int delayMS)
{
	int i;
	for(;delayMS>0;delayMS--)
		for(i=0; i<=3195; i++);
}
