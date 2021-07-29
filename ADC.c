#include "stm32f407xx.h"
void ADC_Init();
int ADC_Read(void);
void delay(int delayMS);
void ADC_Conversion(void);
int ADC_Data;

int main()
{
	ADC_Init();
	while(1)
	{
	ADC_Conversion();
	//GPIOA->MODER |= 0x00000003;
	ADC_Data = ADC_Read();
	//GPIOA->AFR[0] |= 0x00000007;
	delay(1000);
	}
}

void ADC_Init()
{
	RCC->APB2ENR |= (1<<8); // ADC1 Clock
	RCC->AHB1ENR |= (1<<0); //GPIO A Clock
	GPIOA->MODER |= 0x00000003; //GPIOA Port bit as Analog mode for potentiometer (PA0)
	ADC1->CR2 &= ~(1<<0); //ADC converter (ADON) Enable
	ADC1->CR1 |= (1<<24);
	ADC1->SQR3 |= 0;
	ADC1->CR2 |=(1<<0); //ADC converter (ADON) Enable
}

void ADC_Conversion(void)
{
		ADC1->CR2 |=(1<<30); //Start ADC Conversion
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

int ADC_Read()
{
	while(!(ADC1->SR)&(1<<1))
	{
	}
		return ADC1->DR;
}

void delay(int delayMS)
{
	int i;
	for(;delayMS>0;delayMS--)
	for(i=0;i<3196;i++);
}