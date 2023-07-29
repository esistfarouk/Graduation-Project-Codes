/*
 * LCD_interface.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#ifndef HAL_LCD_LCD_INTERFACE_H_
#define HAL_LCD_LCD_INTERFACE_H_


/*
 * Rows
 */
#define LCD_ROW0     0
#define LCD_ROW1     1

/*
 * Columns
 */
#define LCD_COL0     0
#define LCD_COL1     1
#define LCD_COL2     2
#define LCD_COL3     3
#define LCD_COL4     4
#define LCD_COL5     5
#define LCD_COL6     6
#define LCD_COL7     7
#define LCD_COL8     8
#define LCD_COL9     9
#define LCD_COL10    10
#define LCD_COL11    11
#define LCD_COL12    12
#define LCD_COL13    13
#define LCD_COL14    14
#define LCD_COL15    15


void HLCD_voidInit(void);

void HLCD_voidSendCommand(u8 Copy_u8_CmdID);

void HLCD_voidSendChar (u8 Copy_u8_Data);

void HLCD_voidSendString (u8* ptr_u8_String);

void HLCD_voidClearScreen (void);

void HLCD_voidGoTo (u8 Copy_u8_RowID, u8 Copy_u8_ColID);

void HLCD_voidDisplayNumber (u8 Copy_u8_Number);


#endif /* HAL_LCD_LCD_INTERFACE_H_ */
