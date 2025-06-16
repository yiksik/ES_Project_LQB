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
			lcd_view ^= 1;
			if(!lcd_view)
				write_eeprom();
		break;
		case 2:
			if(lcd_view)
				if(++set_obj == 4)
					set_obj = 0;
		break;
		case 3:
			if(lcd_view)
			{
				switch(set_obj)
				{
					case 0:
						if(th_temper < 60)
							++th_temper;
					break;
					case 1:
						if(th_wet < 90)
							th_wet += 5;
					break;
					case 2:
						if(record_gap < 5)
							++record_gap;
					break;
					case 3:
						if(freq_out < 10000)
						{
							freq_out += 500;
							pwm_freq_renew();
						}
					break;
					default:break;
				}
			}
		break;
		case 4:
			if(lcd_view)
			{
				switch(set_obj)
				{
					case 0:
						if(th_temper > -20)
							--th_temper;
					break;
					case 1:
						if(th_wet > 10)
							th_wet -= 5;
					break;
					case 2:
						if(record_gap > 1)
							--record_gap;
					break;
					case 3:
						if(freq_out > 1000)
						{
							freq_out -= 500;
							pwm_freq_renew();
						}
					break;
					default:break;
				}
			}
		break;
		default:break;
	}
}