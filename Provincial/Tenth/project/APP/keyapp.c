#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down;
uint8_t set_obj = 0;

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
	
	if(key_down == 1)
		lcd_view ^= 1;
	if(lcd_view == 1)
	{
		switch(key_down)
		{
			case 2:
				if(++set_obj == 4)
					set_obj = 0;
			break;
			case 3:
				switch(set_obj)
				{
					case 0:
						if(temper_th[0] + 0.3f < 3.31f)
						{
							temper_th[0] += 0.3f;
						}
					break;
					case 1:
						if(temper_th[1] + 0.3f < temper_th[0] - 0.01f)
						{
							temper_th[1] += 0.3f;
						}
					break;
					case 2:
						led_pos[0] = (led_pos[0] + 1) % 8;
						if(led_pos[0] == led_pos[1])
						{
							led_pos[0] = (led_pos[0] + 1) % 8;
						}
						ucled = 0;
						led_renew();
					break;
					case 3:
						led_pos[1] = (led_pos[1] + 1) % 8;
						if(led_pos[0] == led_pos[1])
						{
							led_pos[1] = (led_pos[1] + 1) % 8;
						}
						ucled = 0;
						led_renew();
					break;
					default:break;
				}
			break;
			case 4:
				switch(set_obj)
				{
					case 0:
						if(temper_th[0] - 0.3f > temper_th[1] + 0.01f)
						{
							temper_th[0] -= 0.3f;
						}
					break;
					case 1:
						if(temper_th[1] - 0.3f > -0.01f)
						{
							temper_th[1] -= 0.3f;
						}
					break;
					case 2:
						if(led_pos[0] == 0)
						{
							if(led_pos[1] == 7)
								led_pos[0] = 6;
							else
								led_pos[0] = 7;
						}
						else
						{
							led_pos[0] = led_pos[0] - 1;
							if(led_pos[0] == led_pos[1])
							{
								if(led_pos[0] == 0)
									led_pos[0] = 7;
								else
									led_pos[0] = led_pos[0] - 1;
							}
						}
						ucled = 0;
						led_renew();
					break;
					case 3:
						if(led_pos[1] == 0)
						{
							if(led_pos[0] == 7)
								led_pos[1] = 6;
							else
								led_pos[1] = 7;
						}
						else
						{
							led_pos[1] = led_pos[1] - 1;
							if(led_pos[0] == led_pos[1])
							{
								if(led_pos[1] == 0)
									led_pos[1] = 7;
								else
									led_pos[1] = led_pos[1] - 1;
							}
						}
						ucled = 0;
						led_renew();
					break;
					default:break;
				}
			break;
			default:break;
		}
	}
}