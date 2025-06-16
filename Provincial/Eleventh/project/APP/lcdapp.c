#include "lcdapp.h"

uint8_t lcd_view = 0;
uint32_t time_rec = 0;
uint32_t time_start = 0;
uint8_t state = 0;
float th_temper[2] = {3.0f, 1.0f};
float th_temper_real[2] = {3.0f, 1.0f};

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
		lcd_disp(Line0, "      Data");
		lcd_disp(Line2, " V:%.2fV    ", adc_value);
		if(state)
			time_rec = uwTick - time_start;
		lcd_disp(Line3, " T:%ds       ", time_rec / 1000);
	}
	else
	{
		lcd_disp(Line0, "      Para");
		lcd_disp(Line2, " Vmax:%.2fV ", th_temper[0]);
		lcd_disp(Line3, " Vmin:%.2fV ", th_temper[1]);
	}
}