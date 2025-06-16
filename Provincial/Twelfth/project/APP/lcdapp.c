#include "lcdapp.h"

uint8_t lcd_view = 0;

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
		lcd_disp(Line3, "   CNBR:%d   ", cnbr_num);
		lcd_disp(Line5, "   VNBR:%d   ", vnbr_num);
		lcd_disp(Line7, "   IDLE:%d", idle_num);
	}
	else
	{
		lcd_disp(Line1, "       Para");
		lcd_disp(Line3, "   CNBR:%.2f", cnbr_fee);
		lcd_disp(Line5, "   VNBR:%.2f", vnbr_fee);
		lcd_disp(Line7, "          ");
	}
}