#include "keyapp.h"

uint8_t key_val, key_old = 0, key_down, key_up;
uint8_t key2down = 0;
uint32_t down_tick = 0, up_tick = 0;
uint8_t set_obj = 0;
uint8_t key3down = 0;
uint8_t key3_long = 0;
uint32_t key3tick = 0;
uint8_t state = 0;	//0-Standby; 1-Running; 2-Setting; 3-Pause
uint32_t run_time = 0;

uint8_t key4down = 0;

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
			if(state == 0 || state == 2)
			{
				store_pos++;
				if(store_pos == 6)
					store_pos = 1;
				times[0] = times[store_pos];
			}
		break;
		case 2:
			if(!key2down)
			{
				down_tick = uwTick;
				key2down = 1;
				__HAL_TIM_SetCounter(&htim6, 0);
				HAL_TIM_Base_Start_IT(&htim6);		// 开中断
			}
		break;
		case 3:
			if(state == 2 && !key3down)
			{
				key3down = 1;
				key3_long = 0;
				key3tick = uwTick;
			}
		break;
		case 4:
			if(!key4down)
			{
				key4down = 1;
				__HAL_TIM_SetCounter(&htim7, 0);
				HAL_TIM_Base_Start_IT(&htim7);
			}
		break;
		default:break;
	}
	if(key2down && key_up == 2)
	{
		// 按下并松手： 短按B2
		key2down = 0;		// 复位标志位
		HAL_TIM_Base_Stop_IT(&htim6);		// 关闭中断
		up_tick = uwTick;
		if(state == 0 || state == 2)
		{
			if(state == 0) state = 2;
			else
			{
				if(++set_obj == 3)
					set_obj = 0;
			}
		}
	}
	if(key3down)
	{
		if(key_up == 3)
		{
			key3down = 0;
			if(key3_long == 0)
			{
				// 短按
				switch(set_obj)
				{
					case 0:
						if(++times[0].hours == 99)
						{
							times[0].hours = 0;
						}
					break;
					case 1:
						if(++times[0].mins == 60)
						{
							times[0].mins = 0;
						}
					break;
					case 2:
						if(++times[0].secs == 60)
						{
							times[0].secs = 0;
						}
					break;
					default:break;
				}
			}
		}
		else if(uwTick - key3tick >= 800)
		{
			if(!key3_long) key3_long = 1;
			switch(set_obj)
			{
				case 0:
					if(++times[0].hours == 99)
					{
						times[0].hours = 0;
					}
				break;
				case 1:
					if(++times[0].mins == 60)
					{
						times[0].mins = 0;
					}
				break;
				case 2:
					if(++times[0].secs == 60)
					{
						times[0].secs = 0;
					}
				break;
				default:break;
			}
		}
	}
	if(key4down && key_up == 4)
	{
		// 按下并松开
		key4down = 0;
		HAL_TIM_Base_Stop_IT(&htim7);
		// 短按
		if((state == 0 || state == 2) && times[0].hours * 3600 + times[0].mins * 60 + times[0].secs != 0)
		{
			state = 1;
			led1_count = 0;
			ucled |= 0x01;
			led_renew();
			HAL_TIM_Base_Start_IT(&htim3);
			pa6_switch();
			run_time = times[0].hours * 3600 + times[0].mins * 60 + times[0].secs;
			__HAL_TIM_SetCounter(&htim4, 0);
			HAL_TIM_Base_Start_IT(&htim4);
		}
		else if(state == 1)
		{
			state = 3;
			HAL_TIM_Base_Stop_IT(&htim3);
			ucled &= 0xfe;
			led_renew();
			pa6_switch();
			HAL_TIM_Base_Stop_IT(&htim4);
		}
		else if(state == 3)
		{
			state = 1;
			led1_count = 0;
			ucled |= 0x01;
			led_renew();
			HAL_TIM_Base_Start_IT(&htim3);
			pa6_switch();
			HAL_TIM_Base_Start_IT(&htim4);
		}
	}
}