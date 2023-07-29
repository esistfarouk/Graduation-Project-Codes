/*
 * ADC_private.h
 *
 *  Created on: Sep 14, 2022
 *      Author: FAROUK
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

#define ADC1_BASE_ADDRESS 0x40012400

#define ADC_1 ((volatile ADC_TYPE *)ADC1_BASE_ADDRESS)

typedef struct
{
	volatile u32 ADC_SR;
	volatile u32 ADC_CR[2];
	volatile u32 ADC_SMPR[2];
	volatile u32 ADC_JOFR[4];
	volatile u32 ADC_HTR;
	volatile u32 ADC_LTR;
	volatile u32 ADC_SQR[3];
	volatile u32 ADC_JSQR;
	volatile u32 ADC_JDR[4];
	volatile u32 ADC_DR;
}ADC_TYPE;


#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
