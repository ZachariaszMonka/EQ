/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/

#include "layers_port.h"
#include "VS1003b.h"

int main(void)
{
	uint16_t buff_tx [512] = {0,1,2,3,4,5,6,7,8,9,0xffff,0xf000};
	uint16_t buff_rx [512];
	VS1003b_Init();
	VS1003b_Set_Freq_Mult(SC_MULT_4_XTALI_MASK);


	LP_SPI_high_speed();

	//LP_VS1003_WRITE_DATA(buff_tx,500);



	while(1)
	{
		HAL_SPI_DMAStop(&LLP_hspi4);
		HAL_SPI_TransmitReceive_DMA(&LLP_hspi4,buff_tx,buff_rx,50);
		LP_Delay(2);


	}

}


