#include "iicapp.h"

float x_val = 1.0f, y_val = 1.0f;

void write_eeprom(uint8_t addr)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	I2CSendByte(addr);
	I2CWaitAck();
	switch(addr)
	{
		case 0:
			I2CSendByte(x_store);
		break;
		case 1:
			I2CSendByte(y_store);
		break;
		case 2:
			I2CSendByte((uint8_t)(x_value * 10));
		break;
		case 3:
			I2CSendByte((uint8_t)(y_value * 10));
		break;
		default:break;
	}
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
	x_store = I2CReceiveByte();
	I2CSendAck();
	y_store = I2CReceiveByte();
	I2CSendAck();
	x_val = x_value = I2CReceiveByte() / 10.0f;
	I2CSendAck();
	y_val = y_value = I2CReceiveByte() / 10.0f;
	I2CSendNotAck();
	I2CStop();
}

void write_value_proc(void)
{
	if(fabs(x_val - x_value) > 0.05f)
	{
		x_val = x_value;
		write_eeprom(2);
	}
	if(fabs(y_val - y_value) > 0.05f)
	{
		y_val = y_value;
		write_eeprom(3);
	}
}