#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down;

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
			{
				// 退出参数界面
				if(th_temper[0] >= th_temper[1] + 1.0f)
				{
					th_temper_real[0] = th_temper[0];
					th_temper_real[1] = th_temper[1];
					ucled &= 0xfd;
					led_renew();
				}
				else
				{
					th_temper[0] = th_temper_real[0];
					th_temper[1] = th_temper_real[1];
					ucled |= 0x02;
					led_renew();
				}
			}
		break;
		case 2:
			if(lcd_view)
			{
				th_temper[0] += 0.1f;
				if(th_temper[0] > 3.31f)
					th_temper[0] = 0.0f;
			}
		break;
		case 3:
			if(lcd_view)
			{
				th_temper[1] += 0.1f;
				if(th_temper[1] > 3.31f)
					th_temper[1] = 0.0f;
			}
		break;
		case 4:
			
		break;
		default:break;
	}
}