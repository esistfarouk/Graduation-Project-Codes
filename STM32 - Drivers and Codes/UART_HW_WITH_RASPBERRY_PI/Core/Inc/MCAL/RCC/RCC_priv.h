#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#define RCC ((volatile RCC_t *)0x40021000)

typedef struct
{
	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
}RCC_t;

#define HSI_ON_BIT 0
#define HSE_ON_BIT 16
#define PLL_ON_BIT 24

#define HSI_RDY_BIT 1
#define HSE_RDY_BIT 17
#define PLL_RDY_BIT 25

#define SYSTEM_CLOCK_BIT0 0
#define SYSTEM_CLOCK_BIT1 1

#define AFIOEN_BIT		0
#define IOPAEN_BIT		2
#define IOPBEN_BIT		3
#define	IOPCEN_BIT		4
#define IOPDEN_BIT		5
#define IOPEEN_BIT		6
#define ADC1EN_BIT		9
#define ADC2EN_BIT		10
#define	TIM1EN_BIT		11
#define SPI1EN_BIT		12
#define USART1EN_BIT	14

#define TIM2EN_BIT		0
#define TIM3EN_BIT		1
#define TIM4EN_BIT		2
#define TIM5EN_BIT		3
#define TIM6EN_BIT		4
#define TIM7EN_BIT		5
#define WWDGEN_BIT		11
#define SPI2EN_BIT		14
#define SPI3EN_BIT		15
#define USART2EN_BIT	17
#define USART3EN_BIT	18
#define UART4EN_BIT		19
#define UART5EN_BIT		20
#define I2C1EN_BIT		21
#define I2C2EN_BIT		22
#define CAN1EN_BIT		25
#define CAN2EN_BIT		26
#define BKPEN_BIT		27
#define PWREN_BIT		28
#define DACEN_BIT		29

#define BUSES_PRESCALER_RESET_MASK 1023
#define AHB_PRESCALER_FBIT 4
#define APB1_PRESCALER_FBIT 8
#define APB2_PRESCALER_FBIT 11

#define PLLSRC_BIT 16
#define PLLXTPRE_BIT 17

#define MULTIPLICATION_FACTOR_RESET_MASK 0b1111 << 18
#define PLL_MUL_FBIT 18

#define NOT_READY 	0
#define READY		1

#define HSE_NOT_DIVIDED 1
#define HSE_DIVIDED		2

#endif
