#include "keyapp.h"

uint8_t key_val, key_down, key_up, key_old = 0;
uint8_t key_test = 0;

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
	
	key_down = key_val ^ (key_val & key_old);
	key_up  = ~key_val ^ (key_val & key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 0x01:
			key_test++;
		break;
		case 0x02:
			key_test--;
		break;
		case 0x04:
			key_test = 0;
		break;
		case 0x08:
			key_test = 255;
		break;
		default:break;
	}
}