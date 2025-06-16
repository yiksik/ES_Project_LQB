#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
}

void adc_proc(void)
{
	float adc_temp = 0.0f;
	for(int i = 0; i < 30; i += 3)
	{
		adc_temp += adc_buffer[i];
	}
	adc_value = adc_temp * 3.3f/ 40960.0f;
	
	if(adc_value > temper_th[0] && status_value != 0)
	{
		status_value = 0;
		// 上限
		led_count = 0;
		ucled = (0x01 << led_pos[0]);
		led_renew();
	}
	else if(adc_value < temper_th[1] && status_value != 2)
	{
		status_value = 2;
		// 下限
		led_count = 0;
		ucled = (0x01 << led_pos[1]);
		led_renew();
	}
	else if(adc_value <= temper_th[0] && adc_value >= temper_th[1] && status_value != 1)
	{
		status_value = 1;
		ucled = 0;
		led_renew();
	}
}