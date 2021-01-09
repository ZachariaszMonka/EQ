/*
 * stm32f4xx_it.c
 * interrup function
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f4xx_it.h"

#include "layers_port.h" //TODO

void SysTick_Handler(void)
{

	HAL_IncTick();
	//HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	//100ms
	LLP_iunerrup_tim10();
	HAL_TIM_IRQHandler(&LLP_tim10);

}
