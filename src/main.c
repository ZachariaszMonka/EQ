
/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/



#include "VS1003b.h"
#include "layers_port.h"

int main(void)
{

	LP_init();

	LP_LED(LP_LED_ORANGE,LP_LED_BLINK_5Hz);


	uint16_t adc[99];

	HAL_ADC_Start_DMA(&LP_ADC, adc,99);

	while(1)
	{
		HAL_Delay(1);
		HAL_Delay(1);
	}
}
