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
	uint16_t s1[2000];
	uint16_t s2[2000];
	uint16_t s3[2000];
	uint16_t s4[2000];

	//READ 	wait for ADC
	//GREEN wait for DAC
	//BLUE  data processing
	while(1)
	{
		LP_LED(LP_LED_RED,LP_LED_OFF);
		LP_ADC_wait_FULL();
		LP_LED(LP_LED_RED,LP_LED_ON);
		LP_ADC_read(s1,2000);
		LP_LED(LP_LED_BLUE,LP_LED_ON);
		for(uint16_t i=0; i < 2000; i++)
		{
			s2[i] = s1[i] * 16;
			if(s2[i] > 32768 )
				s3[i] = s2[i] - 32768;
			else
				s3[i] = s2[i] + 32768;

			s4[i] = s3[i]<<8 | s3[i]>>8;
		}
		LP_LED(LP_LED_BLUE,LP_LED_OFF);
		LP_LED(LP_LED_GREEN,LP_LED_OFF);
		LP_VS1003_WRITE_DATA_wait_for_end();
		LP_LED(LP_LED_GREEN,LP_LED_ON);
		VS1003b_Play(s4,2000);
	}
}



