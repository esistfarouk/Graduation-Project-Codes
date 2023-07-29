/*
 * Led_config.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Asmaa Hashim
 */

#include "../Inc/HAL/LED/Led_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"

Led_info   Leds_data[MAX_NUM_OFF_LEDS] =
{
	{GPIO_U8_PORTA , GPIO_U8_PIN0 , LED_OFF},
	{GPIO_U8_PORTA , GPIO_U8_PIN1 , LED_OFF},
	{GPIO_U8_PORTA , GPIO_U8_PIN2 , LED_OFF},
 };
