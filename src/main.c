/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/

#include "layers_port.h"


int main(void)
{

	LP_init();

	LLP_SPI_RES_active();
	LP_Delay(5);
	LLP_SPI_RES_inactive();
	LP_Delay(50);
	uint16_t output[] = {0,0,0,0,0,0,0};
	while(1)
	{
		output[0] = LP_VS1003_register_read(0);
		output[1] = LP_VS1003_register_read(1);
		output[2] = LP_VS1003_register_read(2);
		output[3] = LP_VS1003_register_read(3);

		LP_Delay(10);
		LP_VS1003_register_write(3,0xC430);

	}
}
