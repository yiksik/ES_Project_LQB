#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t state_output = 0;
uint32_t freq = 1000;

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
	if(lcd_view)
	{
		lcd_disp(Line1, "     Setting");
		lcd_disp(Line3, "Freq:%dKHz  ", freq / 1000);
	}
	else
	{
		lcd_disp(Line1, "     Para    ");
		lcd_disp(Line3, "V0: %.2fV", adc_value);
		if(state_output)
			lcd_disp(Line4, "ST: ON ");
		else
			lcd_disp(Line4, "ST: OFF");
		lcd_disp(Line5, "PA: PA9:%d  ", duty1);
		lcd_disp(Line6, "    PB14:%d  ", duty2);
		lcd_disp(Line7, "    %dKHz  ", freq / 1000);
	}
}