#include "timapp.h"

uint32_t ic_buffer[10] = {1};
float freq_pa7 = 0.0f;

void tims_init(void)
{
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, ic_buffer, 10);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim6);
	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(led3_state)
		{
			if(++led3_count == 100)
			{
				led3_count = 0;
				ucled ^= 0x04;
				led_renew();
			}
		}
	}
}

void ic_proc(void)
{
	float temp = 0.0f;
	for(int i = 0; i < 10; ++i)
	{
		temp += ic_buffer[i];
	}
	freq_pa1 = 50000000.0f / temp;
	if(!output_mode)
		freq_pa7 = freq_pa1 * 1.0f * x_value;
	else
		freq_pa7 = freq_pa1 * 1.0f / x_value;
	freq_pa7_renew();
}

void freq_pa7_renew(void)
{
	static float last_freq_pa7 = 0.0f;
	if(fabs(last_freq_pa7 - freq_pa7) > 10.0f)
	{
		last_freq_pa7 = freq_pa7;
		__HAL_TIM_SET_PRESCALER(&htim17, 800000.0f / freq_pa7 - 1);
	}
}