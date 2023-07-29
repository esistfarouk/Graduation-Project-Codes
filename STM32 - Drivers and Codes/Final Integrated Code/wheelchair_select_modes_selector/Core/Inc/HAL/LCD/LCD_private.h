/*
 * LCD_private.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Nadeen
 */

#ifndef HAL_LCD_LCD_PRIVATE_H_
#define HAL_LCD_LCD_PRIVATE_H_

/*
 * Instructions / Commands
 */
#define LCD_CLEAR             0x01 /* replace all characters with ASCII 'space'     */
#define LCD_RETURN_HOME       0x02 /* return cursor to first position on first line */
#define LCD_ENTRY_MODE        0x06 /* shift cursor from left to right on read/write */
#define LCD_DISPLAY_OFF       0x08 /* turn display off                              */
#define LCD_DISPLAY_ON        0x0C /* display on, cursor off, don't blink character */
#define LCD_RESET       	  0x30 /* reset the LCD                                 */
#define LCD_SET_8BITS_2LINES  0x38 /* 8-bit data, 2-line display, 5 x 7 font        */
#define LCD_CURSOR_OFFSET     0x80 /* set cursor position                           */


#endif /* HAL_LCD_LCD_PRIVATE_H_ */
