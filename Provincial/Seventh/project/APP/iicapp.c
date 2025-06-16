#include "iicapp.h"

void write_eeprom(void)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(0);
	I2CWaitAck();
	I2CSendByte(th_arr[0]);
	I2CWaitAck();
	I2CSendByte(th_arr[1]);
	I2CWaitAck();
	I2CSendByte(th_arr[2]);
	I2CWaitAck();
	I2CStop();
}

void read_eeprom(void)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(0);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0xa1);
	I2CWaitAck();
	th_arr[0] = I2CReceiveByte();
	I2CSendAck();
	th_arr[1] = I2CReceiveByte();
	I2CSendAck();
	th_arr[2] = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
}