#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t r_value = 4;

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
		lcd_disp(Line1, "       Data");
		lcd_disp(Line3, "   FRQ:%dHz     ", freq_pa1);
		lcd_disp(Line5, "   R37:%.2fV    ", adc_value);
	}
	else
	{
		lcd_disp(Line1, "       Para");
		lcd_disp(Line3, "      R:%d           ", r_value);
		lcd_disp(Line5, "                 ");
	}
}