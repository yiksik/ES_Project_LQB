#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;
uint8_t duty1 = 0, duty2 = 0;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
}

void adc_proc(void)
{
	float temp = 0.0f;
	for(int i = 0; i < 30; i += 3)
	{
		temp += adc_buffer[i];
	}
	adc_value = temp * 3.3f / 40960.0f;
	duty1 = adc_value * 100 / 3.3f;
	duty2 = 100 - duty1;
	tim_duty_renew();
}