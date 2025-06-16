#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;
uint8_t output_mode = 0;
uint8_t key4down = 0;
uint32_t key4tick = 0;
float adc_pa4_buffer[100] = {0} , adc_pa5_buffer[100] = {0};
uint8_t adc_pa4_start = 0, adc_pa5_start = 0, adc_pa4_end = 1, adc_pa5_end = 1;
uint8_t led3_state = 0;
uint8_t led3_count = 0;

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
			if(++lcd_view == 3)
				lcd_view = 0;
			if(lcd_view == 2)
			{
				channel = 0;
			}
		break;
		case 0x02:
			if(lcd_view == 1)
			{
				// 参数界面下
				if(++x_value == 5)
					x_value = 1;
//				write_eeprom();
			}
		break;
		case 0x04:
			if(lcd_view == 1)
			{
				// 参数界面下
				if(++y_value == 5)
					y_value = 1;
//				write_eeprom();
			}
		break;
		case 0x08:
			if(!lcd_view)
			{
				// 数据界面下
				adc_pa4_real = adc_pa4;		// 电压测量
				adc_pa5_real = adc_pa5;
				if(adc_pa4_real > adc_pa5_real * y_value && !led3_state)
				{
					led3_count = 0;
					ucled |= 0x04;
					led_renew();
					led3_state = 1;
				}
				else if(adc_pa4_real <= adc_pa5_real * y_value && led3_state)
				{
					ucled &= 0xfb;
					led_renew();
					led3_state = 0;
				}
				adc_pa4_buffer[adc_pa4_end] = adc_pa4_real;
				adc_pa5_buffer[adc_pa5_end] = adc_pa5_real;
				adc_pa4_end = (adc_pa4_end+1) % 100;
				adc_pa5_end = (adc_pa5_end+1) % 100;
				if(n_value[0])
				{
					if(adc_pa4_real > a_value[0])
						a_value[0] = adc_pa4_real;
					if(adc_pa4_real < t_value[0])
						t_value[0] = adc_pa4_real;
					h_value[0] = (n_value[0] * h_value[0] + adc_pa4_real) / (n_value[0] + 1);
				}
				else
				{
					a_value[0] = h_value[0] = t_value[0] = adc_pa4_real;
				}
				if(n_value[1])
				{
					if(adc_pa5_real > a_value[1])
							a_value[1] = adc_pa5_real;
					if(adc_pa5_real < t_value[1])
							t_value[1] = adc_pa5_real;
					h_value[1] = (n_value[1] * h_value[1] + adc_pa5_real) / (n_value[1] + 1);
				}
				else
				{
					a_value[1] = h_value[1] = t_value[1] = adc_pa5_real;
				}
				n_value[0]++;
				n_value[1]++;
			}
			else if(lcd_view == 1)
			{
				output_mode ^= 1;
				
				if(!output_mode)
				{
					freq_pa7 = freq_pa1 * 1.0f * x_value;
					ucled |= 0x01;
					ucled &= 0xfd;
					led_renew();
				}
				else
				{
					freq_pa7 = freq_pa1 * 1.0f / x_value;
					ucled &= 0xfe;
					ucled |= 0x02;
					led_renew();
				}
				freq_pa7_renew();
			}
			else
			{
				if(!key4down)
				{
					key4down = 1;
					key4tick = uwTick;
				}
			}
		break;
		default:break;
	}
	if(key4down)
	{
		if(key_up == 0x08)
		{
			key4down = 0;
			if(uwTick - key4tick < 1000)
			{
				channel ^= 1;
			}
			else
			{
				n_value[channel] = a_value[channel] = h_value[channel] = t_value[channel] = 0;
				// 4t测评条件好像错了
				if(!channel)
				{
					adc_pa4_end = 1;
					adc_pa4_start = 0;
				}
				else
				{
					adc_pa5_end = 1;
					adc_pa5_start = 0;
				} 
			}
		}
	}
}