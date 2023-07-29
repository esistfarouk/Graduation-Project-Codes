/*
 * LCD_program.c
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/HAL/LCD/LCD_interface.h"
#include "../Inc/HAL/LCD/LCD_config.h"
#include "../Inc/HAL/LCD/LCD_private.h"

#include "../Inc/MCAL/STK/STK_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/HAL/STP/STP_interface.h"


void HLCD_voidInit(void) {
	/* Set LCD Pin Directions */
	/* Set Data Port as output */
	MDIO_voidSetPortDirection(LCD_DATA_PORT, GPIO_U8_OUTPUT_PP_2MHZ);
		/* Set Control pins as output */
	MDIO_voidSetPinDirection(LCD_CONTROL_PORT, RS, GPIO_U8_OUTPUT_PP_2MHZ);
	MDIO_voidSetPinDirection(LCD_CONTROL_PORT, RW, GPIO_U8_OUTPUT_PP_2MHZ);
	MDIO_voidSetPinDirection(LCD_CONTROL_PORT, EN, GPIO_U8_OUTPUT_PP_2MHZ);

	/* Delay 30ms to ensure the initialization of the LCD driver */
	//_delay_ms(30);
	MSTK_voidSetBusyWait(30000);
	/* Return Home  */
	HLCD_voidSendCommand(LCD_RETURN_HOME);
	//_delay_ms(15);
	MSTK_voidSetBusyWait(15000);
	/* Function Set  */
	HLCD_voidSendCommand(LCD_SET_8BITS_2LINES);
	//_delay_ms(1);
	MSTK_voidSetBusyWait(1000);
	/* Display ON OFF Control */
	HLCD_voidSendCommand(LCD_DISPLAY_ON);
	//_delay_ms(1);
	MSTK_voidSetBusyWait(1000);
	/* Clear Display */
	HLCD_voidSendCommand(LCD_CLEAR);
	//_delay_ms(15);
	MSTK_voidSetBusyWait(15000);
	/* Entry Mode Set  */
	HLCD_voidSendCommand(LCD_ENTRY_MODE);
	//_delay_ms(2);
	MSTK_voidSetBusyWait(2000);
}

void HLCD_voidSendCommand(u8 copy_u8_CmdID) {

	/* Set RS to LOW */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, RS, GPIO_U8_LOW);

	/* Set R/W to LOW */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, RW, GPIO_U8_LOW);

	/* Set E to HIGH  */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_U8_HIGH);

	/* Load Command on Data bus */
	//MDIO_voidSetPortValue(LCD_DATA_PORT, copy_u8_CmdID);
	HSTP_voidSendSync(copy_u8_CmdID);

	/* Set E to LOW */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_U8_LOW);

	/* Wait for E to settle */
	//_delay_ms(10);
	MSTK_voidSetBusyWait(10000);
	/* Set E to HIGH */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_U8_HIGH);

	/* Delay for 10ms to let the LCD execute command */
	//_delay_ms(20);
	MSTK_voidSetBusyWait(20000);
}

void HLCD_voidSendChar(u8 copy_u8_Data) {
	/* Set RS to HIGH */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, RS, GPIO_U8_HIGH);

	/* Set R/W to LOW */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, RW, GPIO_U8_LOW);

	/* Set E to HIGH */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_U8_HIGH);

	/* Load Command on Data bus */
	//MDIO_voidSetPortValue(LCD_DATA_PORT, copy_u8_Data);
	HSTP_voidSendSync(copy_u8_Data);

	/* Set E to LOW */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_U8_LOW);

	/* Wait for E to settle */
	//_delay_ms(5);
	MSTK_voidSetBusyWait(5000);
	/* Set E to HIGH */
	MDIO_voidSetPinValue(LCD_CONTROL_PORT, EN, GPIO_U8_HIGH);

	/* Delay to let the LCD Display the character */
	//_delay_ms(10);
	MSTK_voidSetBusyWait(10000);
}

void HLCD_voidSendString (u8* ptr_u8_String) {
	/* Local loop index */
	u8 u8Index = 0;
	while (ptr_u8_String[u8Index] != '\0') {
		/* Write Character on LCD */
		HLCD_voidSendChar(ptr_u8_String[u8Index]);

		/* Increment local loop index */
		u8Index++;

		/* Delay to let the LCD show the character */
		//_delay_ms(2);
		MSTK_voidSetBusyWait(2000);
	}

}

void HLCD_voidClearScreen (){
	HLCD_voidSendCommand(LCD_CLEAR);
}

void HLCD_voidGoTo (u8 copy_u8_RowID, u8 copy_u8_ColID) {
	u8 local_u8_Address;
	switch(copy_u8_RowID) {
		case 0:
			local_u8_Address = copy_u8_ColID;
			break;
		case 1:
			local_u8_Address = copy_u8_ColID + 0x40;
			break;
		case 2:
			local_u8_Address = copy_u8_ColID + 0x10;
			break;
		case 3:
			local_u8_Address = copy_u8_ColID + 0x50;
			break;
	}
	HLCD_voidSendCommand(local_u8_Address | LCD_CURSOR_OFFSET);
}

void HLCD_voidDisplayNumber (u8 copy_u8_Number) {
	s8 * localPtr_str[16] = {0};
	itoa(copy_u8_Number, (char *)localPtr_str, 10);
	HLCD_voidSendString((u8 *)localPtr_str);
}
