#include "lcdapp.h"

uint8_t store_pos = 1;
time_t times[6] = {0};

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

void lcd_disp_color(uint8_t line, uint8_t start, uint8_t end, char *format, ...)
{
	char str[30];
	va_list arg;
	va_start(arg, format);
	vsprintf(str, format, arg);
	va_end(arg);
	
	u32 i = 0;
  u16 refcolumn = 319;

  while ((str[i] != 0) && (i < start))
  {
     LCD_DisplayChar(line, refcolumn, str[i]);
     refcolumn -= 16;
     i++;
  }
	LCD_SetTextColor(Green);
	while ((str[i] != 0) && (i < end))
  {
     LCD_DisplayChar(line, refcolumn, str[i]);
     refcolumn -= 16;
     i++;
  }
	LCD_SetTextColor(White);
	while ((str[i] != 0) && (i < 20))
  {
     LCD_DisplayChar(line, refcolumn, str[i]);
     refcolumn -= 16;
     i++;
  }
}

void lcd_proc(void)
{
	lcd_disp(Line1, "  NO %d ", store_pos);
	if(state == 1 || state == 3)
		lcd_disp(Line3, "    %02d:%02d:%02d ", run_time/3600, run_time%3600/60, run_time%60);
	else if(state == 0)
		lcd_disp(Line3, "    %02d:%02d:%02d ", times[store_pos].hours, times[store_pos].mins, times[store_pos].secs);
	else
		switch(set_obj)
		{
			case 0:
				lcd_disp_color(Line3, 4, 6, "    %02d:%02d:%02d ", times[0].hours, times[0].mins, times[0].secs);
			break;
			case 1:
				lcd_disp_color(Line3, 7, 9, "    %02d:%02d:%02d ", times[0].hours, times[0].mins, times[0].secs);
			break;
			case 2:
				lcd_disp_color(Line3, 10, 12, "    %02d:%02d:%02d ", times[0].hours, times[0].mins, times[0].secs);
			break;
		}
	switch(state)
	{
		case 0:
			lcd_disp(Line5, "      Standby  ");
		break;
		case 1:
			lcd_disp(Line5, "      Running  ");
		break;
		case 2:
			lcd_disp(Line5, "      Setting  ");
		break;
		case 3:
			lcd_disp(Line5, "      Pause    ");
		break;
		default: break;
	}
	
}