#ifndef		GPIO_PRIVATE_H
#define		GPIO_PRIVATE_H

#define GPIOA ((volatile GPIOA_t *)0x40010800)

typedef struct
{
	volatile u32 GPIOA_CRL;
	volatile u32 GPIOA_CRH;
	volatile u32 GPIOA_IDR;
	volatile u32 GPIOA_ODR;
	volatile u32 GPIOA_BSRR;
	volatile u32 GPIOA_BRR;
	volatile u32 GPIOA_LCKR;
}GPIOA_t;

#define GPIOB ((volatile GPIOB_t *)0x40010C00)

typedef struct
{
	volatile u32 GPIOB_CRL;
	volatile u32 GPIOB_CRH;
	volatile u32 GPIOB_IDR;
	volatile u32 GPIOB_ODR;
	volatile u32 GPIOB_BSRR;
	volatile u32 GPIOB_BRR;
	volatile u32 GPIOB_LCKR;
}GPIOB_t;

#define GPIOC ((volatile GPIOC_t *)0x40011000)

typedef struct
{
	volatile u32 GPIOC_CRL;
	volatile u32 GPIOC_CRH;
	volatile u32 GPIOC_IDR;
	volatile u32 GPIOC_ODR;
	volatile u32 GPIOC_BSRR;
	volatile u32 GPIOC_BRR;
	volatile u32 GPIOC_LCKR;
}GPIOC_t;



/*
#define		GPIO_PORTA_BASE_ADD		(0x40010800)
#define		GPIOA_CRL				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x00))
#define		GPIOA_CRH				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x04))
#define		GPIOA_IDR				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x08))
#define		GPIOA_ODR				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x10))
#define		GPIOA_BSRR				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x10))
#define		GPIOA_BRR				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x14))
#define		GPIOA_LCKR				*(volatile u32 *(GPIO_PORTA_BASE_ADD + 0x18))


#define		GPIO_PORTB_BASE_ADD		(0x40010C00)
#define		GPIOB_CRL				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x00))
#define		GPIOB_CRH				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x04))
#define		GPIOB_IDR				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x08))
#define		GPIOB_ODR				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x0C))
#define		GPIOB_BSRR				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x10))
#define		GPIOB_BRR				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x14))
#define		GPIOB_LCKR				*(volatile u32 *(GPIO_PORTB_BASE_ADD + 0x18))


#define		GPIO_PORTC_BASE_ADD		(0x40011000)
#define		GPIOC_CRL				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x00))
#define		GPIOC_CRH				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x04))
#define		GPIOC_IDR				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x08))
#define		GPIOC_ODR				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x0C))
#define		GPIOC_BSRR				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x10))
#define		GPIOC_BRR				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x14))
#define		GPIOC_LCKR				*(volatile u32 *(GPIO_PORTC_BASE_ADD + 0x18))
*/



#endif
