#include "keyapp.h"

uint8_t key_down, key_up, key_val, key_old = 0;
uint8_t key3down = 0;
uint32_t key3tick = 0;

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
			if(lcd_view == 1)
				switch(set_obj)
				{
					case 0:
						if(pd_value < 999.0f)
							pd_value += 100.0f;
					break;
					case 1:
						if(ph_value < 9999.0f)
							ph_value += 100.0f;
					break;
					case 2:
						if(px_value < 999.0f)
							px_value += 100.0f;
					break;
					default:break;
				}
		break;
		case 2:
			if(lcd_view == 1)
				switch(set_obj)
				{
					case 0:
						if(pd_value > 101.0f)
							pd_value -= 100.0f;
					break;
					case 1:
						if(ph_value > 1001.f)
							ph_value -= 100.0f;
					break;
					case 2:
						if(px_value > -999.0f)
							px_value -= 100.0f;
					break;
					default:break;
				}
		break;
		case 3:
			if(lcd_view == 0)
				lcd0_view ^= 1;
			else if(lcd_view == 1)
			{
				if(++set_obj == 3)
					set_obj = 0;
			}
			else if(lcd_view == 2 && !key3down)
			{
				key3down = 1;
				key3tick = uwTick;
			}
		break;
		case 4:
			if(++lcd_view == 3)
				lcd_view = 0;
			if(lcd_view == 1)
			{
				set_obj = 0;
				ucled &= 0xfe;
				led_renew();
			}
			else if(lcd_view == 0)
			{
				lcd0_view = 0;
				ucled |= 0x01;
				led_renew();
			}
		break;
		default:break;
	}
	if(key3down && key_up == 3)
	{
		key3down = 0;
		if(uwTick - key3tick >= 1000)
		{
			nda_value = ndb_value = nha_value = nhb_value = 0;
			if(led8_state)
			{
				led8_state = 0;
				ucled &= 0x7f;
				led_renew();
			}
		}
	}
}