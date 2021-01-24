/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/
#include"VS1003b.h"
#include"layers_port.h"


int main()
{
	LP_init();
	VS1003b_Init();

	VS1003b_Play_48kHz_Init();

	//VS1003b_set_VOL(0);
	uint16_t s1[768];
	uint16_t s2[768];
	uint16_t s3[768];
	uint16_t s4[768];



	//VS1003b_Play();
	//LP_VS1003_WRITE_DATA_wait_for_end();

	//uint16_t adc_A[768];


	//LP_ADC_read(adc_B,40000);
	//LP_ADC_wait_FULL();


	while(1)
	{
		LP_ADC_wait_FULL();
		LP_ADC_read(s1,768);

		for(uint16_t i=0; i < 768; i++)
		{
			s2[i] = s1[i] * 16;
			if(s2[i] > 32768 )
				s3[i] = s2[i] - 32768;
			else
				s3[i] = s2[i] + 32768;

			s4[i] = s3[i]<<8 | s3[i]>>8;
		}

		LP_VS1003_WRITE_DATA_wait_for_end();
		VS1003b_Play(s4,768);

	}
}



