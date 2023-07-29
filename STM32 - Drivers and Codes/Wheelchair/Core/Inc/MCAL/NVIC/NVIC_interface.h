/*
 * NVIC_interface.h
 *
 *  Created on: Aug 17, 2022
 *      Author: FAROUK
 */

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_

#if MNVIC_GRP_SUB == MNVIC_0_GROUP_16_SUB
#define	GROUP_0_SUB_0	0b0000
#define	GROUP_0_SUB_1	0b0001
#define	GROUP_0_SUB_2	0b0010
#define	GROUP_0_SUB_3	0b0011
#define	GROUP_0_SUB_4	0b0100
#define	GROUP_0_SUB_5	0b0101
#define	GROUP_0_SUB_6	0b0110
#define	GROUP_0_SUB_7	0b0111
#define	GROUP_0_SUB_8	0b1000
#define	GROUP_0_SUB_9	0b1001
#define	GROUP_0_SUB_10	0b1010
#define	GROUP_0_SUB_11	0b1011
#define	GROUP_0_SUB_12	0b1100
#define	GROUP_0_SUB_13	0b1101
#define	GROUP_0_SUB_14	0b1110
#define	GROUP_0_SUB_15	0b1111

#elif MNVIC_GRP_SUB == MNVIC_2_GROUP_8_SUB
#define	GROUP_0_SUB_0	0b0000
#define	GROUP_0_SUB_1	0b0001
#define	GROUP_0_SUB_2	0b0010
#define	GROUP_0_SUB_3	0b0011
#define	GROUP_0_SUB_4	0b0100
#define	GROUP_0_SUB_5	0b0101
#define	GROUP_0_SUB_6	0b0110
#define	GROUP_0_SUB_7	0b0111

#define	GROUP_1_SUB_0	0b1000
#define	GROUP_1_SUB_1	0b1001
#define	GROUP_1_SUB_2	0b1010
#define	GROUP_1_SUB_3	0b1011
#define	GROUP_1_SUB_4	0b1100
#define	GROUP_1_SUB_5	0b1101
#define	GROUP_1_SUB_6	0b1110
#define	GROUP_1_SUB_7	0b1111

#elif MNVIC_GRP_SUB == MNVIC_4_GROUP_4_SUB
#define	GROUP_0_SUB_0	0b0000
#define	GROUP_0_SUB_1	0b0001
#define	GROUP_0_SUB_2	0b0010
#define	GROUP_0_SUB_3	0b0011

#define GROUP_1_SUB_0	0b0100
#define GROUP_1_SUB_1	0b1101
#define GROUP_1_SUB_2	0b1110
#define GROUP_1_SUB_3	0b1111

#define	GROUP_2_SUB_0	0b1000
#define	GROUP_2_SUB_1	0b1001
#define	GROUP_2_SUB_2	0b1010
#define	GROUP_2_SUB_3	0b1011

#define	GROUP_3_SUB_0	0b1100
#define	GROUP_3_SUB_1   0b1101
#define	GROUP_3_SUB_2   0b1110
#define	GROUP_3_SUB_3   0b1111

#elif MNVIC_GRP_SUB == MNVIC_8_GROUP_2_SUB
#define	GROUP_0_SUB_0	0b0000
#define	GROUP_0_SUB_1	0b0001

#define	GROUP_1_SUB_0	0b0010
#define	GROUP_1_SUB_1	0b0011

#define	GROUP_2_SUB_0	0b0100
#define	GROUP_2_SUB_1	0b0101

#define	GROUP_3_SUB_0	0b0110
#define	GROUP_3_SUB_1	0b0111

#define	GROUP_4_SUB_0	0b1000
#define	GROUP_4_SUB_1   0b1001

#define	GROUP_5_SUB_0	0b1010
#define	GROUP_5_SUB_1   0b1011

#define	GROUP_6_SUB_0	0b1100
#define	GROUP_6_SUB_1   0b1101

