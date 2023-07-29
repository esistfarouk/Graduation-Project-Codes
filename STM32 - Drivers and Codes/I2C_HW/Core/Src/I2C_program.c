#include "../Inc/LIB/STD_TYPES.h"
#include "../Inc/LIB/BIT_MATH.h"

#include "../Inc/MCAL/I2C/I2C_private.h"
#include "../Inc/MCAL/I2C/I2C_interface.h"
#include "../Inc/MCAL/I2C/I2C_config.h"

void MI2C_MasterInit(void)
{
	I2C1->CR1 = 0;
	I2C1->CR2 = 2; //2MHz
	I2C1->CCR = 10; //from equation in data sheet to get 100Khz for BUS
	I2C1->TRISE = 3; //from equation in data sheet
	SET_BIT(I2C1->CR1,1); //enable SMBus Mode
	SET_BIT(I2C1->CR1,4); //enable ARP
	SET_BIT(I2C1->CR1,0); //enable Peripheral
}
void MI2C_wait(void)
{
	while((I2C1->SR2&(1<<1)) != 0); //wait for bus to be free
}
void MasterSendStartCondition(void)
{
	SET_BIT(I2C1->CR1,8); //set start bit
	while(GET_BIT(I2C1->SR1,0)== 0) //wait for start condition to be done
	{
		
	}
	u32 var = I2C1->SR1; //read SR1
	u32 var2 = I2C1->SR2; //read SR2
}
void MI2C_MasterTransmitAddress(u8 address, DataDir Direction)
{
	u8 AddressWithDir = ((address << 1)|Direction); //from 7-bit address to 8-bit address with Read/Write direction
	I2C1->DR = AddressWithDir;
	while(GET_BIT(I2C1->SR1,1)== 0) //wait for ACK
	{
		
	}
	u32 var1 = I2C1->SR1;
	u32 var2 = I2C1->SR2;
}
void MI2C_MasterTransmitData(u8 Data)
{
	I2C1->DR = Data;
	while(GET_BIT(I2C1->SR1,7)== 0) //wait for ACK
	{
		
	}
	u32 var1 = I2C1->SR1;
	u32 var2 = I2C1->SR2;
}
void MI2C_MasterRecieve_ThreeBytes(u8* Data)
{
	//see page 762 in data sheet (when 3 bytes remain to be read)
	SET_BIT(I2C1->CR1,10); //send ACK
	while(GET_BIT(I2C1->SR1,6)== 0); //wait for RXNE flag
	SET_BIT(I2C1->CR1,10); //send ACK
	while(GET_BIT(I2C1->SR1,2)== 0); //wait for BTF flag
	CLR_BIT(I2C1->CR1,10); //sned not ACK
	Data[0]=I2C1->DR; //read Byte 1
	MasterSendStopCondition(); //send stop condition
	Data[1]=I2C1->DR; //read byte 2
	while(GET_BIT(I2C1->SR1,6)== 0); //wait for RXNE flag
	Data[2]=I2C1->DR; //read byte 3
}
u8 MI2C_MasterRecieve_OneByte(u8* Data, u8 ACK)
{
	u32 timeout_counter = 0;
	while(GET_BIT(I2C1->SR1,6)== 0)
	{
		timeout_counter++;
		if(timeout_counter == 50000)
		{
			return 0;
		}
		//CLR_BIT(I2C1->CR1,10);
	}
	u32 temp = I2C1->DR;
	*Data = (u8) (temp%256);
	if(ACK == 1)
	{
		SET_BIT(I2C1->CR1,10);
	}
	else if (ACK == 0)
	{
		CLR_BIT(I2C1->CR1,10);
	}
	//u32 var = I2C1->SR1;
	return 1;
}
void MasterSendStopCondition(void)
{
	SET_BIT(I2C1->CR1,9); //set stop condition bit
}
void Master_RecieveDataByte(u8 address, u8* Data)
{
	MasterSendStartCondition();
	MI2C_MasterTransmitAddress(address, Read);
	MI2C_MasterRecieve_OneByte(Data,0);
	MasterSendStopCondition();
}
void MI2C_MasterTransmitAddressWrite(void)
{
	I2C1->DR = 0xB4;
	while(GET_BIT(I2C1->SR1,1)== 0)
	{

	}
	u32 var1 = I2C1->SR1;
	u32 var2 = I2C1->SR2;
}
void MI2C_MasterTransmitAddressRead(void)
{
	I2C1->DR = 0xB5;
	while(GET_BIT(I2C1->SR1,1)== 0)
	{

	}
	u32 var1 = I2C1->SR1;
	u32 var2 = I2C1->SR2;
}
