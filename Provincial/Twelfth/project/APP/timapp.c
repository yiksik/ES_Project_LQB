#include "timapp.h"

//uint32_t rising_buffer[10] = {1};
//uint32_t fall_buffer[10] = {0};
//float duty = 0.0f, freq = 0.0f;

void tims_init(void)
{
	HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	
//	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, rising_buffer, 10);
//	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, fall_buffer, 10);
}

void tim17_switch(void)
{
	static uint8_t state = 0;
	state ^=1;
	if(state)
	{
		HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	}
	else
	{
		HAL_TIM_PWM_Stop(&htim17, TIM_CHANNEL_1);
	}
	ucled ^= 0x02;
	led_renew();
}

//void ic_proc(void)
//{
//	float temp1 = 0.0f, temp2 = 0.0f;
//	for(int i = 0; i < 10; ++i)
//	{
//		temp1 += rising_buffer[i];
//		temp2 += fall_buffer[i];
//	}
//	duty = temp2 / temp1;
//	freq = 10000000.0 / temp1;
//}