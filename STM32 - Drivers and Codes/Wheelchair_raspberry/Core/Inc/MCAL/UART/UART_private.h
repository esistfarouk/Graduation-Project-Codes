/*
 * UART_private.h
 *
 *  Created on: Aug 30, 2022
 *      Author: FAROUK
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_

#define UART1_BASE_ADDRESS 0x40013800
#define UART2_BASE_ADDRESS 0x40004400
#define UART3_BASE_ADDRESS 0x40004800
#define UART4_BASE_ADDRESS 0x40004C00
#define UART5_BASE_ADDRESS 0x40005000


typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR[3];
	volatile u32 GTPR;
}UART_t;

UART_t *UART[5]=
{
		(UART_t*)UART1_BASE_ADDRESS,
		(UART_t*)UART2_BASE_ADDRESS,
		(UART_t*)UART3_BASE_ADDRESS,
		(UART_t*)UART4_BASE_ADDRESS,
		(UART_t*)UART5_BASE_ADDRESS
};

#endif /* MCAL_UART_UART_PRIVATE_H_ */
