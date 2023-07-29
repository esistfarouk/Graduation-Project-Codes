/*
 * KEYPAD_config.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_

/*
 * Configurations Parameter for Keypad Type
 */
#define ROW_SIZE 4
#define COL_SIZE 4

/*
 * Configurations Parameter for Keypad Connection
 */
#define KPD_PORT    GPIO_U8_PORTB

#define COL_START   GPIO_U8_PIN0		/* First Column is PIN8 */
#define COL_END     GPIO_U8_PIN3		/* Last  Column is PIN11 */
#define ROW_START   GPIO_U8_PIN4		/* First Row    is PIN12 */
#define ROW_END     GPIO_U8_PIN7		/* Last  Row    is PIN15 */




#endif /* HAL_KPD_KPD_CONFIG_H_ */
