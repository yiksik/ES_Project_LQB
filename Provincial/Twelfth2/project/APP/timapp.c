#include "timapp.h"

uint32_t ic_buffer[10] = {1};
uint32_t freq_pa1 = 0;
float duty_pa7 = 0.0f;
uint32_t freq_pa7 = 0;
uint8_t led4_state = 0;

void tims_init(void)
{
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, ic_buffer, 10);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
}

void ic_proc(void)
{
	float ic_temp = 0.0f;
	for(int i = 0; i < 10; ++i)
	{
		ic_temp += ic_buffer[i];
	}
	freq_pa1 = (uint32_t)(10000000.0 / ic_temp);
	freq_pa7 = freq_pa1 / r_value;
	pa7_freq_renew();
	
	if((freq_pa1 < 1000 || freq_pa1 >= 5000) && led4_state)
	{
		led4_state = 0;
		ucled &= 0xf7;
		led_renew();
	}
	else if((freq_pa1 >= 1000 && freq_pa1 < 5000) && !led4_state)
	{
		led4_state = 1;
		ucled |= 0x08;
		led_renew();
	}
}

void pa7_freq_renew(void)
{
	// 80 000 000 / 800 / freq - 1
	__HAL_TIM_SET_PRESCALER(&htim17, 100000 / freq_pa7 - 1);
}

void pa7_duty_renew(void)
{
	static float last_duty_pa7 = 0.0f;
	if(fabs(last_duty_pa7 - duty_pa7) > 0.001f)
	{
		last_duty_pa7 = freq_pa7;
		__HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, duty_pa7 * 800);
	}
}