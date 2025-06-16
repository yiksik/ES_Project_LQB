#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t work_mode = 0;

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
	lcd_disp(Line8, "pa6:%.2f%%  ", pa6_duty);
	lcd_disp(Line9, "pa7:%.2f%%  ", pa7_duty);
	if(!lcd_view)
	{
		lcd_disp(Line0, "      Data");
		lcd_disp(Line2, "    V:%.2fV", adc_value);
		if(!work_mode)
			lcd_disp(Line4, "    Mode:AUTO");
		else
			lcd_disp(Line4, "    Mode:MANU");
	}
	else
	{
		lcd_disp(Line0, "      Para");
		lcd_disp(Line2, "    PA6:%d%%  ", duty_pa6_set);
		lcd_disp(Line4, "    PA7:%d%%  ", duty_pa7_set);
	}
}