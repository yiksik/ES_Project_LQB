#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;

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
			if(++lcd_view == 3)
			{
				lcd_view = 0;
			}
		break;
		case 2:
			switch(lcd_view)
			{
				case 0:
					if(++x_shop == x_store + 1)
					{
						x_shop = 0;
					}
				break;
				case 1:
					x_value += 0.1f;
					if(x_value > 2.01f)
						x_value = 1.0f;
				break;
				case 2:
					x_store++;
					write_eeprom(0);
					if(led2_state)
					{
						led2_state = 0;
						ucled &= 0xfd;
						led_renew();
					}
				break;
				default:break;
			}
		break;
		case 3:
			switch(lcd_view)
			{
				case 0:
					if(++y_shop == y_store + 1)
					{
						y_shop = 0;
					}
				break;
				case 1:
					y_value += 0.1f;
					if(y_value > 2.01f)
						y_value = 1.0f;
				break;
				case 2:
					y_store++;
					write_eeprom(1);
					if(led2_state)
					{
						led2_state = 0;
						ucled &= 0xfd;
						led_renew();
					}
				break;
				default:break;
			}
		break;
		case 4:
			if(!lcd_view)
			{
				// 商品购买界面
				ucled |= 0x01;
				led_renew();
				__HAL_TIM_SetCounter(&htim6, 0);
				__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 3000);
				HAL_TIM_Base_Start_IT(&htim6);
				printf("X:%d,Y:%d,Z:%.1f", x_shop, y_shop, (x_shop*x_value + y_shop*y_value));
				x_store -= x_shop;
				y_store -= y_shop;
				write_eeprom(0);
				HAL_Delay(5);
				write_eeprom(1);
				if(!led2_state && x_store == 0 && y_store == 0)
				{
					led2_state = 1;
					ucled |= 0x02;
					led2_count = 0;
					led_renew();
				}					
				x_shop = y_shop = 0;
			}
		break;
		default:break;
	}
	
}