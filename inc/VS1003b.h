/*
 * VS1003b.h
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */
#ifndef VS1003b_H_
#define VS1003b_H_

#include "layers_port.h"


//SCI Registers
#define SCI_MODE		0x0
#define SCI_STATUS		0x1
#define SCI_BASS		0x2
#define SCI_CLOCKF		0x3
#define SCI_DECODE_TIME	0x4
#define SCI_AUDATA		0x5
#define SCI_WRAM		0x6
#define SCI_WRAMADDR	0x7
#define SCI_HDAT0		0x8
#define SCI_HDAT1		0x9
#define SCI_AIADD		0xA
#define SCI_VOL			0xB
#define SCI_AICTRL0		0xC
#define SCI_AICTRL1		0xD
#define SCI_AICTRL2		0xE
#define SCI_AICTRL3		0xF

//SCI_MODE bits
#define SM_DIFF			(1<<0)
#define SM_SETTOZERO	(1<<1)
#define SM_RESET		(1<<2)
#define SM_OUTOFWAV		(1<<3)
#define SM_PDOWN 		(1<<4)
#define SM_TESTS		(1<<5)
#define SM_STREAM		(1<<6)
#define SM_SETTOZERO2	(1<<7)
#define SM_DACT			(1<<8)
#define SM_SDIORD		(1<<9)
#define SM_SDISHARE		(1<<10)
#define SM_SDINEW		(1<<11)
#define SM_ADPCM		(1<<12)
#define SM_ADPCM_HP		(1<<13)
#define SM_LINE_IN		(1<<14)

//SCI_STATUS

//SCI_BASS

//SCI_CLOCKF_MULT
#define SC_MULT_XTALI_MASK		0x0000
#define SC_MULT_1_5_xXTALI_MASK	0x2000
#define SC_MULT_2_XTALI_MASK	0x4000
#define SC_MULT_2_5_XTALI_MASK	0x6000
#define SC_MULT_3_XTALI_MASK	0x8000
#define SC_MULT_3_5_XTALI_MASK	0xA000
#define SC_MULT_4_XTALI_MASK	0xC000
#define SC_MULT_4_5_XTALI_MASK	0xF000

//SCI_CLOCKF_ADD
#define SC_ADD_MASK				0x0000
#define SC_0_5_ADD_MASK			0x0800
#define SC_1_ADD_MASK			0x1000
#define SC_1_5_ADD_MASK			0x1800

//SCI_CLOCKF_FREQ
#define SC_12_288Mhz 			1072





void VS1003b_Init();
void VS1003b_Record();
void VS1003b_Play();
void VS1003b_test_sine();		//Sin test 5168Hz  //5sec
void VS1003b_Set_Freq_Mult(uint16_t Mult);


#endif	//VS1003b_H_
