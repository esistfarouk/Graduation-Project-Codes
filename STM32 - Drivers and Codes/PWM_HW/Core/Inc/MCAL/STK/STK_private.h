/*
 * STK_private.h
 *
 *  Created on: Aug 21, 2022
 *      Author: FAROUK
 */

#ifndef MCAL_STK_STK_PRIVATE_H_
#define MCAL_STK_STK_PRIVATE_H_


typedef struct
{
	volatile u32 CTRL;
	volatile u32 LOAD;
	volatile u32 VAL;
}STK_t;

#define STK ((STK_t *)0xE000E010)

#define MSTK_SRC_AHB 0
#define MSTK_SRC_AHB_8 1

#define MSTK_SINGLE_INTERVAL 0
#define MSTK_PERIODIC_INTERVAL 1

#endif /* MCAL_STK_STK_PRIVATE_H_ */
