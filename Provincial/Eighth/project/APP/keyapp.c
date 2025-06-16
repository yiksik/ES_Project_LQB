#include "keyapp.h"

uint8_t key_val, key_down, key_old = 0;

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
	key_old = key_val;
	
	switch(key_down)
	{
		case 1:
			if(work_state == 0 && platform_cur != 1)
			{
				platform_goal_down[0] = 1;
				ucled |= 0x01;
				led_renew();
				tick = 1;
			}
		break;
		case 2:
			if(work_state == 0 && platform_cur != 2)
			{
				if(platform_cur == 1)
				{
					platform_goal_up[1] = 1;
				}
				else
				{
					platform_goal_down[1] = 1;
				}
				ucled |= 0x02;
				led_renew();
				tick = 1;
			}
		break;
		case 3:
			if(work_state == 0 && platform_cur != 3)
			{
				if(platform_cur == 4)
				{
					platform_goal_down[2] = 1;
				}
				else
				{
					platform_goal_up[2] = 1;
				}
				ucled |= 0x04;
				led_renew();
				tick = 1;
			}
		break;
		case 4:
			if(work_state == 0 && platform_cur != 4)
			{
				platform_goal_up[3] = 1;
				ucled |= 0x08;
				led_renew();
				tick = 1;
			}
		break;
		default:break;
	}
}