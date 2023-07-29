/*
 * Led_program.c
 *
 *  Created on: Aug 16, 2022
 *      Author: Asmaa Hashim
 */

#include "../Inc/HAL/LED/Led_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"

void HLed_voidInit( tLED  led  ,tLed_State  init_state )
{
	MDIO_voidSetPinDirection(Leds_data[led].port , Leds_data[led].pin , GPIO_U8_OUTPUT_PP_2MHZ);
	HLed_voidSetState( led ,init_state );
}

void HLed_voidSetState( tLED  led  ,tLed_State state )
{
	MDIO_voidSetPinValue(Leds_data[led].port , Leds_data[led].pin ,state );
	Leds_data[led].state = state;

}


tLed_State  HLed_voidGetState( tLED  led   )
{
	tLed_State Local_ret = Leds_data[led].state  ;

    return Local_ret ;
}

void HLed_voidTogglee( tLED  led  )
{
	if( HLed_voidGetState( led ) == LED_ON)
	{
		HLed_voidSetState( led ,LED_OFF );

	}
	else if(HLed_voidGetState( led ) == LED_OFF)
	{
		HLed_voidSetState( led ,LED_ON );
	}

}


