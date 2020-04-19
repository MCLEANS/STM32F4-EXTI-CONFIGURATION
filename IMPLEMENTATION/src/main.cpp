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
custom_libraries::edge response_edge = custom_libraries::RISING;
custom_libraries::_EXTI button(GPIOE,3,response_edge);
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
	button.initialize();


	//enable GPIOA RCC
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
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
