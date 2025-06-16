#ifndef __LCDAPP_H
#define __LCDAPP_H

#include "system.h"

void lcd_init(void);
void lcd_disp(u8 Line, u16 startColumn, u16 endColumn);
void lcd_proc(void);

#endif