
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


	uint16_t adc_A[768];
	uint16_t adc_B[768];


	LP_ADC_read(adc_B,768);

	while(1)
	{
		LP_ADC_wait_FULL();
		LP_ADC_read(adc_A,768);

		LP_ADC_wait_FULL();
		LP_ADC_read(adc_B,768);


	}
}
