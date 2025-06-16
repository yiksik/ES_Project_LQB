#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;

uint8_t key1_duan = 0;
uint32_t key1_duan_tick = 0;
uint8_t key1_duan_chang = 0;
uint32_t key1_duan_chang_tick = 0;

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
	key_up = ~key_val & (key_val ^ key_old);
	key_old = key_val;
	
	switch(key_down)
	{
		case 0x01:
			if(!key1_duan)
			{
				key1_duan = 1;
				key1_duan_tick = uwTick;
			}
			else if(key1_duan && !key1_duan_chang)
			{
				key1_duan = 0;
				key1_duan_chang = 1;
				key1_duan_chang_tick = uwTick;
			}
		break;
		case 0x02:

		break;
		case 0x04:

		break;
		case 0x08:

		break;
		default:break;
	}
	if(key1_duan && uwTick - key1_duan_tick >= 300)
	{
		key1_duan = 0;
		printf("duan\r\n");
	}
	if(key1_duan_chang && key_up == 0x01)
	{
		key1_duan_chang = 0;
		if(uwTick - key1_duan_chang_tick >= 1000)
		{
			printf("duan + chang\r\n");
		}
	}		
}