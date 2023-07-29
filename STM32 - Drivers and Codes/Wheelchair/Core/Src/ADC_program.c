/*
 * ADC_program.c
 *
 *  Created on: Sep 14, 2022
 *      Author: FAROUK
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/ADC/ADC_private.h"
#include "../Inc/MCAL/ADC/ADC_interface.h"
#include "../Inc/MCAL/STK/STK_interface.h"


void MADC1_voidInit()
{
	MSTK_voidInit();
	ADC_1->ADC_CR[0]=0;
	ADC_1->ADC_CR[1]=0;
	ADC_1->ADC_CR[1]|=1; //ADCON
	ADC_1->ADC_SMPR[1]=0;
	ADC_1->ADC_SMPR[1]|=1; //channel 0 (7.5 cycles)
	ADC_1->ADC_SMPR[1]|=(1<<3); //channel 1 (7.5 cycles)
	MSTK_voidSetBusyWait(1000);
}
u16 MADC1_u16StartConversion_Channel_0()
{
	u16 Local_u16ADCValue = 65535;
	ADC_1->ADC_SQR[2] = 0;
	ADC_1->ADC_SQR[2] |= 0;
	ADC_1->ADC_SR=0;
	//enable adc
	SET_BIT((ADC_1->ADC_CR[1]),0);
	while(GET_BIT(ADC_1->ADC_SR,1)==0)
	Local_u16ADCValue = (u16)ADC_1->ADC_DR;
	return Local_u16ADCValue;
}
u16 MADC1_u16StartConversion_Channel_1()
{
	u16 Local_u16ADCValue = 65535;
	ADC_1->ADC_SQR[2] = 0;
	ADC_1->ADC_SQR[2] |= 1;
	ADC_1->ADC_SR=0;
	//enable adc
	SET_BIT((ADC_1->ADC_CR[1]),0);
	while(GET_BIT(ADC_1->ADC_SR,1)==0)
	Local_u16ADCValue = (u16)ADC_1->ADC_DR;
	return Local_u16ADCValue;
}
