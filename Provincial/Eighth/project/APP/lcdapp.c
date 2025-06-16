#include "lcdapp.h"

uint8_t platform_cur = 1;		// 当前平台
uint8_t platform_goal_up[4] = {0};	// 上升目标
uint8_t platform_goal_down[4] = {0};	// 下降目标
uint8_t work_state = 0;		// 升降机工作状态
uint8_t platform_goals[3] = {0};
uint8_t goals_num = 0;

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
	lcd_disp(Line2, "     Platform");
	lcd_disp(Line4, "         %d ", platform_cur);
	rtc_proc();
	lcd_disp(Line6, "     %02d:%02d:%02d ", sTime.Hours, sTime.Minutes, sTime.Seconds);
}