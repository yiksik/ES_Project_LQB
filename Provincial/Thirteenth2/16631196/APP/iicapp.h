#ifndef __IICAPP_H
#define __IICAPP_H

#include "system.h"

void write_eeprom(uint8_t addr);
void read_eeprom(void);
void write_value_proc(void);

#endif
