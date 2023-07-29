/*
 * KEYPAD_interface.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#ifndef HAL_KPD_KPD_INTERFACE_H_
#define HAL_KPD_KPD_INTERFACE_H_

#include "../Inc/LIB/STD_TYPES.h"

#define H_KPD_KEY_NOT_PRESSED   255

/*
 * Public Function Prototypes
 */
void H_KPD_void_Init(void);

u8   H_KPD_u8_GetPressedKey(void);

#endif /* HAL_KPD_KPD_INTERFACE_H_ */
