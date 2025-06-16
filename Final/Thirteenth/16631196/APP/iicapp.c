#include "iicapp.h"

uint8_t x_value_eeprom, y_value_eeprom;

void write_eeprom(void)
{
	// y存在地址0，x存在地址1
	uint8_t temp = 0;
	if(y_value != y_value_eeprom)
	{
		temp |= 0x01;		// temp最低位为1表示y发生变化需要写入
		y_value_eeprom = y_value;
	}
	if(x_value != x_value_eeprom)
	{
		temp |= 0x02;		// temp倒数第二位为1表示x发生变化需要写入
		x_value_eeprom = x_value;
	}
	if(!temp) // 没有需要写入的，直接退出函数
		return;
	
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();
	
	if(temp & 0x01)
	{
		// 如果最低位为1，从地址0开始存，否则从地址1开始存
		I2CSendByte(0);
	}
	else
		I2CSendByte(1);
	I2CWaitAck();
	
	if(temp & 0x01)
	{
		// 如果y需要写入
		I2CSendByte(y_value);
		I2CWaitAck();
	}
	if(temp & 0x02)
	{
		// 如果x需要写入
		I2CSendByte(x_value);
		I2CWaitAck();
	}
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
	y_value_eeprom = y_value = I2CReceiveByte();
	I2CSendAck();
	x_value_eeprom = x_value = I2CReceiveByte();
	I2CSendNotAck();
	I2CStop();
}
