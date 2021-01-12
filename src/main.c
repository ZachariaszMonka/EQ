/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
//#include "stm32f411e_discovery.h"
#include "layers_port.h"


int main(void)
{

	LP_init();

	LP_LED(LP_LED_RED, LP_LED_BLINK_5Hz);
	LP_LED(LP_LED_ORANGE, LP_LED_BLINK_1Hz);
	LP_LED(LP_LED_BLUE, LP_LED_OFF);
	LP_LED(LP_LED_GREEN, LP_LED_ON);

	while(1)
	{

	}
}



