/*
 * STK_interface.h
 *
 *  Created on: Aug 21, 2022
 *      Author: FAROUK
 */

#ifndef MCAL_STK_STK_INTERFACE_H_
#define MCAL_STK_STK_INTERFACE_H_


void MSTK_voidInit(void);
void MSTK_voidSetBusyWait(u32 copy_u32Ticks); //delay
void MSTK_voidSetIntervalSingle(u32 copy_u32Ticks, void (*copy_pf)(void)); //call the function one time after every certain number of ticks
void MSTK_voidSetIntervalPeriodic(u32 copy_u32Ticks, void (*copy_pf)(void)); //call the function every certain number of ticks
void MSTK_voidStopInterval(void);
u32 MSTK_u32GetElapsedTime(void);
u32 MSTK_u32GetRemainingTime(void);

#endif /* MCAL_STK_STK_INTERFACE_H_ */
