#include "timapp.h"

uint32_t tim2_ch1_buffer[10] = {0};
uint32_t pa15_freq = 0;
float v_value = 0.0f;
float v_value_real = 0.0f;
float r_value = 1.0f;
uint8_t b_value = 10;
uint8_t device_state = 0;	//设备状态：0-空闲；1-等待；2-运行
uint8_t scene_current = 0;	//当前场景，正常：1~4
uint8_t move_count = 0;
uint8_t led_count = 0;


void tims_init(void)
{
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, tim2_ch1_buffer, 10);
	HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		// 定时器6：1ms中断
		if(device_state == 1)
		{
			if(++led_count == 200)
			{
				led_count = 0;
				ucled ^= 1;
				led_renew();
			}
		}
		else if(device_state == 2)
		{
			// 运行状态
			if(++move_count == 50)
			{
				// 0.05s更新一次坐标
				move_count = 0;
				tt_value++;
				// points_buffer[point_start]是当前坐标
				// points_buffer[(point_start+1)%100]是下一个坐标
				float move_dis = 0.05 * v_value_real;
				float dx = points_buffer[(point_start+1)%100].x - points_buffer[point_start].x;
				float dy = points_buffer[(point_start+1)%100].y - points_buffer[point_start].y;
				float distance = sqrt(dx * dx + dy * dy);
				if(distance > move_dis)
				{
					// 0.05s到不了下一个点，小挪一下
					// dy = points_buffer[(point_start+1)%100].y - points_buffer[point_start].y
					// dx = points_buffer[(point_start+1)%100].x - points_buffer[point_start].x
					points_buffer[point_start].x = move_dis * dx / distance + points_buffer[point_start].x;
					points_buffer[point_start].y = move_dis * dy / distance + points_buffer[point_start].y;
					ts_value += move_dis;
				}
				else
				{
					ts_value += distance;
					point_start = (point_start+1)%100; // 直接到达下一个点
					if(point_end == (point_start+1)%100)
					{
						// 抵达最后一个了
						device_state = 0;								// 空闲状态
						ucled &= 0xfe;
						led_renew();
						v_value_real = 0;
					}
				}
			}
		}
	}
}

void tim2_proc(void)
{
	float tim2_ch1_temp = 0.0f;
	for(int i = 0; i < 10; ++i)
	{
		tim2_ch1_temp += tim2_ch1_buffer[i];
	}
	pa15_freq = (uint32_t)(100000000.0 / tim2_ch1_temp);
	v_value = (uint32_t)(31.4f * r_value * pa15_freq / 100.0f + b_value * 10) / 10.0f;
	if(device_state == 2)
	{
		// 运行状态下
		v_value_real = v_value;
	}
}

void tim16_tim17_pwm_duty_renew(void)
{
	switch(adc_level)
	{
		case 0:
			__HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 1000);
			__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 500);
		break;
		case 1:
			__HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 3000);
			__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 2500);
		break;
		case 2:
			__HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 5000);
			__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 4500);
		break;
		case 3:
			__HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 7000);
			__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 6500);
		break;
		case 4:
			__HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 9000);
			__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 8500);
		break;
		case 5:
			__HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 9500);
			__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 9000);
		break;
		default:break;
	}
}

void tim16_tim17_pwm_freq_renew(void)
{
	switch(scene_current)
	{
		case 1:
			__HAL_TIM_SET_PRESCALER(&htim16, 7);
			__HAL_TIM_SET_PRESCALER(&htim17, 7);
		break;
		case 2:
			__HAL_TIM_SET_PRESCALER(&htim16, 1);
			__HAL_TIM_SET_PRESCALER(&htim17, 7);
		break;
		case 3:
			__HAL_TIM_SET_PRESCALER(&htim16, 7);
			__HAL_TIM_SET_PRESCALER(&htim17, 1);
		break;
		case 4:
			__HAL_TIM_SET_PRESCALER(&htim16, 1);
			__HAL_TIM_SET_PRESCALER(&htim17, 1);
		break;
		default:break;
	}
}

void tim16_tim17_pwm_switch(void)
{
	if(device_state == 2)
	{
		// 运行状态下
		HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	}
	else
	{
		// 其他状态下，保持低电平
		HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
		HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	}
}