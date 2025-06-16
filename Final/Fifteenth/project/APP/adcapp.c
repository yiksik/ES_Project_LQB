#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;
uint8_t adc_level = 0;			// 0~5
uint8_t adc_last_level = 6;	// 0~5, 默认6，第一次检测到才会更新PWM占空比

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
}

void adc_proc(void)
{
	float adc_temp = 0.0f;
	for(int i = 0; i < 30; i += 2)
	{
		adc_temp += adc_buffer[i];
	}
	adc_value = adc_temp * 3.3f / 4096.0f / 15.0f;
	
	// 获取当前adc等级
	adc_level = (int)(adc_value / 0.5f);
	if(adc_level > 5)
		adc_level = 5;
	
	// 如果adc等级发生变化，更新PWM输出情况
	if(adc_last_level != adc_level)
	{
		adc_last_level = adc_level;
		tim16_tim17_pwm_duty_renew();	// 更新占空比
	}
}