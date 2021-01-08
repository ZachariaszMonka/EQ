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


void SysTick_Handler(void)
{

	HAL_IncTick();
	//HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}
