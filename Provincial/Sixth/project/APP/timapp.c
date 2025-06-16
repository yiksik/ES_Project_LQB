#include "timapp.h"

uint8_t led1_count = 0;
uint8_t led1_switch = 1;
uint8_t key_count = 0;

void tims_init(void)
{
	HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(led1_switch && led1_state)
		{
			if(++led1_count == 100)
			{
				led1_count = 0;
				ucled ^= 0x01;
				led_renew();
			}
		}
		if(++key_count == 10)
		{
			key_count = 0;
			key_proc();
		}
	}
}