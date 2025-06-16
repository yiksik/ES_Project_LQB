#include "iicapp.h"

void write_eeprom(void)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte((store_pos-1)*8);
	I2CWaitAck();
	I2CSendByte(times[0].hours);
	I2CWaitAck();
	I2CSendByte(times[0].mins);
	I2CWaitAck();
	I2CSendByte(times[0].secs);
	I2CWaitAck();
	I2CStop();
}

void read_eeprom(void)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte((store_pos-1)*8);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0xa1);
	I2CWaitAck();
	times[store_pos].hours = I2CReceiveByte();
	I2CSendAck();
	times[store_pos].mins = I2CReceiveByte();
	I2CSendAck();
	times[store_pos].secs = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
}