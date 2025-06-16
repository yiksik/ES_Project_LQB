#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t th_arr[3] = {30, 50, 70};

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
	switch(lcd_view)
	{
		case 0:
			lcd_disp(Line1, "Liquid Level");
			lcd_disp(Line3, "Height:%dcm  ", height_value);
			lcd_disp(Line4, "ADC:%.2fV", adc_value);
			lcd_disp(Line5, "Level:%d ", level_value);
		break;
		
		case 1:
			lcd_disp(Line1, "Para Setup  ");
			if(set_obj == 0)
			{
				LCD_SetTextColor(Green);
				lcd_disp(Line3, "Th1:%dcm    ", th_arr[0]);
				LCD_SetTextColor(White);
				lcd_disp(Line4, "Th2:%dcm    ", th_arr[1]);
				lcd_disp(Line5, "Th3:%dcm    ", th_arr[2]);
			}
			else if(set_obj == 1)
			{
				lcd_disp(Line3, "Th1:%dcm    ", th_arr[0]);
				LCD_SetTextColor(Green);
				lcd_disp(Line4, "Th2:%dcm    ", th_arr[1]);
				LCD_SetTextColor(White);
				lcd_disp(Line5, "Th3:%dcm    ", th_arr[2]);
			}
			else
			{
				lcd_disp(Line3, "Th1:%dcm    ", th_arr[0]);
				lcd_disp(Line4, "Th2:%dcm    ", th_arr[1]);
				LCD_SetTextColor(Green);
				lcd_disp(Line5, "Th3:%dcm    ", th_arr[2]);
				LCD_SetTextColor(White);
			}
		break;
		default:break;
	}
	
}