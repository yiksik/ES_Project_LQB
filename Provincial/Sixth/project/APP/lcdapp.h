#ifndef __LCDAPP_H
#define __LCDAPP_H

#include "system.h"

void lcd_init(void);
void lcd_disp(uint8_t line, uint8_t start, uint8_t end);
void lcd_proc(void);

#endif
