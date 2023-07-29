/*
 * RCC_program.c
 *
 *  Created on: Aug 11, 2022
 *      Author: FAROUK
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/RCC/RCC_int.h"
#include "../Inc/MCAL/RCC/RCC_priv.h"
#include "../Inc/MCAL/RCC/RCC_config.h"

void MRCC_voidInit()
{
#if CLK_SOURCE == HSI
	//Turn on HSI
	MRCC_voidClkEnable(HSI);
	//Check HSI Ready
	while(MRCC_u8CheckClockReady(HSI)==NOT_READY);
	// Set Buses Prescaler
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
	// Switch to HSI Clock
	MRCC_voidSetClkSource(HSI);
	// Turn off HSE and PLL
	MRCC_voidClkDisable(HSE);
	MRCC_voidClkDisable(PLL);

#elif CLK_SOURCE == HSE
	// Turn on HSE
	MRCC_voidClkEnable(HSE);
	// Check HSE Ready
	while (MRCC_u8CheckClockReady(HSE) == NOT_READY)
		;
	// Set Buses Prescaler
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);
	// Switch to HSE Clock
	MRCC_voidSetClkSource(HSE);
	// Turn off HSE and PLL
	MRCC_voidClkDisable(HSI);
	MRCC_voidClkDisable(PLL);

#elif CLK_SOURCE == PLL
#if PLL_SOURCE == HSE
	MRCC_voidSetPLLSource(PLL_SOURCE, PLL_HSE_FACTOR);
	// Turn on HSE
	MRCC_voidClkEnable(HSE);
	// Check HSE Ready
	while (MRCC_u8CheckClockReady(HSE) == NOT_READY)
		;
	// Turn on HSI
	MRCC_voidClkEnable(HSI);
	// Check HSI Ready
	while (MRCC_u8CheckClockReady(HSI) == NOT_READY)
		;
	// Switch to HSI Clock
	MRCC_voidSetClkSource(HSI);
#elif PLL_SOURCE == HSI
	MCRR_voidSetPLLSource(PLL_SOURCE,HSE_NOT_DIVIDED);
	// Turn on HSE
	MRCC_voidClkEnable(HSE);
	// Check HSE Ready
	while (MRCC_u8CheckClockReady(HSE) == NOT_READY)
		;
	// Turn on HSI
	MRCC_voidClkEnable(HSI);
	// Check HSI Ready
	while (MRCC_u8CheckClockReady(HSI) == NOT_READY)
		;
	// Switch to HSE Clock
	MRCC_voidSetClkSource(HSE);
#else
#error wrong PLL Configuration
#endif
	// Set Pll Multiplication Factor
	MRCC_voidSetPLLMulFactor(PLL_MULTIPLICATION_FACTOR);

	// Set Buses Prescaler
	MRCC_voidSetBusesPrescaler(AHB_PRESCALER, ABP1_PRESCALER, ABP2_PRESCALER);

	// Turn on PLL
	MRCC_voidClkEnable(PLL);
	// Check PLL Ready
	while (MRCC_u8CheckClockReady(PLL) == NOT_READY)
		;
	// Switch to HSI Clock
	MRCC_voidSetClkSource(PLL);
	// Turn off HSE OR HSI
#if PLL_SOURCE == HSE
	MRCC_voidClkDisable(HSI);
#elif PLL_SOURCE == HSI
	MRCC_voidClkDisable(HSE);
#endif
#else
#error CLOCK Source is not configured properly

#endif
}

void MRCC_voidClkEnable(u8 A_u8ClkSource)
{
	switch(A_u8ClkSource)
	{
	case HSI:
		SET_BIT(RCC->CR,HSI_ON_BIT); break;
	case HSE:
		SET_BIT(RCC->CR,HSE_ON_BIT); break;
	case PLL:
		SET_BIT(RCC->CR,PLL_ON_BIT); break;
	}
}
void MRCC_voidClkDisable(u8 A_u8ClkSource)
{
	switch(A_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CR,HSI_ON_BIT); break;
	case HSE:
		CLR_BIT(RCC->CR,HSE_ON_BIT); break;
	case PLL:
		CLR_BIT(RCC->CR,PLL_ON_BIT); break;
	}
}
u8 MRCC_u8CheckClockReady(u8 A_u8ClkSource)
{
	u8 local_u8ReadyFlag=0;
	switch(A_u8ClkSource)
	{
	case HSI:
		local_u8ReadyFlag=GET_BIT(RCC->CR,HSI_RDY_BIT); break;
	case HSE:
		local_u8ReadyFlag=GET_BIT(RCC->CR,HSE_RDY_BIT); break;
	case PLL:
		local_u8ReadyFlag=GET_BIT(RCC->CR,PLL_RDY_BIT); break;
	}
	return local_u8ReadyFlag;

}
void MRCC_voidSetPLLMulFactor(u8 A_u8MulFactor)
{
	RCC->CFGR &= ~(MULTIPLICATION_FACTOR_RESET_MASK);
	RCC->CFGR |= (A_u8MulFactor << PLL_MUL_FBIT);
}

/* A_u8ClkSource : HSI  -  HSE */
/* A_u8Prescaler : HSE_NOT_DIVIDED  -  HSE_DIVIDED*/
void MRCC_voidSetPLLSource(u8 A_u8ClkSource, u8 A_u8Prescaler)
{
	switch (A_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, PLLSRC_BIT);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, PLLSRC_BIT);
		switch (A_u8Prescaler)
		{
		case HSE_NOT_DIVIDED:
			CLR_BIT(RCC->CFGR, PLLXTPRE_BIT);
			break;
		case HSE_DIVIDED:
			SET_BIT(RCC->CFGR, PLLXTPRE_BIT);
			break;
		default:
			break;
		}
		break;
	}
}
void MRCC_voidSetClkSource(u8 A_u8ClkSource)
{
	switch (A_u8ClkSource)
	{
	case HSI:
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case HSE:
		SET_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	case PLL:
		CLR_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT0);
		SET_BIT(RCC->CFGR, SYSTEM_CLOCK_BIT1);
		break;
	}
}

