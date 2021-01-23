
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

	LP_init();





	//TEST
	__HAL_RCC_TIM2_CLK_ENABLE();
	tim2.Instance = TIM2;
	tim2.Init.Period = 9;
	tim2.Init.Prescaler = 199;
	tim2.Init.ClockDivision = 1;
	tim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	tim2.Init.RepetitionCounter = 0;
	tim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;


	HAL_TIM_Base_Init(&tim2);

	TIM_ClockConfigTypeDef timclk;
	timclk.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&tim2,&timclk);

	TIM_MasterConfigTypeDef sMasterConfig = {0};
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&tim2, &sMasterConfig);

	HAL_TIM_Base_Start(&tim2);




	//TEST END

	uint16_t adc[10];
	HAL_ADC_Start(&LP_ADC);
	HAL_ADC_Start_DMA(&LP_ADC, adc,10);

	while(1)
	{
		//HAL_ADC_Start(&LP_ADC);//triger //test only todo tim1
		HAL_Delay(1);
	}
}