#define	GROUP_7_SUB_0	0b1110
#define	GROUP_7_SUB_1   0b1111


#elif MNVIC_GRP_SUB == MNVIC_16_GROUP_0_SUB
#define GROUP_0_SUB_0	0b0000
#define GROUP_1_SUB_0   0b0001
#define GROUP_2_SUB_0   0b0010
#define GROUP_3_SUB_0   0b0011
#define GROUP_4_SUB_0   0b0100
#define GROUP_5_SUB_0   0b0101
#define GROUP_6_SUB_0   0b0110
#define GROUP_7_SUB_0   0b0111
#define	GROUP_8_SUB_0   0b1000
#define	GROUP_9_SUB_0   0b1001
#define	GROUP_10_SUB_0  0b1010
#define	GROUP_11_SUB_0  0b1011
#define	GROUP_12_SUB_0  0b1100
#define	GROUP_13_SUB_0  0b1101
#define	GROUP_14_SUB_0  0b1110
#define	GROUP_15_SUB_0  0b1111
#endif

void	MNVIC_voidInit				(void);
void	MNVIC_voidEnableInterrupt	(u8 Copy_u8IntNum);
void	MNVIC_voidDisableInterrupt	(u8 Copy_u8IntNum);
void	MNVIC_voidSetPendingFlag	(u8 Copy_u8IntNum);
void	MNVIC_voidClearPendingFlag	(u8 Copy_u8IntNum);
u8		MNVIC_u8GetActiveFlag		(u8 Copy_u8IntNum);
/*options: 	GROUP_0_SUB_0
 * 	 		GROUP_0_SUB_1
 * 	 		GROUP_0_SUB_2
 * 	 		GROUP_0_SUB_3
 * 	 		GROUP_0_SUB_4
 * 	 		GROUP_0_SUB_5
 * 	 		GROUP_0_SUB_6
 * 	 		GROUP_0_SUB_7
 * 	 		GROUP_0_SUB_8
 * 	 		GROUP_0_SUB_9
 * 	 		GROUP_0_SUB_10
 * 	 		GROUP_0_SUB_11
 * 	 		GROUP_0_SUB_12
 * 	 		GROUP_0_SUB_13
 * 	 		GROUP_0_SUB_14
 * 	 		GROUP_0_SUB_15
 * 	 		GROUP_1_SUB_0
 * 	 		GROUP_1_SUB_1
 * 	 		GROUP_1_SUB_2
 * 	 		GROUP_1_SUB_3
 * 	 		GROUP_1_SUB_4
 * 	 		GROUP_1_SUB_5
 * 	 		GROUP_1_SUB_6
 * 	 		GROUP_1_SUB_7
 * 	 		GROUP_2_SUB_0
 * 	 		GROUP_2_SUB_1
 * 	 		GROUP_2_SUB_2
 * 	 		GROUP_2_SUB_3
 * 	 		GROUP_3_SUB_0
 * 	 		GROUP_3_SUB_1
 * 	 		GROUP_3_SUB_2
 * 	 		GROUP_3_SUB_3
 * 	 		GROUP_4_SUB_0
 * 	 		GROUP_4_SUB_1
 * 	 		GROUP_5_SUB_0
 * 	 		GROUP_5_SUB_1
 * 	 		GROUP_6_SUB_0
 * 	 		GROUP_6_SUB_1
 * 	 		GROUP_7_SUB_0
 * 	 		GROUP_7_SUB_1
 * 	 		GROUP_8_SUB_0
 * 	 		GROUP_9_SUB_0
 * 	 		GROUP_10_SUB_0
 * 	 		GROUP_11_SUB_0
 * 	 		GROUP_12_SUB_0
 * 	 		GROUP_13_SUB_0
 * 	 		GROUP_14_SUB_0
 * 	 		GROUP_15_SUB_0*/
void	MNVIC_voidSetPriority		(u8 Copy_u8IntNum,u8 Copy_u8Priority);


#endif /* MCAL_NVIC_NVIC_INTERFACE_H_ */
