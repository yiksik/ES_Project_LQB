#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t duty_pa1 = 0, duty_pa2 = 0;
uint8_t mode = 0;
uint8_t lock = 0;
float pu_value = 2.4f, pd_value = 1.2f;
uint8_t error = 0;
float para_show[2] = {2.4f, 1.2f};


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
	if(!error)
	{
		if(!lcd_view)
		{
			lcd_disp(Line1, "        DATA");
			lcd_disp(Line3, "     A=%.1fV  ", adc_value);
			lcd_disp(Line4, "     P=%d%%-%d%%    ", duty_pa1, duty_pa2);
			if(mode)
				lcd_disp(Line5, "     MODE=H    ");
			else
				lcd_disp(Line5, "     MODE=L    ");
			if(lock)
				lcd_disp(Line6, "     LOCK=Y    ");
			else
				lcd_disp(Line6, "     LOCK=N    ");
		}
		else
		{
			lcd_disp(Line1, "        PARA");
			lcd_disp(Line3, "     PU=%.1fV  ", para_show[0]);
			lcd_disp(Line4, "     PD=%.1fV  ", para_show[1]);
			lcd_disp(Line5, "                 ");
			lcd_disp(Line6, "                 ");
		}
	}
}