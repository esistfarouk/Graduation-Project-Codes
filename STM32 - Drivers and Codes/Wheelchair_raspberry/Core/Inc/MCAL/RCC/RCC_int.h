#ifndef RCC_INIT_H
#define RCC_INIT_H

#define HSI 	0
#define HSE 	1
#define PLL 	2

#define APB1	0
#define APB2	1

#define AFIO	0
#define IOPA	2
#define IOPB	3
#define	IOPC	4
#define IOPD	5
#define IOPE	6
#define ADC1	9
#define ADC2	10
#define	TIM1	11
#define SPI1	12
#define USART1	14

#define TIM2	0
#define TIM3	1
#define TIM4	2
#define TIM5	3
#define TIM6	4
#define TIM7	5
#define WWDG	11
#define SPI2	14
#define SPI3	15
#define USART2	17
#define USART3	18
#define USART4	19
#define USART5	20
#define I2C1	21
#define I2C2	22
#define CAN1	25
#define CAN2	26
#define BKP		27
#define PWR		28
#define DAC		29

#define DISABLE_PERIPHERAL	0
#define ENABLE_PERIPHERAL 	1


void MRCC_voidInit();
void MRCC_voidClkEnable(u8 A_u8ClkSource);
/******************************************************************************/
/*Function: MRCC_voidClkDisable                          			          */
/*I/P Parameters: CLK Source  		            						      */
/*Returns:it returns void                            				          */
/*Desc:This Function Disables the clock  Source							      */
/******************************************************************************/
/* options :- HSI  -  HSE  -  PLL											  */
/******************************************************************************/
void MRCC_voidClkDisable(u8 A_u8ClkSource);

void MRCC_voidSetClkSource(u8 A_u8ClkSource);

u8 MRCC_u8CheckClockReady(u8 A_u8ClkSource);

void MRCC_voidSetBusesPrescaler(u8 A_u8AHBPrescaler, u8 A_u8APB1Prescaler, u8 A_u8APB2Prescaler);

/* A_u8ClkSource : HSI  -  HSE */
/* A_u8Prescaler : HSE_NOT_DIVIDED  -  HSE_DIVIDED*/
void MRCC_voidSetPLLSource(u8 A_u8ClkSource, u8 A_u8Prescaler);
void MRCC_voidSetPLLMulFactor(u8 A_u8MulFactor);
/*A_u8BusID: APB1	-	APB2*/
/*A_u8PeripheralID:
APB2
 * APB1
 * APB2
 * AFIO
 * IOPA
 * IOPB
 * IOPC
 * IOPD
 * IOPE
 * ADC1
 * ADC2
 * TIM1
 * SPI1
 * USART1
APB1
 * TIM2
 * TIM3
 * TIM4
 * TIM5
 * TIM6
 * TIM7
 * WWDG
 * SPI2
 * SPI3
 * USART2
 * USART3
 * UART4
 * UART5
 * I2C1
 * I2C2
 * CAN1
 * CAN2
 * BKP
 * PWR
 * DAC
*/
/*A_u8Control: ENABLE_PERIPHERAL	-	DISABLE_PERIPHERAL*/
void MRCC_voidControlPeripheralsClock(u8 A_u8BusID, u8 A_u8PeripheralID, u8 A_u8Control);
#endif
