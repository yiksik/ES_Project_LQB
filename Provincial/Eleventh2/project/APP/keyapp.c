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
			if(lcd_view)
			{
				ucled &= 0xfd;
				led_renew();
			}
			else
			{
				ucled |= 0x02;
				led_renew();
			}
		break;
		case 2:
			if(lcd_view)
			{
				if((duty_pa6_set+=10) == 100)
					duty_pa6_set = 10;
				if(work_mode == 1)
				{
					// 手动控制
					duty_pa6 = duty_pa6_set * 1.0f / 100.0f;
					pa6_duty_renew();
				}
			}
		break;
		case 3:
			if(lcd_view)
			{
				if((duty_pa7_set+=10) == 100)
					duty_pa7_set = 10;
				if(work_mode == 1)
				{
					// 手动控制
					duty_pa7 = duty_pa7_set * 1.0f / 100.0f;
					pa7_duty_renew();
				}
			}
		break;
		case 4:
			work_mode ^= 1;
			if(work_mode)
			{
				duty_pa6 = duty_pa6_set * 1.0f / 100.0f;
				pa6_duty_renew();
				duty_pa7 = duty_pa7_set * 1.0f / 100.0f;
				pa7_duty_renew();
				ucled &= 0xfe;
				led_renew();
			}
			else
			{
				duty_pa6 = duty_pa7 = adc_value / 3.3f;
				pa6_duty_renew();
				pa7_duty_renew();
				ucled |= 0x01;
				led_renew();
			}
		break;
		default:break;
	}
}