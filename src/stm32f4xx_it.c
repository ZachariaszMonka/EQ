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
	//todo check source of interrupt (tim10?)
	//100ms
	LLP_iunerrup_tim10();
	HAL_TIM_IRQHandler(&LLP_tim10);

}

void DMA2_Stream0_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&LLP_dma_spi4_rx);
}


void DMA2_Stream1_IRQHandler(void)
{

	LLP_iunerrup_dma_tx();
	HAL_DMA_IRQHandler(&LLP_dma_spi4_tx);
}

void DMA2_Stream4_IRQHandler(void)
{
	HAL_DMA_IRQHandler(&LLP_dma_adc);
}
void EXTI1_IRQHandler(void)
{
	LLP_interrup_EXTI1();
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}
