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
	uint16_t s0[2000];
	uint16_t s1[2000];
	uint16_t s2[2000];
	uint16_t s3[2000];


	//uint16_t s0[2000];

	//READ 	wait for ADC
	//GREEN wait for DAC
	//BLUE  data processing
	while(1)
	{
		LP_LED(LP_LED_RED,LP_LED_OFF);
		LP_ADC_wait_FULL();
		LP_LED(LP_LED_RED,LP_LED_ON);
		LP_ADC_read(s0,2000);

		//MIX
		uint16_t Pot1 = 250; //Pot low
		Pot1 = LP_ADC_EXTERNAL_CH_L();
		uint16_t fir1[8] = {1,1,1,1,1,1,1,1};
		uint16_t fir2[8] = {2,2,1,1,1,1,0,0};
		uint16_t fir3[8] = {2,2,2,2,0,0,0,0};
		uint16_t fir4[8] = {8,0,0,0,0,0,0,0};
		uint16_t fir[8];
		for(uint16_t i=0; i < 8; i++)
		{
			if(Pot1 < 50)
				fir[i] = fir1[i];
			if(Pot1 < 100 && Pot1 > 50)
				fir[i] = fir2[i];
			if(Pot1 < 50 && Pot1 > 100)
				fir[i] = fir3[i];
			if( Pot1 > 200)
				fir[i] = fir4[i];
		}

		LP_LED(LP_LED_BLUE,LP_LED_ON);
		//FIR

		for(uint16_t i=0; i < 2000; i++)
		{
			uint16_t temp = 0;
			for(uint16_t f=0; f < 8; f++)
			{
				if(i>=f)
				{
					temp += fir[f] * s0[i - f]/8;
				}
			}
			s2[i] = temp;
		}

		//DECODING
		for(uint16_t i=0; i < 2000; i++)
		{
			s2[i] = s2[i] * 16;
			if(s2[i] > 32768 )
				s2[i] = s2[i] - 32768;
			else
				s2[i] = s2[i] + 32768;

			s3[i] = s2[i]<<8 | s2[i]>>8;
		}

		LP_LED(LP_LED_BLUE,LP_LED_OFF);



		LP_LED(LP_LED_GREEN,LP_LED_OFF);
		LP_VS1003_WRITE_DATA_wait_for_end();
		LP_LED(LP_LED_GREEN,LP_LED_ON);
		VS1003b_Play(s3,2000);
	}
}



