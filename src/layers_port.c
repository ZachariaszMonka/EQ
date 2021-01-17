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
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();

	LLP_gpio.Pin = LP_pin_LED_BLUE | LP_pin_LED_GREEN
			| LP_pin_LED_ORANGE | LP_pin_LED_RED;
	LLP_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	LLP_gpio.Pull = GPIO_NOPULL;
	LLP_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LP_port_LED, &LLP_gpio);

	LLP_gpio.Pin = LP_pin_SCK|LP_pin_MISO|LP_pin_MOSI;
	LLP_gpio.Mode = GPIO_MODE_AF_PP;
	LLP_gpio.Pull = GPIO_PULLUP;
	LLP_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	LLP_gpio.Alternate = GPIO_AF5_SPI4;
	HAL_GPIO_Init(LP_port_SPI, &LLP_gpio);

	LLP_gpio.Pin = LP_pin_DCS | LP_pin_CCS| LP_pin_RES;
	LLP_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	LLP_gpio.Pull = GPIO_NOPULL;
	LLP_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LP_port_RES, &LLP_gpio);

	LLP_gpio.Pin = LP_pin_DREQ;
	LLP_gpio.Mode = GPIO_MODE_INPUT;
	LLP_gpio.Pull = GPIO_PULLUP;
	LLP_gpio.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LP_port_RES, &LLP_gpio);


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

	//SPI4

	LP_SPI_low_speed();

	//end SPI4
}

void Error_Handler(void)
{

}

void LP_Delay(uint32_t Delay)
{
	//idea sleep MCU
	HAL_Delay(Delay);
}

