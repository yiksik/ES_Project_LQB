#include "lcdapp.h"

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
	// freq_pa5_ch1, freq_pa1_ch2, freq_pa2_ch3, freq_pa3_ch4;
	// 四路频率测量
	lcd_disp(Line0, "freq_pa1:%dHz    ", freq_pa1_ch2);
	lcd_disp(Line1, "duty_pa1:%.2f%%    ", duty_pa1);
	lcd_disp(Line2, "freq_pa2:%dHz    ", freq_pa2_ch3);
	lcd_disp(Line3, "duty_pa2:%.2f%%    ", duty_pa2);
} 