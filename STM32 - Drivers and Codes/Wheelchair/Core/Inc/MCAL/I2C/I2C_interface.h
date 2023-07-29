#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

typedef enum
{
	Write,
	Read
}DataDir;

void MI2C_MasterInit(void);

void Master_RecieveDataByte(u8 address, u8* Data);
void MasterSendStartCondition(void);
void MI2C_MasterTransmitAddress(u8 address, DataDir Direction);
u8 MI2C_MasterRecieve_OneByte(u8* Data, u8 ACK);
void MasterSendStopCondition(void);
void MI2C_MasterTransmitData(u8 Data);
void MI2C_MasterTransmitAddressWrite(void);
void MI2C_MasterTransmitAddressRead(void);
void MI2C_MasterRecieve_ThreeBytes(u8* Data);
void MI2C_wait(void);
#endif
