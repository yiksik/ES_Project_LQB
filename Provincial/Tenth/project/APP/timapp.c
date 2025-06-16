#include "timapp.h"

uint8_t led_count = 0;

void tims_init(void)
{
	__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
	HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		if(++led_count == 200)
		{
			led_count = 0;
			if(status_value == 0)
			{
				// 上限指示灯闪烁
				ucled ^= (0x01 << led_pos[0]);
				led_renew();
			}
			else if(status_value == 2)
			{
				// 下限指示灯闪烁
				ucled ^= (0x01 << led_pos[1]);
				led_renew();
			}
		}
	}
}