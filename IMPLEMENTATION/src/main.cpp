/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "clockconfig.h"
#include "EXTI.h"


custom_libraries::clock_config system_clock;
bool toggle = false;

extern "C" void EXTI3_IRQHandler(void){
	if(EXTI->PR & EXTI_PR_PR3){
		EXTI->PR |= EXTI_PR_PR3;
		toggle = true;
	}
}

int main(void)
{
	system_clock.initialize();
	//enable SYSCFG RCG
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	//enable GPIOA RCC and GPIOE RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
	//select actual ext_int pin in interrupt system configuration register.
	SYSCFG->EXTICR[0] = ~SYSCFG_EXTICR1_EXTI3;
	SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PE;
	//unmask the interrupt
	EXTI->IMR |= EXTI_IMR_MR3;
	//Falling trigger selection
	EXTI->FTSR |= EXTI_FTSR_TR3;

	//Set interrupt line to input pull_up
	GPIOE->MODER &= ~GPIO_MODER_MODER3;
	GPIOE->PUPDR |= GPIO_PUPDR_PUPDR3_0;

	//set GPIOA6 to output
	GPIOA->MODER |= GPIO_MODER_MODER6_0;
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_1;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_6;

	NVIC_SetPriority(EXTI3_IRQn,0x00);
	NVIC_EnableIRQ(EXTI3_IRQn);





	while(1){

		if(toggle == true){
			GPIOA->ODR ^= (1<<6);
			toggle = false;
		}
	}
}
