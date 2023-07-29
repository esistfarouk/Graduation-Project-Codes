#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_private.h"

void	MDIO_voidSetPinDirection	(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Direction )
{
		/*		Range Check			*/
	if(Copy_u8PortID<3 && Copy_u8PinID<16)
	{
		switch(Copy_u8PortID)
		{
			case	GPIO_U8_PORTA	:	
			/*	Check if Low				*/
			if(Copy_u8PinID <8)
			{
				//	#define		CLR(REG,BIT)		REG &=~(1<<BIT)
				/*	CLR The 4 bits Of Direction					*/
				GPIOA->GPIOA_CRL	&=~((0b1111)			<< (Copy_u8PinID * 4));
				GPIOA->GPIOA_CRL	|=((Copy_u8Direction)	<< (Copy_u8PinID * 4));
			
			}
			else if(Copy_u8PinID <16)
			{
				Copy_u8PinID -= 8;
				/*	CLR The 4 bits Of Direction					*/
				GPIOA->GPIOA_CRH	&=~((0b1111)			<< (Copy_u8PinID * 4));
				GPIOA->GPIOA_CRH	|=((Copy_u8Direction)	<< (Copy_u8PinID * 4));
			}else{	/*	Return Error */	}		break;
			
			case	GPIO_U8_PORTB	:	
			/*	Check if Low				*/
			if(Copy_u8PinID <8)
			{
				//	#define		CLR(REG,BIT)		REG &=~(1<<BIT)
				/*	CLR The 4 bits Of Direction					*/
				GPIOB->GPIOB_CRL	&=~((0b1111)			<< (Copy_u8PinID * 4));
				GPIOB->GPIOB_CRL	|=((Copy_u8Direction)	<< (Copy_u8PinID * 4));
			
			}else if(Copy_u8PinID <16)
			{
				Copy_u8PinID -= 8;
				/*	CLR The 4 bits Of Direction					*/
				GPIOB->GPIOB_CRH	&=~((0b1111)			<< (Copy_u8PinID * 4));
				GPIOB->GPIOB_CRH	|=((Copy_u8Direction)	<< (Copy_u8PinID * 4));
			}else{	/*	Return Error */	}		break;
			
			case	GPIO_U8_PORTC	:	
			/*	Check if Low				*/
			if(Copy_u8PinID <8)
			{
				//	#define		CLR(REG,BIT)		REG &=~(1<<BIT)
				/*	CLR The 4 bits Of Direction					*/
				GPIOC->GPIOC_CRL	&=~((0b1111)			<< (Copy_u8PinID * 4));
				GPIOC->GPIOC_CRL	|=((Copy_u8Direction)	<< (Copy_u8PinID * 4));
			
			}else if(Copy_u8PinID <16)
			{
				Copy_u8PinID -= 8;
				/*	CLR The 4 bits Of Direction					*/
				GPIOC->GPIOC_CRH	&=~((0b1111)			<< (Copy_u8PinID * 4));
				GPIOC->GPIOC_CRH	|=((Copy_u8Direction)	<< (Copy_u8PinID * 4));
			}else{	/*	Return Error */	}		break;
		}
		
	}else{	/*	Return Error		*/	}	
}

//DIO_voidSetPinValue		(GPIO_U8_PORTA ,GPIO_U8_PIN0 ,GPIO_U8_HIGH	);
void	MDIO_voidSetPinValue		(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Value		)
{
	/*		Range Check			*/
	if(Copy_u8PortID<3 && Copy_u8PinID<16)
	{
		if(Copy_u8Value == GPIO_U8_HIGH)
		{
			switch(Copy_u8PortID)
			{
				case	GPIO_U8_PORTA :
					GPIOA->GPIOA_BSRR = (1<<Copy_u8PinID);
					//SET_BIT(GPIOA->GPIOA_ODR,Copy_u8PinID);
				break;
				case 	GPIO_U8_PORTB :
					GPIOB->GPIOB_BSRR = (1<<Copy_u8PinID);
					//GPIO_U8_PORTB :	SET_BIT(GPIOB->GPIOB_ODR,Copy_u8PinID);
				break;
				case	GPIO_U8_PORTC :
					GPIOC->GPIOC_BSRR = (1<<Copy_u8PinID);
					//SET_BIT(GPIOC->GPIOC_ODR,Copy_u8PinID);
				break;
			}
			
		}else if (Copy_u8Value == GPIO_U8_LOW)
		{
			switch(Copy_u8PortID)
			{
			case	GPIO_U8_PORTA :
				GPIOA->GPIOA_BRR = (1<<Copy_u8PinID);
				//CLR_BIT(GPIOA->GPIOA_ODR,Copy_u8PinID);
			break;
			case 	GPIO_U8_PORTB :
				GPIOB->GPIOB_BRR = (1<<Copy_u8PinID);
				//CLR_BIT(GPIOB->GPIOB_ODR,Copy_u8PinID);
			break;
			case	GPIO_U8_PORTC :
				GPIOC->GPIOC_BRR = (1<<Copy_u8PinID);
				//SET_BIT(GPIOC->GPIOC_ODR,Copy_u8PinID);
			break;
			}	
		}else{	/*	Return Error	*/}
		
	}else{	/*	Return Error		*/	}
}
u8		MDIO_u8GetPinValue		(u8 Copy_u8PortID ,u8 Copy_u8PinID )
{
	u8	Local_u8Value	= 0x55 ;
	/*		Range Check			*/
	if(Copy_u8PortID<3 && Copy_u8PinID<16)
	{
		switch(Copy_u8PortID)
		{
			case	GPIO_U8_PORTA :	Local_u8Value = GET_BIT(GPIOA->GPIOA_IDR,Copy_u8PinID);	break;
			case	GPIO_U8_PORTB :	Local_u8Value = GET_BIT(GPIOB->GPIOB_IDR,Copy_u8PinID);	break;
			case	GPIO_U8_PORTC :	Local_u8Value = GET_BIT(GPIOC->GPIOC_IDR,Copy_u8PinID);	break;
		}		
	}else{	/*	Return Error		*/	}	
	return Local_u8Value ;
}

void MDIO_voidDelay(u32 Copy_u32Counter)
{
	for(volatile u32 i = 0; i <= Copy_u32Counter; i++)
	{
		asm("NOP");
	}
}

void	MDIO_voidSetPortDirection	(u8 Copy_u8PortID ,u8 Copy_u8Direction 	)
{
	for(u8 i = GPIO_U8_PIN0; i <= GPIO_U8_PIN15; i++)
	{
		MDIO_voidSetPinDirection(Copy_u8PortID, i, Copy_u8Direction);
	}


}
void	MDIO_voidSetPortValue		(u8 Copy_u8PortID ,u8 Copy_u8Value		)
{
	switch(Copy_u8PortID)
	{
	case GPIO_U8_PORTA:
		GPIOA->GPIOA_ODR=Copy_u8Value;
	break;
	case GPIO_U8_PORTB:
		GPIOB->GPIOB_ODR=Copy_u8Value;
	break;
	case GPIO_U8_PORTC:
		GPIOC->GPIOC_ODR=Copy_u8Value;
	break;
	}
}
u16		MDIO_u16GetPortValue		(u8 Copy_u8PortID  							)
{

}
