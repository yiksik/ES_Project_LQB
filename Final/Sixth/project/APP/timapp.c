#include "timapp.h"

void tims_init(void)
{
	// 题目是使用TIM1控制PA9和PB14互补输出PWM
	// 但是新板子PA9没有引出不方便测量
	// 使用TIM15控制PA1（补）和PA2来代替
	
//	HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
//	HAL_TIMEx_PWMN_Start(&htim15, TIM_CHANNEL_1);
}

void tim_switch(void)
{
	if(state_output)
	{
		HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Start(&htim15, TIM_CHANNEL_1);
	}
	else
	{
		HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_1);
		HAL_TIMEx_PWMN_Stop(&htim15, TIM_CHANNEL_1);
	}
}

void tim_duty_renew(void)
{
	static uint8_t duty_last;
	if(duty_last == duty1)
		return;
	duty_last = duty1;
	__HAL_TIM_SetCompare(&htim15, TIM_CHANNEL_1, duty_last);		//更新占空比
}

void tim_freq_renew(void)
{
	// freq 是频率
	// 80 000 000 / 100 / freq - 1是预分频 
	__HAL_TIM_SET_PRESCALER(&htim15, 800000 / freq - 1);
}