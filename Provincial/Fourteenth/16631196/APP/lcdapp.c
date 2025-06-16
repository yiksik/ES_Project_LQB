#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t mode = 0;
uint8_t n_value = 0;
float mh_value = 0.0f, ml_value = 0.0f;

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
		lcd_disp(Line1, "        DATA");
		if(mode)
			lcd_disp(Line3, "     M=H");
		else
			lcd_disp(Line3, "     M=L");
		lcd_disp(Line4, "     P=%d%%    ", (uint32_t)(duty_value * 100));
		lcd_disp(Line5, "     V=%.1f       ", v_value);
	}
	else if(lcd_view == 1)
	{
		lcd_disp(Line1, "        PARA");
		lcd_disp(Line3, "     R=%d   ",  r_value_show);
		lcd_disp(Line4, "     K=%d       ", k_value_show);
		lcd_disp(Line5, "                ", ml_value);
	}
	else
	{
		lcd_disp(Line1, "        RECD");
		lcd_disp(Line3, "     N=%d   ",  n_value);
		lcd_disp(Line4, "     MH=%.1f    ", mh_value);
		lcd_disp(Line5, "     ML=%.1f    ", ml_value);
	}
}