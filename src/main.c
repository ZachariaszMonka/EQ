
/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/



#include "VS1003b.h"
#include "layers_port.h"

int main(void)
{

	const uint16_t header[] =
	{0x5249, 0x4646,0xF83F, 0x0000, 0x5741,
				0x5645, 0x666d, 0x7420, 0x1400, 0x0000, 0x1100,
				0x0100, 0x401f, 0x0000, 0x7512, 0x0000,	0x0001,
				0x0400, 0x0200, 0xf901, 0x6661, 0x6374, 0x0400,
				0x0000, 0x5c1f, 0x0000, 0x6461, 0x7461, 0xBC3F,
				0x0000	};

			uint16_t buff[8192];
	uint16_t clear[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	while(1){

	VS1003b_Init();
	VS1003b_Set_Freq_Mult(SC_MULT_4_XTALI_MASK);

	LP_SPI_high_speed();
	//LP_VS1003_WRITE_DATA(header,sizeof(buff)/2);


	uint16_t w = 0, idx =0;

	//setvol////////////////////////
	LP_VS1003_register_write(SCI_BASS, 0);
	//VS1003b_Set_Freq_Mult(SC_MULT_4_XTALI_MASK);
	LP_VS1003_register_write(SCI_AICTRL0, 24);
	LP_VS1003_register_write(SCI_AICTRL1, 0);
	LP_VS1003_set_bit(SCI_MODE,SM_RESET|SM_SDISHARE|SM_SDINEW|SM_ADPCM|SM_LINE_IN);  //line in recording
	for (idx=0; idx < sizeof(header)/2; idx++) {
	buff[idx] = header[idx];
	}
	uint8_t stop = 32;
	uint16_t increment=0;
	while (stop!=0) {
		do {
			w = LP_VS1003_register_read(SCI_HDAT1);
		} while (w < 256 || w >= 896);
		while (idx < 256) {
			//w = LLP_SPI_read()
			w=LP_VS1003_register_read(SCI_HDAT0);

			buff[increment + idx++] = w;
			}
			stop -- ;
			increment +=256;
			idx =0;
			}









	VS1003b_Init();
	VS1003b_Set_Freq_Mult(SC_MULT_4_XTALI_MASK);

	LP_SPI_high_speed();
	LP_Delay(2000);
	LP_VS1003_WRITE_DATA(clear,sizeof(clear)/2);
	LP_VS1003_WRITE_DATA(buff,sizeof(buff)/2);
	LP_Delay(2000);
	LP_VS1003_WRITE_DATA(buff,sizeof(buff)/2);
	LP_Delay(2000);
	LP_VS1003_WRITE_DATA(clear,sizeof(clear)/2);
	LP_Delay(2000);
	LP_VS1003_WRITE_DATA(buff,sizeof(buff)/2);
	LP_Delay(2000);
	LP_VS1003_WRITE_DATA(buff,sizeof(buff)/2);
	while(1)
		{
			//LP_VS1003_WRITE_DATA(buff2,sizeof(buff2)/2);
			//LP_Delay(5000);
		}

	//LP_VS1003_WRITE_DATA(buff2,sizeof(buff2)/2);
	//LP_VS1003_Hardware_reset();
}
}
