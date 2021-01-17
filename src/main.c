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
	LP_VS1003_register_read(0); //first data is lost
	LP_VS1003_set_bit(SCI_MODE,SM_TESTS);
	LP_VS1003_set_bit(SCI_MODE,SM_SDISHARE);
	LP_Delay(10);

	uint16_t buff[] = {0xaaaa, 0x5555,0x0000,0xffff,0x0001,0x00ff};
	LP_SPI_high_speed();

	while(1)
	{
		LP_VS1003_WRITE_DATA(buff,sizeof(buff)/2);
		LP_Delay(10);
	}

}


