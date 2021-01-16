/*
 * VS1003b.c
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */

#include "VS1003b.h"

//todo
void VS1003b_Record()
{
	//LP_VS1003_register_write();

}
//todo
void VS1003b_Play()
{


}

void test_sin()		//Sin test 5168Hz  ///5s
{
	uint8_t input[] = {0x53,0xEF,0x6E,0x7E,0x0,0x0,0x0,0x0};
	uint8_t input2[] = {0x45,0x78,0x69,0x74,0x0,0x0,0x0,0x0};


	LP_VS1003_set_bit(SCI_MODE,SM_TESTS);
	LP_VS1003_set_bit(SCI_MODE,SM_SDISHARE);
	LLP_DREQ_WAIT();


	// replace this SDI funkcion transmit
	LLP_SPI_CS_SCI_inactive_SDI_active();
	LLP_SPI_write(input,sizeof(input));


	LP_Delay(5000);

	LLP_DREQ_WAIT();




	LLP_SPI_write(input2,sizeof(input2));
}


