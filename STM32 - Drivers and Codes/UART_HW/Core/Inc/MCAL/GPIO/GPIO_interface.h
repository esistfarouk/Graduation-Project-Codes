#ifndef		GPIO_INTERFACE_H
#define		GPIO_INTERFACE_H

/*		Make it works then better it		*/

void	MDIO_voidSetPinDirection	(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Direction );
void	MDIO_voidSetPinValue		(u8 Copy_u8PortID ,u8 Copy_u8PinID ,u8 Copy_u8Value		);
u8		MDIO_u8GetPinValue			(u8 Copy_u8PortID ,u8 Copy_u8PinID 			);

/*		Your Tasks							*/
void	MDIO_voidSetPortDirection	(u8 Copy_u8PortID ,u8 Copy_u8Direction 	);
void	MDIO_voidSetPortValue		(u8 Copy_u8PortID ,u8 Copy_u8Value		);
u16		MDIO_u16GetPortValue		(u8 Copy_u8PortID  							);

void MDIO_voidDelay(u32 Copy_u32Counter);

#define	GPIO_U8_PORTA				0
#define	GPIO_U8_PORTB				1
#define	GPIO_U8_PORTC				2

#define	GPIO_U8_PIN0				0
#define	GPIO_U8_PIN1				1
#define	GPIO_U8_PIN2				2
#define	GPIO_U8_PIN3				3
#define	GPIO_U8_PIN4				4
#define	GPIO_U8_PIN5				5
#define	GPIO_U8_PIN6				6
#define	GPIO_U8_PIN7				7
#define	GPIO_U8_PIN8				8
#define	GPIO_U8_PIN9				9
#define	GPIO_U8_PIN10				10
#define	GPIO_U8_PIN11				11
#define	GPIO_U8_PIN12				12
#define	GPIO_U8_PIN13				13
#define	GPIO_U8_PIN14				14
#define	GPIO_U8_PIN15				15

#define GPIO_U8_HIGH				1
#define GPIO_U8_LOW					0

#define	GPIO_U8_INPUT_ANALOG			0b0000
#define	GPIO_U8_INPUT_FLOATING			0b0100
#define	GPIO_U8_INPUT_PULL_UP_DOWN		0b1000


#define	GPIO_U8_OUTPUT_PP_10MHZ		0b0001
#define	GPIO_U8_OUTPUT_OD_10MHZ		0b0101
#define	GPIO_U8_OUTPUT_AF_PP_10MHZ	0b1001
#define	GPIO_U8_OUTPUT_AF_OD_10MHZ	0b1101

#define	GPIO_U8_OUTPUT_PP_2MHZ		0b0010
#define	GPIO_U8_OUTPUT_OD_2MHZ		0b0110
#define	GPIO_U8_OUTPUT_AF_PP_2MHZ	0b1010
#define	GPIO_U8_OUTPUT_AF_OD_2MHZ	0b1110

#define	GPIO_U8_OUTPUT_PP_50MHZ		0b0011
#define	GPIO_U8_OUTPUT_OD_50MHZ		0b0111
#define	GPIO_U8_OUTPUT_AF_PP_50MHZ	0b1011
#define	GPIO_U8_OUTPUT_AF_OD_50MHZ	0b1111


#endif
