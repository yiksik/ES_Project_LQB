#include "timapp.h"

uint32_t add_all = 5000, add_set1 = 2500, add_reset1 = 2500, add_set2 = 2500, add_reset2 = 2500;
uint16_t capture = 0;

void tims_init(void)
{
////	add_all = 5000;
	__HAL_TIM_CLEAR_IT(&htim6, TIM_IT_UPDATE);
	HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_2);
	HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_3);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM6)
	{
		error = 0;
		HAL_TIM_Base_Stop_IT(&htim6);
		// 参数恢复
		para_show[0] = pu_value;
		para_show[1] = pd_value;
	}
}

void pwm_freq_renew(void)
{
	if(mode)
	{
		add_all = 500;
	}
	else
	{
		add_all = 5000;
	}
	add_reset2 = add_set1 = duty_pa1 * add_all / 100;
	add_set2 = add_reset1 = add_all - add_set1;
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2)
	{
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			capture = __HAL_TIM_GetCompare(&htim2, TIM_CHANNEL_2);
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == GPIO_PIN_SET)
			{
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, capture + add_set1);
			}
			else
			{
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, capture + add_reset1);
			}
			HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_2);
		}
		else
		{
			capture = __HAL_TIM_GetCompare(&htim2, TIM_CHANNEL_3);
			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_SET)
			{
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, capture + add_set2);
			}
			else
			{
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, capture + add_reset2);
			}
			HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_3);
		}
	}
}