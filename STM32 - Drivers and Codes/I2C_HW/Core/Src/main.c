/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"
#include "../Inc/MCAL/I2C/I2C_interface.h"

#include "../Inc/MCAL/RCC/RCC_int.h"
#include "../Inc/MCAL/NVIC/NVIC_interface.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/UART/UART_interface.h"

int main(void)
{
	UART_Config_t Debug;
	Debug.UART_NUM=UART1;
	Debug.UART_ENABLE_STATE=UART_ENABLE;
	Debug.UART_WORD_LENGTH=UART_EIGHT_BITS;
	Debug.UART_WAKEUP=UART_IDLE_LINE;
	Debug.UART_PARITY_CONTROL_ENABLE=UART_PARITY_DISABLED;
	Debug.UART_PARITY_SELECTION=UART_EVEN_PARITY;
	Debug.UART_PEIE=UART_INTERRUPT_IS_INHIBITED_PE;
	Debug.UART_TXEIE=UART_INTERRUPT_IS_INHIBITED_TXE;
	Debug.UART_TCIE=UART_INTERRUPT_IS_INHIBITED_TC;
	Debug.UART_RXNEIE=UART_INTERRUPT_IS_INHIBITED_RXNE;
	Debug.UART_IDLEIE=UART_INTERRUPT_IS_INHIBITED_IDLE;
	Debug.UART_TE=UART_TRANSMITTER_ENABLE;
	Debug.UART_RE=UART_RECEIVER_ENABLE;
	Debug.UART_RWU=UART_RECEIVER_ACTIVE_MODE;
	Debug.UART_SBK=UART_NO_BREAK_CHARACTER;
	Debug.UART_BaudRate=9600;
	/*Initializing RCC and Clocks for Peripherals*/
    MRCC_voidInit();
    MRCC_voidControlPeripheralsClock(APB2, IOPA, ENABLE_PERIPHERAL);
    MRCC_voidControlPeripheralsClock(APB2, IOPB, ENABLE_PERIPHERAL);
    MRCC_voidControlPeripheralsClock(APB1, I2C1, ENABLE_PERIPHERAL);

    MDIO_voidSetPinDirection(GPIO_U8_PORTB, GPIO_U8_PIN6, GPIO_U8_OUTPUT_AF_OD_2MHZ);
    MDIO_voidSetPinDirection(GPIO_U8_PORTB, GPIO_U8_PIN7, GPIO_U8_OUTPUT_AF_OD_2MHZ);
    //MDIO_voidSetPinDirection(GPIO_U8_PORTB, GPIO_U8_PIN8, GPIO_U8_OUTPUT_AF_OD_2MHZ);
    //MDIO_voidSetPinDirection(GPIO_U8_PORTB, GPIO_U8_PIN9, GPIO_U8_OUTPUT_AF_OD_2MHZ);

    MDIO_voidSetPinDirection(GPIO_U8_PORTA, GPIO_U8_PIN9, GPIO_U8_OUTPUT_AF_PP_2MHZ);
    MDIO_voidSetPinDirection(GPIO_U8_PORTA, GPIO_U8_PIN10, GPIO_U8_INPUT_FLOATING);
	MRCC_voidControlPeripheralsClock(APB2, USART1, ENABLE_PERIPHERAL);
	MUART_voidInit(&Debug);

    MI2C_MasterInit();
    /*
    MDIO_voidSetPinValue(GPIO_U8_PORTB, GPIO_U8_PIN6, GPIO_U8_LOW);
    MDIO_voidDelay(50000);
    MDIO_voidSetPinValue(GPIO_U8_PORTB, GPIO_U8_PIN6, GPIO_U8_HIGH);
     */
    /*u8 my_data_LOW = 20;
    u8 my_data_HIGH = 20;
    u8 PEC = 0;*/
    f32 data = 20;
    u8 temperature = 0;
    u8 I2C_Data[3];
	while(1)
	{
		MUART_voidTransmitCharSync(&Debug, '0');
		MI2C_wait();
		//MUART_voidTransmitCharSync(&Debug, '1');
		MasterSendStartCondition();
		//MUART_voidTransmitCharSync(&Debug, '2');
		MI2C_MasterTransmitAddress(0x5A, Write);
		//MUART_voidTransmitCharSync(&Debug, '3');
		MI2C_MasterTransmitData(0x07);
		//MUART_voidTransmitCharSync(&Debug, 'a');
		MasterSendStartCondition();
		//MUART_voidTransmitCharSync(&Debug, 'b');
		MI2C_MasterTransmitAddress(0x5A, Read);
		//MUART_voidTransmitCharSync(&Debug, 'c');
		MI2C_MasterRecieve_ThreeBytes(I2C_Data);
		/*if(MI2C_MasterRecieve_OneByte(&my_data_LOW,1)==0)
		{
			MDIO_voidDelay(100000);
			MasterSendStopCondition();
			MasterSendStopCondition();
			MasterSendStartCondition();
			MI2C_MasterTransmitAddressWrite();
			MI2C_MasterTransmitData(0x07);
			MasterSendStartCondition();
			MI2C_MasterTransmitAddressRead();
		}
		MUART_voidTransmitCharSync(&UART_2, 'd');
		MI2C_MasterRecieve_OneByte(&my_data_HIGH,1);
		MUART_voidTransmitCharSync(&UART_2, 'e');
		MI2C_MasterRecieve_OneByte(&PEC,0);
		MUART_voidTransmitCharSync(&UART_2, 'f');
		MUART_voidTransmitCharSync(&UART_2, 0x0D);
		//MasterSendStopCondition();*/
		MUART_voidSendInteger(&Debug, I2C_Data[0]);
		MUART_voidTransmitCharSync(&Debug, 0x0D);
		MUART_voidSendInteger(&Debug, I2C_Data[1]);
		MUART_voidTransmitCharSync(&Debug, 0x0D);
		data = (I2C_Data[1]<<8|I2C_Data[0])*0.02;
		temperature=data-273;
		MUART_voidTransmitSync(&Debug, (u8* )"Temperature: ");
		MUART_voidSendInteger(&Debug, temperature);
		MUART_voidTransmitCharSync(&Debug, 0x0D);
	}
}
