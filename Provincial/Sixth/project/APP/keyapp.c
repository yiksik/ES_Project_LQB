#include "keyapp.h"

uint8_t key_old = 0, key_val, key_down, key_up;
uint8_t time_set[3] = {0};
uint8_t set_obj = 0;

void key_proc(void)
{
	key_val = 0;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val |= 0X01;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
		key_val |= 0X02;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
		key_val |= 0X04;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val |= 0X08;
	
	key_down = key_val & (key_val ^ key_old);
	key_up = ~key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 0x01:
			led1_switch ^= 0x01;
			if(!led1_switch)
			{
				led1_state = 0;
				ucled &= 0xfe;
				led_renew();
				if(!lcd_view)
				{
					sprintf(lcd_buffer, "FF");
					lcd_disp(Line2, 6, 8);
				}
			}
			else
			{
				if(!lcd_view)
				{
					sprintf(lcd_buffer, "N ");
					lcd_disp(Line2, 6, 8);
				}
			}
		break;
		case 0x02:
			lcd_view ^= 0x01;
			if(lcd_view)
			{
				sprintf(lcd_buffer, "           ");
				lcd_disp(Line0, 0, 11);
				lcd_disp(Line1, 0, 11);
				lcd_disp(Line3, 0, 11);
				sprintf(lcd_buffer, "     Setting");
				lcd_disp(Line2, 0, 12);
				sprintf(lcd_buffer, "     %02d-%02d-%02d", time_set[0], time_set[1], time_set[2]);
				lcd_disp(Line4, 0, 13);
			}
			else
			{
				sprintf(lcd_buffer, "V1: %.2fV", adc_value);
				lcd_disp(Line0, 0, 9);
				sprintf(lcd_buffer, "k: %.1f", k_value);
				lcd_disp(Line1, 0, 6);
				if(led1_switch)
				{
					sprintf(lcd_buffer, "LED: ON     ");
					lcd_disp(Line2, 0, 12);
				}
				else
				{
					sprintf(lcd_buffer, "LED: OFF    ");
					lcd_disp(Line2, 0, 12);
				}
				sprintf(lcd_buffer, "T: %02d-%02d-%02d", sTime.Hours, sTime.Minutes, sTime.Seconds);
				lcd_disp(Line3, 0, 13);
				sprintf(lcd_buffer, "             ");
				lcd_disp(Line4, 0, 13);

				rtc_set_alarm();
			}
		break;
		case 0x04:
			if(lcd_view)
			{
				if(++set_obj == 3)
					set_obj = 0;
			}
		break;
		case 0x08:
			if(lcd_view)
			{
				if(++time_set[set_obj] == 60)
					time_set[set_obj] = 0;
				sprintf(lcd_buffer, "     %02d-%02d-%02d", time_set[0], time_set[1], time_set[2]);
				lcd_disp(Line4, 0, 13);
			}
		break;
		default:break;
	}
}