/*
 * layers_port.h
 *
 * @author  Lucjan Maciej, Zachariasz Monka
 *
 */

#ifndef LAYERS_PORT_H_
#define LAYERS_PORT_H_

#ifndef includestm32f4xx
	#define includestm32f4xx_h_
	#include "stm32f4xx.h"
#endif //includestm32f4xx_h_

//TODO encapsulation LLP

#define LP_pin_LED_BLUE GPIO_PIN_15
#define LP_pin_LED_RED GPIO_PIN_14
#define LP_pin_LED_ORANGE GPIO_PIN_13
#define LP_pin_LED_GREEN GPIO_PIN_12

#define LP_port_LED GPIOD


GPIO_InitTypeDef LLP_gpio;

typedef enum
{
	LP_LED_OFF = 0U,
	LP_LED_ON = 1U,
	LP_LED_TOGLE = 2U,
	LP_LED_BLINK_1Hz = 3U, //TODO
	LP_LED_BLINK_4Hz = 4U, //TODO
} LP_LED_STATUS;

typedef enum
{
	LP_LED_BLUE = 0U,
	LP_LED_RED = 1U,
	LP_LED_ORANGE = 2U,
	LP_LED_GREEN = 3U,
} LP_LED_COLOR;

LP_LED_STATUS LLP_led_tab[4];



void LP_init(void);
void LP_LED(LP_LED_COLOR color, LP_LED_STATUS status);

#endif // LAYERS_PORT_H_
