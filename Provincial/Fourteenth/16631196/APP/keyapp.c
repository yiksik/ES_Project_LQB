#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;
uint8_t tf_state =  0;
uint8_t set_obj = 0;
uint8_t key4down = 0;
uint32_t key4tick = 0;
uint8_t duty_lock = 0;

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
			if(++lcd_view == 3)
				lcd_view = 0;
			if(lcd_view == 1)
			{
				set_obj = 0;
				ucled &= 0xfe;
				led_renew();
			}
			else if(lcd_view == 2)
			{
				r_value = r_value_show;
				k_value = k_value_show;
			}
			else
			{
				ucled |= 0x01;
				led_renew();
			}
		break;
		case 2:
			if(!lcd_view && !tf_state)
			{
				// 数据界面下且不在转换中
				tf_state = 1;		// 开始转换
				__HAL_TIM_SetCounter(&htim6, 0);
				HAL_TIM_Base_Start_IT(&htim6);
				count_led2 = 0;
				ucled |= 0x02;
				led_renew();
			}
			else if(lcd_view == 1)
			{
				set_obj ^= 1;
			}
		break;
		case 3:
			if(lcd_view == 1)
			{
				if(!set_obj)
				{
					if(++r_value_show == 11)
						r_value_show = 1;
				}
				else
				{
					if(++k_value_show == 11)
						k_value_show = 1;
				}	
			}
		break;
		case 4:
			if(lcd_view == 1)
			{
				if(!set_obj)
				{
					if(--r_value_show == 0)
						r_value_show = 10;
				}
				else
				{
					if(--k_value_show == 0)
						k_value_show = 10;
				}	
			}
			if(!lcd_view && !key4down)
			{
				key4down = 1;
				key4tick = uwTick;
			}
		break;
		default:break;
	}
	if(key4down && key_up == 4)
	{
		key4down = 0;
		if(uwTick - key4tick >= 1990)
		{
			duty_lock = 1;
			ucled |= 0x04;
			led_renew();
		}
		else
		{
			duty_lock = 0;
			ucled &= 0xfb;
			led_renew();
		}
	}
}