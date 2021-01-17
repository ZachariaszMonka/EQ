/*
 * VS1003b.c
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */

#include "VS1003b.h"

void VS1003b_Init()
{
	LP_init();
	LP_VS1003_Hardware_reset();
	LP_VS1003_set_bit(SCI_MODE,SM_SDISHARE);					//turn off xDCS turn on xCS to both SCI and SDI
}
void VS1003b_Set_Freq_Mult(uint16_t Mult)
{
	//basic clock Frequency: 12.288 Mhz
	//Multiplication1 up to 4.5 with 0.5 step
	// use prefix SC_MULT_ to chose
	LP_VS1003_set_bit(SCI_CLOCKF,Mult);

}
//todo
void VS1003b_Record()
{
	//LP_VS1003_register_write();

}
//todo
void VS1003b_Play()
{


}

void VS1003b_test_sine()		//Sin test 5168Hz  ///5s
{
	uint8_t input[] = {0x53,0xEF,0x6E,0x7E,0x0,0x0,0x0,0x0};  	//turn on sequence
	uint8_t input2[] = {0x45,0x78,0x69,0x74,0x0,0x0,0x0,0x0};	//turn off sequence
	LP_init();
	LP_VS1003_Hardware_reset();									//Reset
	LP_VS1003_set_bit(SCI_MODE,SM_TESTS);						//turn on tests option
	LP_VS1003_set_bit(SCI_MODE,SM_SDISHARE);					//turn off xDCS turn on xCS to both SCI and SDI
	LP_VS1003_WRITE_DATA(input,sizeof(input));
	LP_Delay(5000);
	LP_VS1003_WRITE_DATA(input2,sizeof(input2));
}


