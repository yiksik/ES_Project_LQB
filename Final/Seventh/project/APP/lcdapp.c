#include "lcdapp.h"

uint8_t lcd_view = 0;
uint32_t record_times = 0;
uint8_t record_index = 0;
uint8_t set_obj = 0;
int th_temper = 40;
uint8_t th_wet = 80;
uint8_t record_gap = 1;

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
//	lcd_disp(Line0, "adc:%.2f", adc_value);
//	lcd_disp(Line1, "temper:%d  ", temper_value);
//	lcd_disp(Line2, "ic_freq:%d  ", freq_ic);
//	lcd_disp(Line3, "wet:%d  ", wet_value);
//	lcd_disp(Line4, "%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
	if(!lcd_view)
	{
		lcd_disp(Line1, "Data");
		lcd_disp(Line2, "temper:%dC    ", temper_value);
		lcd_disp(Line3, "wet:%d%%    ", wet_value);
		lcd_disp(Line4, "Time:%02d:%02d:%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
		lcd_disp(Line5, "record times:%d  ", record_times);
	}
	else
	{
		lcd_disp(Line1, "Para");
		switch(set_obj)
		{
			case 0:
				LCD_SetTextColor(Green);
				lcd_disp(Line2, "th_temper:%dC    ", th_temper);
				LCD_SetTextColor(White);
				lcd_disp(Line3, "th_wet:%d%%    ", th_wet);
				lcd_disp(Line4, "gap: %dS            ", record_gap);
				lcd_disp(Line5, "test: %.1fKHz        ", freq_out / 1000.0f);
			break;
			case 1:
				lcd_disp(Line2, "th_temper:%dC    ", th_temper);
				LCD_SetTextColor(Green);
				lcd_disp(Line3, "th_wet:%d%%    ", th_wet);
				LCD_SetTextColor(White);
				lcd_disp(Line4, "gap: %dS            ", record_gap);
				lcd_disp(Line5, "test: %.1fKHz        ", freq_out / 1000.0f);
			break;
			case 2:
				lcd_disp(Line2, "th_temper:%dC    ", th_temper);
				lcd_disp(Line3, "th_wet:%d%%    ", th_wet);
				LCD_SetTextColor(Green);
				lcd_disp(Line4, "gap: %dS            ", record_gap);
				LCD_SetTextColor(White);
				lcd_disp(Line5, "test: %.1fKHz        ", freq_out / 1000.0f);
			break;
			case 3:
				lcd_disp(Line2, "th_temper:%dC    ", th_temper);
				lcd_disp(Line3, "th_wet:%d%%    ", th_wet);
				lcd_disp(Line4, "gap: %dS            ", record_gap);
				LCD_SetTextColor(Green);
				lcd_disp(Line5, "test: %.1fKHz        ", freq_out / 1000.0f);
				LCD_SetTextColor(White);
			break;
			default:break;
		}
	}
}