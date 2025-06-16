#include "lcdapp.h"

point_t points_buffer[100];		// 存储一百个坐标点
int point_start = 0;				// 当前坐标索引
int point_end = 1;					// 最后一个坐标索引
uint8_t lcd_view = 0;					// lcd界面：0-行程；1-参数；2-统计


void lcd_init(void)
{
	LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	
	lcd_disp(Line1, "        DATA");
	lcd_disp(Line3, "     ST=Idle");
	lcd_disp(Line4, "     CP=%d,%d", (uint16_t)points_buffer[point_start].x, (uint16_t)points_buffer[point_start].y);
	lcd_disp(Line5, "     TP=NF");
	lcd_disp(Line6, "     SE=%.1f",0.0);
	lcd_disp(Line7, "     RN=NF");
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
			// 行程界面
			switch(device_state)
			{
				case 0:
					lcd_disp(Line3, "     ST=Idle    ");		// 空闲
				break;
				case 1:
					lcd_disp(Line3, "     ST=Wait    ");		// 等待
				break;
				case 2:
					lcd_disp(Line3, "     ST=Busy    ");		// 运行
				break;
				default:break;
			}
			lcd_disp(Line4, "     CP=%d,%d    ", (uint16_t)points_buffer[point_start].x, (uint16_t)points_buffer[point_start].y);
			if(device_state == 0)
			{
				// 空闲状态
				lcd_disp(Line5, "     TP=NF      ");
				lcd_disp(Line7, "     RN=NF      ");
			}
			else
			{
				// 其他状态显示下一个目标点
				lcd_disp(Line5, "     TP=%d,%d    ", (uint16_t)points_buffer[(point_start+1)%100].x, (uint16_t)points_buffer[(point_start+1)%100].y);
				lcd_disp(Line7, "     RN=%d  ", (point_end+99-point_start)%100 );
			}
			lcd_disp(Line6, "     SE=%.1f    ", v_value_real);
		break;
		case 1:
			// 参数界面
			lcd_disp(Line3, "     R=%.1f", r_value);
			lcd_disp(Line4, "     B=%d  ", b_value);
		break;
		case 2:
			// 统计界面
			lcd_disp(Line3, "     TS=%.1f      ", ts_value);
			lcd_disp(Line4, "     TT=%d        ", tt_value/20);
		break;
		default:break;
	}
}