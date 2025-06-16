#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t lcd0_view = 0;
float pd_value = 1000.0f, ph_value = 5000.0f, px_value = 0.0f;
uint8_t nda_value = 0, ndb_value = 0, nha_value = 0, nhb_value = 0;
uint8_t set_obj = 0;

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
//	lcd_disp(Line0, "%d,%d      ", freq_pa, freq_pb);
	if(!lcd_view)
	{
		if(!lcd0_view)
		{
			lcd_disp(Line1, "        DATA");
			if(freq_pa < 0)
				lcd_disp(Line3, "     A=NULL    ");
			else
			{
				if(freq_pa < 1000)
					lcd_disp(Line3, "     A=%dHz    ", (uint32_t)freq_pa);
				else
					lcd_disp(Line3, "     A=%.2fKHz    ", freq_pa / 1000.0f);
			}
			if(freq_pb < 0)
			{
				lcd_disp(Line4, "     B=NULL    ");
			}
			else
			{
				if(freq_pb < 1000)
					lcd_disp(Line4, "     B=%dHz   ", (uint32_t)freq_pb);
				else
					lcd_disp(Line4, "     B=%.2fKHz    ", freq_pb / 1000.0f);
			}
		}
		else
		{
			lcd_disp(Line1, "        DATA");
			if(freq_pa < 0)
				lcd_disp(Line3, "     A=NULL    ");
			else
			{
				if(period_pa_us < 1000)
					lcd_disp(Line3, "     A=%duS    ", (uint32_t)period_pa_us);
				else
					lcd_disp(Line3, "     A=%.2fmS    ", period_pa_us / 1000.0f);
			}
			if(freq_pb < 0)
				lcd_disp(Line3, "     A=NULL    ");
			else
			{
				if(period_pb_us < 1000)
					lcd_disp(Line4, "     B=%duS   ", (uint32_t)period_pb_us);
				else
					lcd_disp(Line4, "     B=%.2fmS    ", period_pb_us / 1000.0f);
			}
		}
		lcd_disp(Line5, "                ");
		lcd_disp(Line6, "                ");
	}
	else if(lcd_view == 1)
	{
		lcd_disp(Line1, "        PARA");
		lcd_disp(Line3, "     PD=%dHz    ", (uint32_t)pd_value);
		lcd_disp(Line4, "     PH=%dHz    ", (uint32_t)ph_value);
		lcd_disp(Line5, "     PX=%dHz    ", (int32_t)px_value);
		lcd_disp(Line6, "                ");
	}
	else
	{
		lcd_disp(Line1, "        RECD");
		lcd_disp(Line3, "     NDA=%d     ", (uint32_t)nda_value);
		lcd_disp(Line4, "     NDB=%d     ", (uint32_t)ndb_value);
		lcd_disp(Line5, "     NHA=%d     ", (uint32_t)nha_value);
		lcd_disp(Line6, "     NHB=%d     ", (uint32_t)nhb_value);
	}
}