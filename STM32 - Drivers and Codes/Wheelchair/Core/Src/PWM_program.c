/*
 * PWM_program.c
 *
 *  Created on: Feb 13, 2023
 *      Author: FAROUK
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"

#include "../Inc/MCAL/PWM/PWM_private.h"
#include "../Inc/MCAL/PWM/PWM_interface.h"


void MPWM_voidInit()
{
	TIM_3->TIMx_CCER=0;
	SET_BIT(TIM_3->TIMx_CCER,0); //enable output of channel 0
	SET_BIT(TIM_3->TIMx_CCER,4); //enable output of channel 1
	TIM_3->TIMx_CCMR1=0x6868; //channel 0 and channel 1 pwm mode 1 and enable output compare preload
	TIM_3->TIMx_CR1=0x0080; //upcounting auto reload
	TIM_3->TIMx_PSC=8-1; //prescaler
	TIM_3->TIMx_ARR=2000-1; //max value of counter (reload)
	TIM_3->TIMx_CCR1=1000-1; //compare value for pwm
	TIM_3->TIMx_CCR2=1000-1; //compare value for pwm
	TIM_3->TIMx_EGR=1; //generate update
	SET_BIT(TIM_3->TIMx_CR1,0); //enable timer
}
void MPWM_voidChannel_1_SetValue(u16 Copy_u16PWM_Value)
{
	TIM_3->TIMx_CCR1=Copy_u16PWM_Value;
}
void MPWM_voidChannel_2_SetValue(u16 Copy_u16PWM_Value)
{
	TIM_3->TIMx_CCR2=Copy_u16PWM_Value;
}

