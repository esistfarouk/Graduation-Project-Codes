/*
 * KEYPAD_program.c
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"


#include "../Inc/HAL/KPD/KPD_config.h"
#include "../Inc/HAL/KPD/KPD_interface.h"
#include "../Inc/HAL/KPD/KPD_private.h"


#include "../Inc/MCAL/GPIO/GPIO_interface.h"

#include "../Inc/MCAL/STK/STK_interface.h"

void H_KPD_void_Init(void)
{
	/* Set Columns as Output */
	for (u8 local_u8_PinID = COL_START; local_u8_PinID <= COL_END; local_u8_PinID++)
	{
		MDIO_voidSetPinDirection(KPD_PORT, local_u8_PinID, GPIO_U8_OUTPUT_PP_2MHZ);
	}

	/* Set Rows as Inputs & Pulled down */
	for (u8 local_u8_PinID = ROW_START; local_u8_PinID <= ROW_END; local_u8_PinID++)
	{
		MDIO_voidSetPinDirection(KPD_PORT, local_u8_PinID, GPIO_U8_INPUT_PULL_UP_DOWN );
		MDIO_voidSetPinValue(KPD_PORT, local_u8_PinID, GPIO_U8_LOW);
	}
}

u8 H_KPD_u8_GetPressedKey(void)
{
	u8 local_u8_Column;
	u8 local_u8_Row;

	/* Initialize the switch status to NOT Pressed */
	u8 local_u8_PressedKey = H_KPD_KEY_NOT_PRESSED;

	/* Looping on columns of the Key Pad */
	for (local_u8_Column = COL_START; local_u8_Column <= COL_END; local_u8_Column++)
	{
		/* Activate the Column */
		MDIO_voidSetPinValue(KPD_PORT, local_u8_Column, GPIO_U8_HIGH);
		/* Loop on the rows of the Key Pad */
		for (local_u8_Row = ROW_START; local_u8_Row <= ROW_END; local_u8_Row++)
		{
			/* Check the status of the switch */
			if (MDIO_u8GetPinValue(KPD_PORT, local_u8_Row) == 1)
			{
				/* Get the value of the currently pressed switch */
				local_u8_PressedKey = global_A_u8_SwitchVal[local_u8_Row - ROW_START][local_u8_Column - COL_START];

				/* Wait until the switch is released (Single Press) */
				while (MDIO_u8GetPinValue(KPD_PORT, local_u8_Row)==1)
				{
					;
				}
				/* Delay to avoid bouncing */
				//_delay_ms(20);
				MSTK_voidSetBusyWait(20000);
			}
		}
		/* Deactivate the Column */
		MDIO_voidSetPinValue(KPD_PORT, local_u8_Column, GPIO_U8_LOW);
		MSTK_voidSetBusyWait(1000);
	}
	return local_u8_PressedKey;
}

