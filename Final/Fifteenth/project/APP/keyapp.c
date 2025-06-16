#include "keyapp.h"

uint8_t key_old = 0, key_val, key_down, key_up;
uint8_t set_obj = 0; // 设置对象：0-R；1-B；
float ts_value = 0.0f;
uint32_t tt_value = 0;
uint8_t b3_b4_down = 0;
uint32_t b3_b4_tick = 0;

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
			switch(device_state)
			{
				case 0:
					// 空闲状态按下B1
					if(point_end != (point_start+1)%100 )
					{
						// 存在目标点
						device_state = 2;	//切换到运行状态
						ucled |= 0x01;
						led_renew();
						tim16_tim17_pwm_switch();
						v_value_real = v_value;
					}
				break;
				case 1:
					// 等待状态按下B1
					device_state = 2;		//切换到运行状态
					ucled |= 0x01;
					led_renew();
					tim16_tim17_pwm_switch();
					v_value_real = v_value;
				break;
				case 2:
					// 运行状态按下B1
					ucled |= 0x01;
					led_renew();
					led_count = 0;
					device_state = 1;		//切换到等待状态
					tim16_tim17_pwm_switch();
					v_value_real = 0;
				break;
				default:break;
			}
		break;
		case 0x02:
				lcd_view = (lcd_view + 1) % 3;
				switch(lcd_view)
				{
					case 0:
						lcd_disp(Line1, "        DATA");
						lcd_proc();
					break;
					case 1:
						set_obj = 0;
						lcd_disp(Line1, "        PARA");
						lcd_disp(Line3, "     R=%.1f      ", r_value);
						lcd_disp(Line4, "     B=%d        ", b_value);
						lcd_disp(Line5, "                 ", b_value);
						lcd_disp(Line6, "                 ", b_value);
						lcd_disp(Line7, "                 ", b_value);
					break;
					case 2:
						lcd_disp(Line1, "        RECD");
						lcd_disp(Line3, "     TS=%.1f      ", ts_value);
						lcd_disp(Line4, "     TT=%d        ", tt_value/20);
					break;
					default:break;
				}
		break;
		case 0x04:
				if(lcd_view == 1)
				{
					// 参数界面下
					set_obj ^= 1;
				}
		break;
		case 0x08:
				if(lcd_view == 1)
				{
					// 参数界面下
					if(!set_obj)
					{
						// 设置R参数
						r_value += 0.1;
						if(r_value > 2.05)
							r_value = 1.0;
					}
					else
					{
						// 设置B参数
						b_value += 10;
						if(b_value > 100)
							b_value = 10;
					}
				}
		break;
		default:break;
	}
	if(lcd_view == 0 && device_state == 0)
	{
		if(!b3_b4_down && key_val == 0x0c)
		{
			b3_b4_down = 1;
			b3_b4_tick = uwTick;
		}
		if(b3_b4_down && key_val != 0x0c)
		{
			b3_b4_down = 0;
			if(uwTick - b3_b4_tick >= 2000)
			{
				ts_value = 0;
				tt_value = 0;
			}
		}
	}
}