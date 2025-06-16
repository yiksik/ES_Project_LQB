#include "lcdapp.h"

// 全局变量str用于承接准备刷新显示的字符串
char str[30];
/* 
	统一使用方法：
	1.使用sprintf格式化字符串str
	如sprintf(str, "hello:%d  ", key_test);
	2.使用lcd_disp(Line0, 起始列, 结束列);
	如lcd_disp(Line0, 0, 20);
*/


void lcd_init(void)
{
	LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(White);
	
    // 1.初始化的时候 和 2.界面发生切换 的时候可以刷新整行
	sprintf(str, "hello:%d  ", key_test);
	lcd_disp(Line0, 0, 20);		//列0开始， 列19结束
}

/*
	核心代码：lcd显示刷新
	功能：将当前str字符串存储的值，从Line行的startColumn列开始显示，到endColumn列结束
*/
void lcd_disp(u8 Line, u16 startColumn, u16 endColumn)
{
    // 该部分代码参考LCD_DisplayStringLine源码理解记忆
	u8 i = 0;
	while((startColumn < endColumn) && (str[i] != 0))
	{
		LCD_DisplayChar(Line, 319-16*startColumn, str[i++]);
		startColumn++;
	}
}

void lcd_proc(void)
{
    // 当界面不发生变化时，只刷新值的显示内容，即只需要刷新其对应的位置。
    // tips：对应可以确定更新事件发生的值，可以在事件发生时手动刷新（类似于LED），而非按一定频率动态扫描，反应更灵敏也减少了很大一部分资源的消耗。
	sprintf(str, "%d  ", key_test);
	lcd_disp(Line0, 6, 9);
}