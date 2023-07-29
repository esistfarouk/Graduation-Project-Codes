/*
 * UART_program.c
 *
 *  Created on: Aug 30, 2022
 *      Author: FAROUK
 */

#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/LIB/STD_TYPES.h"


#include "../Inc/MCAL/UART/UART_private.h"
#include "../Inc/MCAL/UART/UART_interface.h"

#define FCLK 8000000

static void (* UART1_CallBack)(void)=NULL;
static void (* UART2_CallBack)(void)=NULL;
static void (* UART3_CallBack)(void)=NULL;


void MUART_voidInit(UART_Config_t *copy_UARTNum)
{
	f32 USARTDIVFactor=(FCLK/(16.0*(copy_UARTNum->UART_BaudRate)));
	u8 Mantissa = (u8) USARTDIVFactor;
	u8 DIV_Fraction = 0;
	USARTDIVFactor-=Mantissa;
	USARTDIVFactor*=16;
	if(USARTDIVFactor>15)
	{
		DIV_Fraction=0;
		Mantissa++;
	}
	else
	{
		DIV_Fraction = (u8) USARTDIVFactor;
	}
	/*Baudrate*/
	UART[copy_UARTNum->UART_NUM]->BRR=0;
	UART[copy_UARTNum->UART_NUM]->BRR|=DIV_Fraction;
	UART[copy_UARTNum->UART_NUM]->BRR|=(Mantissa<<4);
	/*Configuration*/
	UART[copy_UARTNum->UART_NUM]->CR[0]=0;
	UART[copy_UARTNum->UART_NUM]->CR[0]|=(copy_UARTNum->UART_SBK);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_RWU)<<1);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_RE)<<2);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_TE)<<3);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_IDLEIE)<<4);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_RXNEIE)<<5);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_TCIE)<<6);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_TXEIE)<<7);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_PEIE)<<8);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_PARITY_SELECTION)<<9);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_PARITY_CONTROL_ENABLE)<<10);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_WAKEUP)<<11);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_WORD_LENGTH)<<12);
	UART[copy_UARTNum->UART_NUM]->CR[0]|=((copy_UARTNum->UART_ENABLE_STATE)<<13);
	/*Clear status reg*/
	UART[copy_UARTNum->UART_NUM]->SR=0;
}

void MUART_voidTransmitCharSync(UART_Config_t *copy_UARTNum, u8 data)
{
	UART[copy_UARTNum->UART_NUM]->DR=data;
	while(GET_BIT(UART[copy_UARTNum->UART_NUM]->SR,6)==0);
}

void MUART_voidTransmitSync(UART_Config_t *copy_UARTNum, u8 arr[])
{
	u8 i = 0;
	while(arr[i]!='\0')
	{
		UART[copy_UARTNum->UART_NUM]->DR=arr[i];
		while(GET_BIT(UART[copy_UARTNum->UART_NUM]->SR,6)==0);
		i++;
	}
}

u8 MUART_u8RecieveCharSync(UART_Config_t *copy_UARTNum)
{
	u8 Local_u8Data = 0;
	while(GET_BIT(UART[copy_UARTNum->UART_NUM]->SR,5)==0);
	Local_u8Data = UART[copy_UARTNum->UART_NUM]->DR;
	return Local_u8Data;
}

void MUART_voidSendInteger(UART_Config_t *copy_UARTNum, u16 copy_u16IntegerData)
{
	if(copy_u16IntegerData==0)
	{
		MUART_voidTransmitCharSync(copy_UARTNum, 0x30);
		return;
	}
	u16 Local_u16Integer = copy_u16IntegerData;
	u8 Local_DigitsCounter = 0;
	u8 Local_Digit[4];
	while(Local_u16Integer!=0)
	{
		Local_DigitsCounter++;
		Local_u16Integer/=10;
	}
	Local_u16Integer = copy_u16IntegerData;
	for(s8 i = Local_DigitsCounter-1; i>=0; i--)
	{
		Local_Digit[i]=Local_u16Integer%10;
		Local_u16Integer/=10;
	}
	for(u8 i = 0; i<Local_DigitsCounter; i++)
	{
		MUART_voidTransmitCharSync(copy_UARTNum, Local_Digit[i]+0x30);
	}
}

u8 MUART_u8ReceiveInteger(UART_Config_t *copy_UARTNum)
{
	u8 Local_u8Integer = 0;
	u8 Local_DigitsCounter = 0;
	u8 Local_Digit[3];
	while(MUART_u8RecieveCharSync(copy_UARTNum)!='*');
	u8 data = 'E';
	while(data!='#')
	{
		data = MUART_u8RecieveCharSync(copy_UARTNum);
		if(data<='9'&&data>='0')
		{
			Local_Digit[Local_DigitsCounter]=(data-0x30);
			Local_DigitsCounter++;
		}
	}
	for(u8 i = 0; i< Local_DigitsCounter; i++)
	{
		u8 Mul = 1;
		for(u8 j =i; j<Local_DigitsCounter-1; j++)
		{
			Mul*=10;
		}
		Local_u8Integer+=Local_Digit[i]*Mul;
	}
	return Local_u8Integer;
}
void MUART1_voidSetCallBack	(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		UART1_CallBack  = 	ptr ;
	}
}
void USART1_IRQHandler(void)
{
	UART1_CallBack();
}
void MUART2_voidSetCallBack	(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		UART2_CallBack  = 	ptr ;
	}
}
void USART2_IRQHandler(void)
{
	UART2_CallBack();
}
void MUART3_voidSetCallBack	(void (*ptr) (void))
{
	if(ptr != NULL)
	{
		UART3_CallBack  = 	ptr ;
	}
}
void USART3_IRQHandler(void)
{
	UART3_CallBack();
}
u8 MUART1_u8ReadDR()
{
	return UART[0]->DR;
}
u8 MUART2_u8ReadDR()
{
	return UART[1]->DR;
}
u8 MUART3_u8ReadDR()
{
	return UART[2]->DR;
}
