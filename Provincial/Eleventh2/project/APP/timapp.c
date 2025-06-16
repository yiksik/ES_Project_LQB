#include "timapp.h"

float duty_pa6 = 0.1f, duty_pa7 = 0.1f;
uint8_t duty_pa6_set = 10, duty_pa7_set = 10;
uint32_t tim2_buffer[10] = {0};
uint32_t tim3_buffer[10] = {0};
uint32_t tim2_fall_buffer[10] = {0};
uint32_t tim3_fall_buffer[10] = {0};
float pa6_duty = 0.0f, pa7_duty = 0.0f;

void tims_init(void)
{
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);
	
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_2, tim2_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, tim2_fall_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_2, tim3_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_1, tim3_fall_buffer, 10);
}

void pa6_duty_renew(void)
{
	static float duty_pa6_last = 0.0f;
	if(fabs(duty_pa6 - duty_pa6_last) > 0.01f)
	{
		duty_pa6_last = duty_pa6;
		__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, duty_pa6 * 10000);
	}
}

void pa7_duty_renew(void)
{
	static float duty_pa7_last = 0.0f;
	if(fabs(duty_pa7 - duty_pa7_last) > 0.01f)
	{
		duty_pa7_last = duty_pa7;
		__HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, duty_pa7 * 10000);
	}		
}

void ic_proc(void)
{
	float temp1 = 0.0f, temp2 = 0.0f, temp3 = 0.0f, temp4 = 0.0f;
	for(int i = 0; i < 10; ++i)
	{
		temp1 += tim2_buffer[i];
		temp2 += tim2_fall_buffer[i];
		temp3 += tim3_buffer[i];
		temp4 += tim3_fall_buffer[i];
	}
	pa6_duty = temp2  * 100 / temp1;
	pa7_duty = temp4  * 100 / temp3;
}