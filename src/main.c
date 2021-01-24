/**
  ******************************************************************************
  * @file    main.c
  * @author  Lucjan Maciej, Zachariasz Monka
  * @brief   main function.
  ******************************************************************************
*/
#include"VS1003b.h"



int main()
{
	LP_init();
	VS1003b_Init();
	VS1003b_Play_48kHz_Init();
	VS1003b_Play();
	VS1003b_END_Play();



}


