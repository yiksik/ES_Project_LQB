#include "keyapp.h"

uint8_t key_val,key_old = 0, key_down, key_up;

void key_proc(void)
{
	key_val = 0;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val |= 0X01;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == GPIO_PIN_RESET)
		key_val |= 0X02;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == GPIO_PIN_RESET)
		key_val |= 0X04;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
		key_val |= 0X08;
	
	key_down = key_val & (key_val ^ key_old);
	key_up = ~key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 0x01:
			
		break;
		case 0x02:
			
		break;
		case 0x04:
			
		break;
		case 0x08:
			
		break;
		default:break;
	}
}