#include "keyapp.h"

uint8_t key_val, key_down, key_up, key_old = 0x00;

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
		break;
		case 2:
			if(lcd_view)
			{
				cnbr_fee += 0.5f;
				vnbr_fee += 0.5f;
			}
		break;
		case 3:
			if(lcd_view && vnbr_fee > 0.51f)
			{
				cnbr_fee -= 0.5f;
				vnbr_fee -= 0.5f;
			}
		break;
		case 4:
			tim17_switch();
		break;
		default:break;
	}
}