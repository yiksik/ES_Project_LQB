#include "timapp.h"

uint8_t led2_state = 0;
uint8_t led3_state = 0;
uint16_t led2_count = 0;
uint16_t led3_count = 0;

void tims_init(void)
{
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_Base_Start_IT(&htim7);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		// 定时器6：1s定时
		adc_proc();
		ucled ^= 0x01;
		led_renew();
	}
	if(htim->Instance == TIM7)
	{
		// 定时器7：1ms定时
		if(led2_state)
		{
			led2_count++;
			if(led2_count % 200 == 0)
			{
				ucled ^= 0x02;
				led_renew();
			}
			if(led2_count == 1800)
			{
				led2_count = 0;
				led2_state = 0;
			}
		}
		if(led3_state)
		{
			led3_count++;
			if(led3_count % 200 == 0)
			{
				ucled ^= 0x04;
				led_renew();
			}
			if(led3_count == 1800)
			{
				led3_count = 0;
				led3_state = 0;
			}
		}
	}
}