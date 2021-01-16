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

	LP_init();

	LLP_SPI_RES_active();
	LP_Delay(5);
	LLP_SPI_RES_inactive();
	LP_Delay(5);
	LP_VS1003_register_read(0);


	uint16_t output[] = {0,0,0,0,0};


	output[0] = LP_VS1003_register_read(0);
	test_sin();
	while(1){
		output[0] = LP_VS1003_register_read(0);
		output[1] = LP_VS1003_register_read(0);
		output[2] = LP_VS1003_register_read(0);
		output[3] = LP_VS1003_register_read(0);
		output[4] = LP_VS1003_register_read(0);

	}

}


