#include "timapp.h"

uint32_t tim2_ch1_buffer[10] = {1};
uint32_t tim2_ch2_buffer[10] = {1};
uint32_t tim3_ch1_buffer[10] = {1};
uint32_t tim3_ch2_buffer[10] = {1};
float freq_r40 = 0.0f, duty_r40 = 0.0f, freq_r39 = 0.0f, duty_r39 = 0.0f;

void tims_init(void)
{
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, tim2_ch1_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, tim2_ch2_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_1, tim3_ch1_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_2, tim3_ch2_buffer, 10);
}

void ic_proc(void)
{
	float temp1 = 0.0f, temp2 = 0.0f, temp3 = 0.0f, temp4 = 0.0f;
	for(int i = 0; i < 10; ++i)
	{
		temp1 += tim2_ch1_buffer[i];
		temp2 += tim2_ch2_buffer[i];
		temp3 += tim3_ch1_buffer[i];
		temp4 += tim3_ch2_buffer[i];
	}
	freq_r40 = 50000000.0f / temp1;
	duty_r40 = temp2 / temp1;
	freq_r39 = 50000000.0f / temp3;
	duty_r39 = temp4 / temp3;
}