#include "keyapp.h"

uint8_t key_val, key_down, key_old = 0x00;
uint8_t set_obj = 0;

void key_proc(void)
{
	key_val = 0x00;
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
			if(!lcd_view)
				write_eeprom();
		break;
		case 2:
			if(lcd_view)
			{
				if(++set_obj == 3)
					set_obj = 0;
			}
		break;
		case 3:
			if(lcd_view)
			{
				if(th_arr[set_obj] < 95)
					th_arr[set_obj] += 5;
			}
		break;
		case 4:
			if(lcd_view)
			{
				if(th_arr[set_obj] > 5)
					th_arr[set_obj] -= 5;
			}
		break;
		default:break;
	}
}