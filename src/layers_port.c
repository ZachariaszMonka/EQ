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
	//VARIABLE END

	//TODO timer 125ms
}

void LP_LED(LP_LED_COLOR color, LP_LED_STATUS status)
{
	//eg. LP_LED(LP_LED_ORANGE, LP_LED_ON);

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

//void LP_LED()

