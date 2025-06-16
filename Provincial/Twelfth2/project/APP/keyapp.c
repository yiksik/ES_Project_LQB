#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;
uint8_t led_flag = 1;

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
			lcd_view ^= 1;
			if(lcd_view)
			{
				ucled |= 0x02;
				ucled &= 0xfe;
			}
			else
			{
				ucled |= 0x01;
				ucled &= 0xfd;
			}
			led_renew();
		break;
		case 2:
			if(lcd_view)
			{
				if(r_value < 10)
					r_value += 2;
			}
		break;
		case 3:
			if(lcd_view)
			{
				if(r_value > 2)
					r_value -= 2;
			}
		break;
		case 4:
			led_flag ^= 1;
			led_renew();
		break;
		default:break;
	}
}