void MRCC_voidSetBusesPrescaler(u8 A_u8AHBPrescaler, u8 A_u8APB1Prescaler, u8 A_u8APB2Prescaler)
{
	RCC->CFGR &= ~(BUSES_PRESCALER_RESET_MASK << AHB_PRESCALER_FBIT);
	RCC->CFGR |= (A_u8AHBPrescaler << AHB_PRESCALER_FBIT);
	RCC->CFGR |= (A_u8APB1Prescaler << APB1_PRESCALER_FBIT);
	RCC->CFGR |= (A_u8APB2Prescaler << APB2_PRESCALER_FBIT);
}
void MCRR_voidControlPeripheralsClock(u8 A_u8BusID, u8 A_u8PeripheralID, u8 A_u8Control)
{
	if(A_u8BusID==APB1)
	{
		switch(A_u8PeripheralID)
		{
			case TIM2:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,TIM2EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,TIM2EN_BIT);
			break;
			case TIM3:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,TIM3EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,TIM3EN_BIT);
			break;
			case TIM4:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,TIM4EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,TIM4EN_BIT);
			break;
			case TIM5:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,TIM5EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,TIM5EN_BIT);
			break;
			case TIM6:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,TIM6EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,TIM6EN_BIT);
			break;
			case TIM7:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,TIM7EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,TIM7EN_BIT);
			break;
			case WWDG:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,WWDGEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,WWDGEN_BIT);
			break;
			case SPI2:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,SPI2EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,SPI2EN_BIT);
			break;
			case SPI3:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,SPI3EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,SPI3EN_BIT);
			break;
			case USART2:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,USART2EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,USART2EN_BIT);
			break;
			case USART3:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,USART3EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,USART3EN_BIT);
			break;
			case USART4:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,UART4EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,UART4EN_BIT);
			break;
			case USART5:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,UART5EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,UART5EN_BIT);
			break;
			case I2C1:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,I2C1EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,I2C1EN_BIT);
			break;
			case I2C2:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,I2C2EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,I2C2EN_BIT);
			break;
			case CAN1:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,CAN1EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,CAN1EN_BIT);
			break;
			case CAN2:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,CAN2EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,CAN2EN_BIT);
			break;
			case BKP:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,BKPEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,BKPEN_BIT);
			break;
			case PWR:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,PWREN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,PWREN_BIT);
			break;
			case DAC:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB1ENR,DACEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB1ENR,DACEN_BIT);
			break;
		}
	}
	else if(A_u8BusID==APB2)
	{
		switch(A_u8PeripheralID)
		{
			case AFIO:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,AFIOEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,AFIOEN_BIT);
			break;
			case IOPA:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,IOPAEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,IOPAEN_BIT);
			break;
			case IOPB:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,IOPBEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,IOPBEN_BIT);
			break;
			case IOPC:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,IOPCEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,IOPCEN_BIT);
			break;
			case IOPD:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,IOPDEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,IOPDEN_BIT);
			break;
			case IOPE:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,IOPEEN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,IOPEEN_BIT);
			break;
			case ADC1:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,ADC1EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,ADC1EN_BIT);
			break;
			case ADC2:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,ADC2EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,ADC2EN_BIT);
			break;
			case TIM1:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,TIM1EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,TIM1EN_BIT);
			break;
			case SPI1:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,SPI1EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,SPI1EN_BIT);
			break;
			case USART1:
				if(A_u8Control==ENABLE_PERIPHERAL)			SET_BIT(RCC->APB2ENR,USART1EN_BIT);
				else if(A_u8Control==DISABLE_PERIPHERAL)	CLR_BIT(RCC->APB2ENR,USART1EN_BIT);
			break;
		}
	}
}
