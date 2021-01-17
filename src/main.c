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

	VS1003b_Init();
	VS1003b_Set_Freq_Mult(SC_MULT_4_XTALI_MASK);


	LP_SPI_high_speed();



	while(1)
	{

	}

}


