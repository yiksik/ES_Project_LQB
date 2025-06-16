#include "iicapp.h"

void write_eeprom(void)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(0);
	I2CWaitAck();
	I2CSendByte((uint8_t)(th_temper + 20));
	I2CWaitAck();
	I2CSendByte(th_wet);
	I2CWaitAck();
	I2CSendByte(record_gap);
	I2CWaitAck();
	I2CSendByte((uint8_t)(freq_out/100));
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
	th_temper = I2CReceiveByte() - 20;
	I2CSendAck();
	th_wet = I2CReceiveByte();
	I2CSendAck();
	record_gap = I2CReceiveByte();
	I2CSendAck();
	freq_out = I2CReceiveByte() * 100;
	I2CSendNotAck();
	I2CStop();
}