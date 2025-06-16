#include "timapp.h"

uint8_t led2_state = 0;
uint8_t led2_count = 0;

void tims_init(void)
{
	__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
	__HAL_TIM_CLEAR_IT(&htim7, TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim7);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		HAL_TIM_Base_Stop_IT(&htim6);
		__HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 500);
		ucled &= 0xfe;
		led_renew();
	}
	if(htim->Instance == TIM7)
	{
		if(led2_state)
		{
			if(++led2_count == 100)
			{
				led2_count = 0;
				ucled ^= 0x02;
				led_renew();
			}
		}
	}
}