#include "keyapp.h"

uint8_t key_val, key_down, key_old = 0;
uint8_t b3_b4_flag = 0;

void key_proc(void)
{
	key_val = 0;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val |= 0x01;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
		key_val |= 0x02;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
		key_val |= 0x04;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val |= 0x08;
	
	key_down = key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 0x01:
			state_output ^= 1;
			tim_switch();
		break;
		case 0x02:
			lcd_view ^= 1;
			LCD_Clear(Black);		// 一般不这么干，图快而已
			if(!lcd_view)
			{
				tim_freq_renew();	
				write_eeprom();
			}
		break;
		case 0x04:
			if(lcd_view)
			{
				freq += 1000;
				if(freq == 11000)
					freq = 1000;
			}
		break;
		default:break;
	}
}