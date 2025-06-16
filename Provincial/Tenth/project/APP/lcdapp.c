#include "lcdapp.h"

uint8_t lcd_view = 0;
uint8_t status_value = 0;	//0-upper;1-normal;2-lower
float temper_th[2] = {2.4, 1.2};
uint8_t led_pos[2] = {0, 1};

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
		lcd_disp(Line1, "     Main       ");
		lcd_disp(Line3, "   Volt:%.2fV       ", adc_value);
		switch(status_value)
		{
			case 0:
				lcd_disp(Line4, "   Status:Upper      ");
			break;
			case 1:
				lcd_disp(Line4, "   Status:Normal     ");
			break;
			case 2:
				lcd_disp(Line4, "   Status:Lower      ");
			break;
			default:break;
		}
		lcd_disp(Line5, "                         ");
		lcd_disp(Line6, "                         ");
	}
	else
	{
		lcd_disp(Line1, "     Setting  ");
		switch(set_obj)
		{
			case 0:
				LCD_SetBackColor(Green);
				lcd_disp(Line3, "   Max Volt:%.2fV     ", temper_th[0]);
				LCD_SetBackColor(Black);
				lcd_disp(Line4, "   Min Volt:%.2fV     ", temper_th[1]);
				lcd_disp(Line5, "   Upper:LD%d         ", led_pos[0]+1);
				lcd_disp(Line6, "   Lower:LD%d         ", led_pos[1]+1);
			break;
			case 1:
				lcd_disp(Line3, "   Max Volt:%.2fV     ", temper_th[0]);
				LCD_SetBackColor(Green);
				lcd_disp(Line4, "   Min Volt:%.2fV     ", temper_th[1]);
				LCD_SetBackColor(Black);
				lcd_disp(Line5, "   Upper:LD%d         ", led_pos[0]+1);
				lcd_disp(Line6, "   Lower:LD%d         ", led_pos[1]+1);
			break;
			case 2:
				lcd_disp(Line3, "   Max Volt:%.2fV     ", temper_th[0]);
				lcd_disp(Line4, "   Min Volt:%.2fV     ", temper_th[1]);
				LCD_SetBackColor(Green);
				lcd_disp(Line5, "   Upper:LD%d         ", led_pos[0]+1);
				LCD_SetBackColor(Black);
				lcd_disp(Line6, "   Lower:LD%d         ", led_pos[1]+1);
			break;
			case 3:
				lcd_disp(Line3, "   Max Volt:%.2fV     ", temper_th[0]);
				lcd_disp(Line4, "   Min Volt:%.2fV     ", temper_th[1]);
				lcd_disp(Line5, "   Upper:LD%d         ", led_pos[0]+1);
				LCD_SetBackColor(Green);
				lcd_disp(Line6, "   Lower:LD%d         ", led_pos[1]+1);
				LCD_SetBackColor(Black);
			break;
			default:break;
		}
		
	}
}