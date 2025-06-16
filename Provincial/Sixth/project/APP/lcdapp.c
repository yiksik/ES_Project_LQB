#include "lcdapp.h"

uint8_t lcd_view = 0;	//0-LCD显示界面； 1-定时上报时间设置界面
char lcd_buffer[30];

void lcd_init(void)
{
	LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	sprintf(lcd_buffer, "V1: %.2fV", adc_value);
	lcd_disp(Line0, 0, 20);
	sprintf(lcd_buffer, "k: %.1f", k_value);
	lcd_disp(Line1, 0, 20);
	sprintf(lcd_buffer, "LED: ON ");
	lcd_disp(Line2, 0, 20);
	sprintf(lcd_buffer, "T: %02d-%02d-%02d", 23, 59, 55);
	lcd_disp(Line3, 0, 20);
}

void lcd_disp(uint8_t line, uint8_t start, uint8_t end)
{
	uint8_t i = 0;
	while((start < end) && lcd_buffer[i])
	{
		LCD_DisplayChar(line, 319-start*16, lcd_buffer[i++]);
		++start;
	}
}

void lcd_proc(void)
{
	
}