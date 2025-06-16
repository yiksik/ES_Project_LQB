#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;
uint8_t ans_wrong = 0;
uint8_t led2_state = 0;

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
			if(!lcd_view)
			{
				if(!b1_down)
				{
					b1_down = 1;
					b1_num = 0;
				}
				else if(b1_down)
				{
					if(++b1_num == 10)
						b1_num = 0;
				}
			}
		break;
		case 2:
			if(!lcd_view)
			{
				if(!b2_down)
				{
					b2_down = 1;
					b2_num = 0;
				}
				else if(b2_down)
				{
					if(++b2_num == 10)
						b2_num = 0;
				}
			}
		break;
		case 3:
			if(!lcd_view)
			{
				if(!b3_down)
				{
					b3_down = 1;
					b3_num = 0;
				}
				else if(b3_down)
				{
					if(++b3_num == 10)
						b3_num = 0;
				}
			}
		break;
		case 4:
			if(!lcd_view)
			{
				if(b1_down && b2_down && b3_down && ans[0]==b1_num && ans[1]==b2_num && ans[2]==b3_num)
				{
					// 密码验证成功
					lcd_view = 1;		// 切换lcd显示
					pwm_switch();		// 更新pwm
					__HAL_TIM_SetCounter(&htim6, 0);
					HAL_TIM_Base_Start_IT(&htim6);
					ucled |= 0x01;
					led_renew();
				}
				else
				{
					// 密码验证失败
					ans_wrong++;
					b1_down = b2_down = b3_down = 0;
					if(ans_wrong >= 3)
					{
						led2_state = 1;
						led2_count = 0;
						ucled |= 0x02;
						led_renew();
					}
				}
			}
		break;
		default:break;
	}
}