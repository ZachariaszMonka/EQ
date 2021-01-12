/*
 * layers_port.c
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */

#include "layers_port.h"


void LP_init(void)
{
	HAL_Init();
	SystemClock_Config();
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

void SystemClock_Config(void)
{
	#define SYSCLK_CLOCK 96000000UL
	#define HCLK_CLOCK 96000000UL
	#define ETHERNET_PTP_CLOCK 96000000UL
	#define SYSTEM_TIMER_CLOCK 96000000UL
	#define FCLK_CLOCK 96000000UL
	#define APD1_PERIPH_CLOCK 48000000UL
	#define APD1_TIMER_CLOCK 96000000UL
	#define APD2_PERIPH_CLOCK 96000000UL
	#define APD2_TIMER_CLOCK 96000000UL
	#define I2S_CLOCK 48000000UL

	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	__HAL_RCC_SYSCFG_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 96;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	*/
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK
							  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
	{
		Error_Handler();
	}

	if (HAL_SYSTICK_Config(SYSCLK_CLOCK/1000UL) != HAL_OK)
	{
		Error_Handler();
	}
}

	void Error_Handler(void)
{

}


//void LP_LED()

