/*
 * NVIC_program.c
 *
 *  Created on: Aug 17, 2022
 *      Author: FAROUK
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"


#include	"../Inc/MCAL/NVIC/NVIC_private.h"
#include	"../Inc/MCAL/NVIC/NVIC_config.h"
#include	"../Inc/MCAL/NVIC/NVIC_interface.h"

void	MNVIC_voidInit				(void)
{
	#ifndef	SCB_AIRCR
		#define	SCB_AIRCR		*((volatile u32 *)(0xE000ED00 + 0x0C))
	#endif
	SCB_AIRCR = MNVIC_GRP_SUB;
}
void	MNVIC_voidEnableInterrupt	(u8 Copy_u8IntNum) //55
{
	/*		Ranage	Check 		*/
	if(Copy_u8IntNum < 32)
	{
		NVIC_ISER0 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 64)
	{
		Copy_u8IntNum -= 32 ;
		NVIC_ISER1 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 86)
	{
		Copy_u8IntNum -= 64 ;
		NVIC_ISER2 = (1<<Copy_u8IntNum);
	}else{		/*	return Error 			*/}
}
void	MNVIC_voidDisableInterrupt	(u8 Copy_u8IntNum)
{
	/*		Ranage	Check 		*/
	if(Copy_u8IntNum < 32)
	{
		NVIC_ICER0 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 64)
	{
		Copy_u8IntNum -= 32 ;
		NVIC_ICER1 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 86)
	{
		Copy_u8IntNum -= 64 ;
		NVIC_ICER2 = (1<<Copy_u8IntNum);
	}else{		/*	return Error 			*/}
}
void	MNVIC_voidSetPendingFlag	(u8 Copy_u8IntNum)
{
	/*		Ranage	Check 		*/
	if(Copy_u8IntNum < 32)
	{
		NVIC_ISPR0 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 64)
	{
		Copy_u8IntNum -= 32 ;
		NVIC_ISPR1 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 86)
	{
		Copy_u8IntNum -= 64 ;
		NVIC_ISPR2 = (1<<Copy_u8IntNum);
	}else{		/*	return Error 			*/}
}
void	MNVIC_voidClearPendingFlag	(u8 Copy_u8IntNum)
{
	/*		Ranage	Check 		*/
	if(Copy_u8IntNum < 32)
	{
		NVIC_ICPR0 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 64)
	{
		Copy_u8IntNum -= 32 ;
		NVIC_ICPR1 = (1<<Copy_u8IntNum);
	}else if(Copy_u8IntNum < 86)
	{
		Copy_u8IntNum -= 64 ;
		NVIC_ICPR2 = (1<<Copy_u8IntNum);
	}else{		/*	return Error 			*/}
}
u8		MNVIC_u8GetActiveFlag		(u8 Copy_u8IntNum)
{
	u8 Local_u8Value = 0x55 ;
	/*		Ranage	Check 		*/
	if(Copy_u8IntNum < 32)
	{
		Local_u8Value	=	GET_BIT(NVIC_IAPR0,Copy_u8IntNum);
	}else if(Copy_u8IntNum < 64)
	{
		Copy_u8IntNum -= 32 ;
		Local_u8Value	=	GET_BIT(NVIC_IAPR1,Copy_u8IntNum);
	}else if(Copy_u8IntNum < 86)
	{
		Copy_u8IntNum -= 64 ;
		Local_u8Value	=	GET_BIT(NVIC_IAPR2,Copy_u8IntNum);
	}else{		/*	return Error 			*/}
	return Local_u8Value;
}


void	MNVIC_voidSetPriority		(u8 Copy_u8IntNum,u8 Copy_u8Priority)
{
	/*		Range Check 				*/
	if(Copy_u8IntNum < 82)
	{
		NVIC_IPR[Copy_u8IntNum] =	(Copy_u8Priority<<4);
	}

}

