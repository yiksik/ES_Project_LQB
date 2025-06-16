#include "timapp.h"

uint32_t tim3_ch2_buffer[10] = {1};
uint32_t freq_pa7 = 0;
uint8_t r_value = 1, k_value = 1;
uint8_t r_value_show = 1, k_value_show = 1;
float v_value = 0.0f;
float mh_buffer = 0.0f, ml_buffer = 0.0f;
uint32_t mh_tick = 0, ml_tick = 0;
uint16_t freq_pa1 = 4000;
uint8_t count_led2 = 0;

void tims_init(void)
{
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_2, tim3_ch2_buffer, 10);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim7);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(!mode)
		{
			// 低频转高频
			freq_pa1 += 160;
			if(freq_pa1 == 8000)
			{
				// 转换完成
				tf_state = 0;
				mode = 1;
				HAL_TIM_Base_Stop_IT(&htim6);
				n_value++;
				ucled &= 0xfd;
				led_renew();
				mh_buffer = 0.0f;
			}
		}
		else
		{
			// 高频转低频
			freq_pa1 -= 160;
			if(freq_pa1 == 4000)
			{
				// 转换完成
				tf_state = 0;
				mode = 0;
				HAL_TIM_Base_Stop_IT(&htim6);
				n_value++;
				ucled &= 0xfd;
				led_renew();
				ml_buffer = 0.0f;
			}
		}
		pa1_freq_renew();
	}
	if(htim->Instance == TIM7)
	{
		if(tf_state)
		{
			if(++count_led2 == 100)
			{
				count_led2 = 0;
				ucled ^= 0x02;
				led_renew();
			}
		}
	}
}

void ic_proc(void)
{
	uint32_t temp = 0.;
	for(int i = 0; i < 10; ++i)
	{
		temp += tim3_ch2_buffer[i];
	}
	freq_pa7 = 50000000 / temp;
	v_value = freq_pa7 * 6.28f * r_value / 100.0f / k_value;
	if(!mode)
	{
		// 低频
		if(fabs(v_value - ml_buffer) > 0.01 * ml_buffer)
		{
			ml_buffer = v_value;
			ml_tick = uwTick;
		}
		else if(uwTick - ml_tick >= 2000)
		{
			// 速度稳定超过两秒
			if(ml_buffer > ml_value)
			{
				ml_value = ml_buffer;
			}
		}
	}
	else
	{
		// 高频
		if(fabs(v_value - mh_buffer) > 0.01 * ml_buffer)
		{
			mh_buffer = v_value;
			mh_tick = uwTick;
		}
		else if(uwTick - mh_tick >= 2000)
		{
			// 速度稳定超过两秒
			if(mh_buffer > mh_value)
			{
				mh_value = mh_buffer;
			}
		}
	}
}

void pa1_duty_renew(void)
{
	static float last_duty = 10.0f;
	if(fabs(last_duty - duty_value) > 0.005)
	{
		last_duty = duty_value;
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, duty_value * 100);
	}
}

void pa1_freq_renew(void)
{
	// 80 000 000 / 100 / freq - 1
	__HAL_TIM_SET_PRESCALER(&htim2, 800000 / freq_pa1 - 1);
}