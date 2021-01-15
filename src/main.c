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

	uint8_t tx_buf[] = {0, 1, 2, 3, 4 };
	uint8_t rx_buf[] = {1, 1, 1, 1, 1 };

	LP_LED(LP_LED_ORANGE, LP_LED_ON);
	while(1)
	{

		LLP_SPI_CS_active();
		LLP_SPI_read_write(tx_buf, rx_buf, 4);
		LLP_SPI_CS_inactive();
		LP_Delay(5);

	}
}



