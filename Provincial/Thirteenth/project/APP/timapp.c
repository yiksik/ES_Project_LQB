#include "timapp.h"

uint32_t led2_count = 0;

//uint32_t ic_rising_buffer[10] = {1}, ic_falling_buffer[10];
//float duty, freq = 0.0f;

void tims_init(void)
{
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim7);
	
//	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_2, ic_rising_buffer, 10);
//	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_1, ic_falling_buffer, 10);
}

//void ic_proc(void)
//{
//	float temp1 = 0.0f, temp2 = 0.0f;
//	for(int i = 0; i < 10; ++i)
//	{
//		temp1 += ic_rising_buffer[i];
//		temp2 += ic_falling_buffer[i];
//	}
//	duty = temp2 / temp1;
//	freq = 10000000.0f / temp1;
//}

void pwm_switch(void)
{
	if(lcd_view)
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 1000);
		__HAL_TIM_SET_PRESCALER(&htim2, 3);
	}
	else
	{
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 5000);
		__HAL_TIM_SET_PRESCALER(&htim2, 7);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		HAL_TIM_Base_Stop_IT(&htim6);
		lcd_view = 0;
		b1_num = b2_num = b3_num = b1_down = b2_down = b3_down = ans_wrong = 0;
		pwm_switch();
		ucled &= 0xfe;
		led_renew();
	}
	if(htim->Instance == TIM7)
	{
		if(led2_state)
		{
			led2_count++;
			if(led2_count >= 5000)
			{
				led2_state = 0;
				led2_count = 0;
				ucled &= 0xfd;
				led_renew();
			}
			else if(led2_count % 100 == 0)
			{
				ucled ^= 0x02;
				led_renew();
			}
		}
	}
}