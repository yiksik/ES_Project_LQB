#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;
float duty_value = 0.0f;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
}

void adc_proc(void)
{
	if(duty_lock) return;
	float temp = 0.0f;
	for(int i = 0; i < 30; i += 3)
	{
		temp += adc_buffer[i];
	}
	adc_value = temp * 3.3f / 40960.0f;
	if(adc_value <= 1.0f)
		duty_value = 0.1;
	else if(adc_value >= 3.0f)
		duty_value = 0.85;
	else
		duty_value = 0.375f * (adc_value - 1) + 0.1f;
	
	pa1_duty_renew();
}