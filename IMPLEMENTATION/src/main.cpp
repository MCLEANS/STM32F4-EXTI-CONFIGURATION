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


custom_libraries::clock_config system_clock;

int main(void)
{
	system_clock.initialize();

	while(1){

	}
}
