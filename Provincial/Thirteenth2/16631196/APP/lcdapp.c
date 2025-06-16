#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t x_shop = 0, y_shop = 0;
float x_value = 1.0f, y_value = 1.0f;
uint32_t x_store = 10, y_store = 10;

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
		lcd_disp(Line1, "        SHOP ");
		lcd_disp(Line3, "     X:%d   ", x_shop);
		lcd_disp(Line4, "     Y:%d   ", y_shop);
	}
	else if(lcd_view == 1)
	{
		lcd_disp(Line1, "        PRISE ");
		lcd_disp(Line3, "     X:%.1f ", x_value);
		lcd_disp(Line4, "     Y:%.1f ", y_value);
	}
	else
	{
		lcd_disp(Line1, "        REP  ");
		lcd_disp(Line3, "     X:%d  ", x_store);
		lcd_disp(Line4, "     Y:%d  ", y_store);
	}
}