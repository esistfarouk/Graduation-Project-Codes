/*
 * PWM_private.h
 *
 *  Created on: Feb 13, 2023
 *      Author: FAROUK
 */

#ifndef INC_MCAL_PWM_PWM_PRIVATE_H_
#define INC_MCAL_PWM_PWM_PRIVATE_H_



#define TIM3_BASE_ADDRESS 0x40000400

#define TIM_3 ((volatile TIM3_Reg *)TIM3_BASE_ADDRESS)

typedef struct
{
	volatile u32 TIMx_CR1;
	volatile u32 TIMx_CR2;
	volatile u32 TIMx_SMCR;
	volatile u32 TIMx_DIER;
	volatile u32 TIMx_SR;
	volatile u32 TIMx_EGR;
	volatile u32 TIMx_CCMR1;
	volatile u32 TIMx_CCMR2;
	volatile u32 TIMx_CCER;
	volatile u32 TIMx_CNT;
	volatile u32 TIMx_PSC;
	volatile u32 TIMx_ARR;
	volatile u32 Reserved;
	volatile u32 TIMx_CCR1;
	volatile u32 TIMx_CCR2;
	volatile u32 TIMx_CCR3;
	volatile u32 TIMx_CCR4;
	volatile u32 Reserved1;
	volatile u32 TIMx_DCR;
	volatile u32 TIMx_DMAR;
}TIM3_Reg;




#endif /* INC_MCAL_PWM_PWM_PRIVATE_H_ */
