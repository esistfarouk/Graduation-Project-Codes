/*
 * ADC_interface.h
 *
 *  Created on: Sep 14, 2022
 *      Author: FAROUK
 */

#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "ADC_private.h"


void MADC1_voidInit();
u16 MADC1_u16StartConversion_Channel_0();
u16 MADC1_u16StartConversion_Channel_1();


#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
