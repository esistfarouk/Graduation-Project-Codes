/*
 * KEYPAD_private.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#ifndef HAL_KPD_KPD_PRIVATE_H_
#define HAL_KPD_KPD_PRIVATE_H_

/* Keypad mapping to actual values on keypad hardware */
const u8 global_A_u8_SwitchVal[ROW_SIZE][COL_SIZE] =
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}
};


#endif /* HAL_KPD_KPD_PRIVATE_H_ */
