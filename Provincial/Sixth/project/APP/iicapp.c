#include "iicapp.h"

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
	k_value = I2CReceiveByte() / 10.0f;
	I2CSendNotAck();
	I2CStop();
}
void write_eeprom(void)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(0);
	I2CWaitAck();
	I2CSendByte((uint8_t)(k_value * 10));
	I2CWaitAck();
	I2CStop();
}
