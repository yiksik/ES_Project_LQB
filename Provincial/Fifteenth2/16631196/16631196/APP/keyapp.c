#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;
uint8_t set_obj = 0;
uint8_t key4down = 0;
uint32_t key4tick = 0;

void key_proc(void)
{
	key_val = 0;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val = 1;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
		key_val = 2;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
		key_val = 3;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val = 4;
	
	key_down = key_val & (key_val ^ key_old);
	key_up = ~key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 1:
			lcd_view ^= 1;
			if(!lcd_view)
			{
				if(para_show[0] <= para_show[1] + 0.01f)
				{
					// error
					__HAL_TIM_SET_COUNTER(&htim6, 0);
					HAL_TIM_Base_Start_IT(&htim6);
					error = 1;
					LCD_Clear(Black);
					lcd_disp(Line4, "       ERROR");
					lcd_view = 1;		// 返回参数界面
				}
				else
				{
					pu_value = para_show[0];
					pd_value = para_show[1];
				}
			}
			else
			{
				set_obj = 0;
			}
		break;
		case 2:
			if(!lcd_view)
			{
				if(!lock)
				{
					mode ^= 1;
					if(mode)
					{
						ucled |= 0x01;
					}	
					else
					{
						ucled &= 0xfe;
					}
					led_renew();
					pwm_freq_renew();
				}
			}
			else
			{
				set_obj ^= 1;
			}
		break;
		case 3:
			if(lcd_view)
			{
				if(para_show[set_obj] < 3.29f)
				{
					para_show[set_obj] += 0.3f;
				}
			}
		break;
		case 4:
			if(lcd_view)
			{
				if(para_show[set_obj] > 0.01f)
				{
					para_show[set_obj] -= 0.3f;
				}
			}
			else
			{
				if(!key4down)
				{
					key4down = 1;
					key4tick = uwTick;
				}
			}
		break;
		default:break;
	}
	if(key4down && key_up == 4)
	{
		key4down = 0;
		if(uwTick >= key4tick + 1500)
		{
			// 长按
			if(!lock)
			{
				ucled |= 0x02;
				led_renew();
			}
			lock = 1;
		}
		else
		{
			// 短按
			if(lock)
			{
				ucled &= 0xfd;
				led_renew();
			}
			lock = 0;
		}
	}
}