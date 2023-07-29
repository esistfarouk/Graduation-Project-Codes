#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/RCC/RCC_int.h"
#include "../Inc/MCAL/GPIO/GPIO_interface.h"
#include "../Inc/MCAL/UART/UART_interface.h"

#include "../Inc/HAL/LED/Led_interface.h"

int main(void)
{
	UART_Config_t UART_2;
	UART_2.UART_NUM=UART3;
	UART_2.UART_ENABLE_STATE=UART_ENABLE;
	UART_2.UART_WORD_LENGTH=UART_EIGHT_BITS;
	UART_2.UART_WAKEUP=UART_IDLE_LINE;
	UART_2.UART_PARITY_CONTROL_ENABLE=UART_PARITY_DISABLED;
	UART_2.UART_PARITY_SELECTION=UART_EVEN_PARITY;
	UART_2.UART_PEIE=UART_INTERRUPT_IS_INHIBITED_PE;
	UART_2.UART_TXEIE=UART_INTERRUPT_IS_INHIBITED_TXE;
	UART_2.UART_TCIE=UART_INTERRUPT_IS_INHIBITED_TC;
	UART_2.UART_RXNEIE=UART_INTERRUPT_IS_INHIBITED_RXNE;
	UART_2.UART_IDLEIE=UART_INTERRUPT_IS_INHIBITED_IDLE;
	UART_2.UART_TE=UART_TRANSMITTER_ENABLE;
	UART_2.UART_RE=UART_RECEIVER_ENABLE;
	UART_2.UART_RWU=UART_RECEIVER_ACTIVE_MODE;
	UART_2.UART_SBK=UART_NO_BREAK_CHARACTER;
	UART_2.UART_BaudRate=9600;
	MRCC_voidInit();
	MCRR_voidControlPeripheralsClock(APB2 ,IOPB ,ENABLE_PERIPHERAL);
	MDIO_voidSetPinDirection(GPIO_U8_PORTB, GPIO_U8_PIN10, GPIO_U8_OUTPUT_AF_PP_2MHZ);
	MDIO_voidSetPinDirection(GPIO_U8_PORTB, GPIO_U8_PIN11, GPIO_U8_INPUT_FLOATING);
	MCRR_voidControlPeripheralsClock(APB1, USART3, ENABLE_PERIPHERAL);
	MUART_voidInit(&UART_2);
	while(1)
    {
		MUART_voidTransmitCharSync(&UART_2, 'N');
		/*data=MUART_u8RecieveCharSync(&UART_1);
		if(data=='A')
		{
			LED1_STATUS=HLed_voidGetState(LED_1);
			HLed_voidTogglee(LED_1);
			if(HLed_voidGetState(LED_1)!=LED1_STATUS)
			{
				MUART_voidTransmitSync(&UART_1, "OK ");
			}
			else
			{
				MUART_voidTransmitSync(&UART_1, "NOK ");
			}
		}
		if(data=='B')
		{
			LED2_STATUS=HLed_voidGetState(LED_2);
			HLed_voidTogglee(LED_2);
			if(HLed_voidGetState(LED_2)!=LED2_STATUS)
			{
				MUART_voidTransmitSync(&UART_1, "OK ");
			}
			else
			{
				MUART_voidTransmitSync(&UART_1, "NOK ");
			}
		}
		if(data=='C')
		{
			LED3_STATUS=HLed_voidGetState(LED_3);
			HLed_voidTogglee(LED_3);
			if(HLed_voidGetState(LED_3)!=LED3_STATUS)
			{
				MUART_voidTransmitSync(&UART_1, "OK ");
			}
			else
			{
				MUART_voidTransmitSync(&UART_1, "NOK ");
			}
		}*/
    }
}
