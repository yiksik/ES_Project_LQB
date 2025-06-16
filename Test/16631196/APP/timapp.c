#include "timapp.h"

uint32_t ic_ch1_buffer[2] = {0};
//uint32_t ic_ch1_buffer = 0;
uint32_t ic_ch2_buffer[2] = {0};
uint32_t ic_ch3_buffer[2] = {0};
uint32_t ic_ch4_buffer[2] = {0};
uint32_t freq_pa5_ch1 = 0, freq_pa1_ch2 = 0, freq_pa2_ch3 = 0, freq_pa3_ch4 = 0;
float duty_pa1 = 0.0f, duty_pa2 = 0.0f;

void tims_init(void)
{
//	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, ic_ch2_buffer, 2);
}

void ic_proc(void)
{
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, ic_ch1_buffer, 2);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, ic_ch2_buffer, 2);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_3, ic_ch3_buffer, 2);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_4, ic_ch4_buffer, 2);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	switch(htim->Channel)
	{
		case HAL_TIM_ACTIVE_CHANNEL_1:
//			freq_pa5_ch1 = 1000000 / ((ic_ch1_buffer[1] + 65535 - ic_ch1_buffer[0]) % 65535);
		break;
		case HAL_TIM_ACTIVE_CHANNEL_2:
			freq_pa1_ch2 = 1000000 / ((ic_ch2_buffer[1] + 65535 - ic_ch2_buffer[0]) % 65535);
			float temp1 = ((ic_ch2_buffer[1] + 65535 - ic_ch2_buffer[0]) % 65535);
			float temp2 = ((ic_ch1_buffer[0] + 65535 - ic_ch2_buffer[0]) % 65535);
			if(temp2 / temp1 < 1.01f)
				duty_pa1 = temp2 * 100.0f / temp1;
			else
				duty_pa1 = ((ic_ch1_buffer[1] + 65535 - ic_ch2_buffer[0]) % 65535) * 100.0f / temp1;
		break;
		case HAL_TIM_ACTIVE_CHANNEL_3:
			freq_pa2_ch3 = 1000000 / ((ic_ch3_buffer[1] + 65535 - ic_ch3_buffer[0]) % 65535);
			float temp3 = ((ic_ch3_buffer[1] + 65535 - ic_ch3_buffer[0]) % 65535);
			float temp4 = ((ic_ch4_buffer[0] + 65535 - ic_ch3_buffer[0]) % 65535);
			if(temp4 / temp3 < 1.01f)
				duty_pa2 = temp4 * 100.0f / temp3;
			else
				duty_pa2 = ((ic_ch4_buffer[1] + 65535 - ic_ch3_buffer[0]) % 65535) * 100.0f / temp3;
		break;
		case HAL_TIM_ACTIVE_CHANNEL_4:
//			freq_pa3_ch4 = 1000000 / ((ic_ch4_buffer[1] + 65535 - ic_ch4_buffer[0]) % 65535);
		break;
		default:break;
	}
}