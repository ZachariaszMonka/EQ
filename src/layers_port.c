/*
 * layers_port.c
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */

#include "layers_port.h"


void LP_init(void)
{
	//initialization peripheries using in port_layers library

	//GPIO
	__HAL_RCC_GPIOD_CLK_ENABLE();

	LLP_gpio.Pin = LP_pin_LED_BLUE | LP_pin_LED_GREEN
			| LP_pin_LED_ORANGE | LP_pin_LED_RED;
	LLP_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	LLP_gpio.Pull = GPIO_NOPULL;
	LLP_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LP_port_LED, &LLP_gpio);
	//GPIO END

	//VARIABLE
	LLP_led_tab[LP_LED_BLUE]   = LP_LED_OFF;
	LLP_led_tab[LP_LED_RED]    = LP_LED_OFF;
	LLP_led_tab[LP_LED_ORANGE] = LP_LED_OFF;
	LLP_led_tab[LP_LED_GREEN]  = LP_LED_OFF;
	LLP_tim10_cycle = 0;
	//VARIABLE END

	//timer 10 (100ms)

	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	__HAL_RCC_TIM10_CLK_ENABLE();

	LLP_tim10.Instance = TIM10;
	LLP_tim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; //96MHz
	LLP_tim10.Init.Prescaler = 48000-1; //2kHz
	LLP_tim10.Init.CounterMode = TIM_COUNTERMODE_UP;
	LLP_tim10.Init.Period = 2*100-1;
	LLP_tim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_Base_Init(&LLP_tim10);
	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
	HAL_TIM_Base_Start_IT(&LLP_tim10);
	//end timer 10
}

void LP_LED(LP_LED_COLOR color, LP_LED_STATUS status)
{
	//eg. LP_LED(LP_LED_ORANGE, LP_LED_ON);

	LLP_led_tab[color] = status;
	uint16_t pin;
	switch (color)
	{
		case LP_LED_BLUE:
			pin = LP_pin_LED_BLUE;
			break;
		case LP_LED_RED:
			pin = LP_pin_LED_RED;
			break;
		case LP_LED_ORANGE:
			pin = LP_pin_LED_ORANGE;
			break;
		case LP_LED_GREEN:
			pin = LP_pin_LED_GREEN;
			break;
	}

	if(status == LP_LED_TOGLE)
	{
		HAL_GPIO_TogglePin(LP_port_LED, pin);
	}
	else if(status == LP_LED_ON)
	{
		HAL_GPIO_WritePin(LP_port_LED, pin, SET);
	}
	else
	{
		HAL_GPIO_WritePin(LP_port_LED, pin, RESET);
	}
}

volatile void LLP_iunerrup_tim10(void)
{
	if(LLP_tim10_cycle++ == 5)
	{
		LLP_tim10_cycle = 0;

		if(LLP_led_tab[LP_LED_BLUE] == LP_LED_BLINK_1Hz)
			HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_BLUE);
		if(LLP_led_tab[LP_LED_GREEN] == LP_LED_BLINK_1Hz)
			HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_GREEN);
		if(LLP_led_tab[LP_LED_ORANGE] == LP_LED_BLINK_1Hz)
			HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_ORANGE);
		if(LLP_led_tab[LP_LED_RED] == LP_LED_BLINK_1Hz)
			HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_RED);
	}

	if(LLP_led_tab[LP_LED_BLUE] == LP_LED_BLINK_5Hz)
		HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_BLUE);
	if(LLP_led_tab[LP_LED_GREEN] == LP_LED_BLINK_5Hz)
		HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_GREEN);
	if(LLP_led_tab[LP_LED_ORANGE] == LP_LED_BLINK_5Hz)
		HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_ORANGE);
	if(LLP_led_tab[LP_LED_RED] == LP_LED_BLINK_5Hz)
		HAL_GPIO_TogglePin(LP_port_LED, LP_pin_LED_RED);
}


//void LP_LED()

