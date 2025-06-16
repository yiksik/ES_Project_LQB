#include "lcdapp.h"

uint8_t lcd_view = 0;
uint32_t freq_pa1 = 0;
uint8_t x_value = 1, y_value = 2;
uint8_t n_value[2] = {0};
float a_value[2] = {0.0f}, t_value[2] = {0.0f}, h_value[2] = {0.0f};
uint8_t channel = 0;

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

void lcd_res(void)
{
	static uint8_t state = 0;
	state ^= 1;
	if(state)
	{
		LCD_WriteReg(R1, 0x0100);
		LCD_WriteReg(R96, 0xA700);
		ucled &= 0xf7;
		led_renew();
	}
	else
	{
		LCD_WriteReg(R1, 0x0000);
		LCD_WriteReg(R96, 0x2700);
		ucled |= 0x08;
		led_renew();
	}
	LCD_Clear(Black);
}

void lcd_proc(void)
{
	if(!lcd_view)
	{
		lcd_disp(Line1, "        DATA   ");
		lcd_disp(Line3, "     PA4=%.2f", adc_pa4_real);
		lcd_disp(Line4, "     PA5=%.2f", adc_pa5_real);
		lcd_disp(Line5, "     PA1=%d     ", freq_pa1);
		lcd_disp(Line6, "                ");
	}
	else if(lcd_view == 1)
	{
		lcd_disp(Line1, "        PARA   ");
		lcd_disp(Line3, "     X=%d     ", x_value);
		lcd_disp(Line4, "     Y=%d     ", y_value);
		lcd_disp(Line5, "                ");
		lcd_disp(Line6, "                ");
	}
	else
	{
		if(!channel)
			lcd_disp(Line1, "        REC-PA4");
		else
			lcd_disp(Line1, "        REC-PA5");
		lcd_disp(Line3, "     N=%d     ", n_value[channel]);
		lcd_disp(Line4, "     A=%.2f  ", a_value[channel]);
		lcd_disp(Line5, "     T=%.2f  ", t_value[channel]);
		lcd_disp(Line6, "     H=%.2f  ", h_value[channel]);
	}
}