#ifndef __LCDAPP_H
#define __LCDAPP_H

#include "system.h"

void lcd_init(void);
void lcd_disp(uint8_t line, char *format, ...);
void lcd_proc(void);
void lcd_res(void);

#endif