void LP_SPI_low_speed(void)
//750kbps
{
	__HAL_RCC_SPI4_CLK_ENABLE();

	LLP_hspi4.Instance = SPI4;
	LLP_hspi4.Init.Mode = SPI_MODE_MASTER;
	LLP_hspi4.Init.Direction = SPI_DIRECTION_2LINES;
	LLP_hspi4.Init.DataSize = SPI_DATASIZE_16BIT;
	LLP_hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
	LLP_hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
	LLP_hspi4.Init.NSS = SPI_NSS_SOFT;
	LLP_hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	LLP_hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
	LLP_hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
	LLP_hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	LLP_hspi4.Init.CRCPolynomial = 7;
	if (HAL_SPI_Init(&LLP_hspi4) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_SPI_ENABLE(&LLP_hspi4);

}

void LP_SPI_high_speed(void)
//8Mbps
{
	__HAL_RCC_SPI4_CLK_ENABLE();

	LLP_hspi4.Instance = SPI4;
	LLP_hspi4.Init.Mode = SPI_MODE_MASTER;
	LLP_hspi4.Init.Direction = SPI_DIRECTION_2LINES;
	LLP_hspi4.Init.DataSize = SPI_DATASIZE_16BIT;
	LLP_hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
	LLP_hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
	LLP_hspi4.Init.NSS = SPI_NSS_SOFT;
	LLP_hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
	LLP_hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
	LLP_hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
	LLP_hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	LLP_hspi4.Init.CRCPolynomial = 7;
	if (HAL_SPI_Init(&LLP_hspi4) != HAL_OK)
	{
		Error_Handler();
	}

	__HAL_SPI_ENABLE(&LLP_hspi4);

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


void LLP_SPI_write(uint16_t* tx_buff , uint16_t size)
{
	HAL_SPI_Transmit(&LLP_hspi4, tx_buff, size, HAL_MAX_DELAY);
}

void LLP_SPI_read(uint16_t* rx_buff , uint16_t size)
{
	HAL_SPI_Receive(&LLP_hspi4, rx_buff, size, HAL_MAX_DELAY);
}
void LLP_SPI_read_write(uint16_t* tx_buff,uint16_t* rx_buff , uint16_t size)
{
	HAL_SPI_TransmitReceive(&LLP_hspi4, tx_buff, rx_buff, size, HAL_MAX_DELAY);
}


void LLP_SPI_CS_SCI_inactive_SDI_active(void)
{
	HAL_GPIO_WritePin(LP_port_RES, LP_pin_CCS, SET);
}
void LLP_SPI_CS_SCI_active_SDI_inactive(void)
{
	HAL_GPIO_WritePin(LP_port_RES, LP_pin_CCS, RESET);
}
void LLP_SPI_DCS_inactive(void)
{
	HAL_GPIO_WritePin(LP_port_RES, LP_pin_DCS, SET);
}
void LLP_SPI_DCS_active(void)
{
	HAL_GPIO_WritePin(LP_port_RES, LP_pin_DCS, RESET);
}
void LLP_SPI_RES_inactive(void)
{
	HAL_GPIO_WritePin(LP_port_RES, LP_pin_RES, SET);
}
void LLP_SPI_RES_active(void)
{
	HAL_GPIO_WritePin(LP_port_RES, LP_pin_RES, RESET);
}

void LLP_DREQ_WAIT(void)
{
	//idea time out
	while(HAL_GPIO_ReadPin(LP_port_RES, LP_pin_DREQ)==GPIO_PIN_RESET)
	{}
}

uint16_t LP_VS1003_register_read(uint8_t register_adres)
{
	//example use
	//output[0] = LP_VS1003_register_read(0);


	uint16_t read_mode = 0b00000011;

	LLP_DREQ_WAIT();
	LLP_SPI_CS_SCI_active_SDI_inactive();
	uint16_t send_msb,send_lsb;
	send_msb = (read_mode)<<8;
	send_lsb = (register_adres)<<0;
	uint16_t send = send_msb|send_lsb;
	LLP_SPI_write(&send,1);
	uint16_t out;
	LLP_SPI_read(&out,1);
	LLP_SPI_CS_SCI_inactive_SDI_active();
	return out;
}

void LP_VS1003_register_write(uint8_t register_adres, uint16_t data)
{
	//example use
	//LP_VS1003_register_write(3,0xC430);

	uint16_t write_mode = 0b00000010;

	LLP_DREQ_WAIT();
	LLP_SPI_CS_SCI_active_SDI_inactive();
	uint16_t send_msb,send_lsb;
	send_msb = (write_mode)<<8;
	send_lsb = (register_adres)<<0;
	uint16_t send = send_msb|send_lsb;
	LLP_SPI_write(&send,1);
	LLP_SPI_write(&data,1);
	LLP_SPI_CS_SCI_inactive_SDI_active();
}
void LP_VS1003_set_bit(uint8_t register_adres, uint16_t bit)
{
	uint8_t read_mode = 0b00000011;
	uint8_t write_mode = 0b00000010;
	uint16_t buf;
	uint16_t send_msb,send_lsb;
	uint16_t send;
	LLP_DREQ_WAIT();
	LLP_SPI_CS_SCI_active_SDI_inactive();
	send_msb = (read_mode)<<8;
	send_lsb = (register_adres)<<0;
	send = send_msb|send_lsb;
	LLP_SPI_write(&send,1);
	LLP_SPI_read(&buf,1);
	LLP_SPI_CS_SCI_inactive_SDI_active();
	buf |= bit;
	LLP_DREQ_WAIT();
	LLP_SPI_CS_SCI_active_SDI_inactive();
	send_msb = (write_mode)<<8;
	send_lsb = (register_adres)<<0;
	send = send_msb|send_lsb;
	LLP_SPI_write(&send,1);
	LLP_SPI_write(&buf,1);
	LLP_SPI_CS_SCI_inactive_SDI_active();
}

void LP_VS1003_reset_bit(uint8_t register_adres, uint16_t bit)
{
	uint8_t read_mode = 0b00000011;
	uint8_t write_mode = 0b00000010;
	uint16_t buf;
	uint16_t send_msb,send_lsb;
	uint16_t send;
	LLP_DREQ_WAIT();
	LLP_SPI_CS_SCI_active_SDI_inactive();
	send_msb = (read_mode)<<8;
	send_lsb = (register_adres)<<0;
	send = send_msb|send_lsb;
	LLP_SPI_write(&send,1);
	LLP_SPI_read(&buf,1);
	LLP_SPI_CS_SCI_inactive_SDI_active();
	buf &= ~bit;
	LLP_DREQ_WAIT();
	LLP_SPI_CS_SCI_active_SDI_inactive();
	send_msb = (write_mode)<<8;
	send_lsb = (register_adres)<<0;
	send = send_msb|send_lsb;
	LLP_SPI_write(&send,1);
	LLP_SPI_write(&buf,1);
	LLP_SPI_CS_SCI_inactive_SDI_active();
}
void LP_VS1003_WRITE_DATA(uint16_t* data,uint16_t size)
{

	uint16_t cycle = 0;
	while(size > cycle)
	{
		LLP_SPI_CS_SCI_inactive_SDI_active();
		LLP_DREQ_WAIT();  //wait to permission to send data
		if(size - cycle >=16)
		{
			LLP_SPI_write(data + cycle,16);
			cycle+=16;
		}
		else
		{
			LLP_SPI_write(data + cycle,1);
			cycle+=1;
		}
		LLP_SPI_CS_SCI_active_SDI_inactive();
	}
}

void LP_VS1003_Hardware_reset(void)
{
	LLP_SPI_RES_active();
	LP_Delay(5);
	LLP_SPI_RES_inactive();
	LP_Delay(5);
	LP_VS1003_register_read(0); //first data is lost
}
