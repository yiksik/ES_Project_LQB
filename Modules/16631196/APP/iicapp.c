#include "iicapp.h"

uint8_t mcp_value = 0;
uint8_t mcp_value_read = 0;
uint8_t eeprom_write = 0;
uint8_t eeprom_read = 0;

void write_mcp4017(void)
{
	I2CStart();
	I2CSendByte(0x5e);
	I2CWaitAck();
	I2CSendByte(mcp_value);
	I2CWaitAck();
	I2CStop();
}

void read_mcp4017(void)
{
	I2CStart();
	I2CSendByte(0x5f);
	I2CWaitAck();
	mcp_value_read = I2CReceiveByte();
	I2CSendNotAck();
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
	eeprom_read = I2CReceiveByte();
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
	I2CSendByte(eeprom_write);
	I2CWaitAck();
	I2CStop();
}