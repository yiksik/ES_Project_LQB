#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t b1_down = 0, b2_down = 0, b3_down = 0;
uint8_t b1_num = 0, b2_num = 0, b3_num = 0;
uint8_t ans[3] = {1,2,3};

void lcd_init(void)
{
	LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
}

void lcd_disp(uint8_t line, char *format, ...)
{
	char str[30];
	va_list arg;
	va_start(arg, format);
	vsprintf(str, format, arg);
	va_end(arg);
	LCD_DisplayStringLine(line, (u8*)str);
}

void lcd_proc(void)
{
	if(!lcd_view)
	{
		lcd_disp(Line1, "       PSD");
		if(b1_down)
			lcd_disp(Line3, "    B1:%d     ", b1_num);
		else
			lcd_disp(Line3, "    B1:@      ");
		if(b2_down)
			lcd_disp(Line4, "    B2:%d  ", b2_num);
		else
			lcd_disp(Line4, "    B2:@  ");
		if(b3_down)
			lcd_disp(Line5, "    B3:%d  ", b3_num);
		else
			lcd_disp(Line5, "    B3:@  ");
	}
	else
	{
		lcd_disp(Line1, "       STA");
		lcd_disp(Line3, "    F:2000Hz  ");
		lcd_disp(Line4, "    D:10%%  ");
		lcd_disp(Line5, "              ");
	}
}