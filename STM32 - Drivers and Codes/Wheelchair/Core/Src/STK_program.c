/*
 * STK_program.c
 *
 *  Created on: Aug 21, 2022
 *      Author: Nadeen
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"


#include	"../Inc/MCAL/STK/STK_private.h"
#include	"../Inc/MCAL/STK/STK_config.h"
#include	"../Inc/MCAL/STK/STK_interface.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

static void (* SysTick_CallBack)(void)=NULL;
static u8 MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;

void MSTK_voidInit(void)
{
#if MSTK_CLOCK_SOURCE == MSTK_SRC_AHB
STK->CTRL = 0x00000004;
#elif MSTK_CLOCK_SOURCE == MSTK_SRC_AHB_8
STK->CTRL = 0x00000000;
#else
#error "Wrong Clock Source Prescaler"
#endif
}
void MSTK_voidSetBusyWait(u32 copy_u32Ticks) //delay
{
	/*load ticks to load register*/
	STK->LOAD = copy_u32Ticks;
	/*Start Timer*/
	SET_BIT(STK->CTRL,0);
	/*wait till flag is raised*/
	while((GET_BIT(STK->CTRL,16))==0)
	{
		asm("NOP");
	}
	/*stop timer*/
	CLR_BIT(STK->CTRL,0);
	/*Re initialization of LOAD and VAL*/
	STK->LOAD=0;
	STK->VAL=0;
}
void MSTK_voidSetIntervalSingle(u32 copy_u32Ticks, void (*copy_pf)(void)) //call the function one time after every certain number of ticks
{
	/*Disable Timer*/
	CLR_BIT(STK->CTRL,0);
	STK->VAL=0;
	/*load ticks to load register*/
	STK->LOAD = copy_u32Ticks;
	/*start timer*/
	SET_BIT(STK->CTRL,0);
	/*save CallBack*/
	SysTick_CallBack = copy_pf;
	/*set mode to periodic*/
	MSTK_u8ModeOfInterval=MSTK_SINGLE_INTERVAL;
	/*enable interrupt*/
	SET_BIT(STK->CTRL,1);
}
void MSTK_voidSetIntervalPeriodic(u32 copy_u32Ticks, void (*copy_pf)(void)) //call the function every certain number of ticks
{
	/*load ticks to load register*/
	STK->LOAD = copy_u32Ticks-1;
	/*start timer*/
	SET_BIT(STK->CTRL,0);
	/*save CallBack*/
	SysTick_CallBack = copy_pf;
	/*set mode to periodic*/
	MSTK_u8ModeOfInterval=MSTK_PERIODIC_INTERVAL;
	/*enable interrupt*/
	SET_BIT(STK->CTRL,1);
}
void MSTK_voidStopInterval(void)
{
	/*Diasble Interrupt*/
	CLR_BIT(STK->CTRL,1);
	/*Disable Timer*/
	CLR_BIT(STK->CTRL,0);
	/*Re initialization of LOAD and VAL*/
	STK->LOAD=0;
	STK->VAL=0;
}
u32 MSTK_u32GetElapsedTime(void)
{
	u32 Local_u32ElapsedTime;
	Local_u32ElapsedTime = ((STK->LOAD)-(STK->VAL));
	return Local_u32ElapsedTime;
}
u32 MSTK_u32GetRemainingTime(void)
{
	u32 Local_u32RemainingTime;
	Local_u32RemainingTime = (STK->VAL);
	return Local_u32RemainingTime;
}
void SysTick_Handler(void)
{
	//u8 Local_u8Temp;
	/*if single*/
	if(MSTK_u8ModeOfInterval==MSTK_SINGLE_INTERVAL)
	{
		/*disable interrupt*/
		CLR_BIT(STK->CTRL,1);
		/*stop timer*/
		CLR_BIT(STK->CTRL,0);
		/*Re initialization of LOAD and VAL*/
		STK->LOAD=0;
		STK->VAL=0;
	}
	/*call back*/
	SysTick_CallBack();
	/*clear interrupt flag by reading it*/
	//Local_u8Temp=(GET_BIT(STK->CTRL,16));
}
