#include "adcapp.h"

uint32_t adc_buffer[30] = {0};
float adc_value = 0.0f;
float last_adc_value = 0.0f;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc2, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc2, adc_buffer, 30);
	HAL_Delay(5);
	last_adc_value = adc_value = adc_buffer[0] * 3.3f / 4096.0f;
}

void adc_proc(void)
{
	float temp = 0.0f;
	for(int i = 0; i < 30; i += 3)
	{
		temp += adc_buffer[i];
	}
	adc_value = temp * 3.3f / 40960.0f;
	if(last_adc_value <= th_temper_real[1] && adc_value > th_temper_real[1])
	{
		state = 1;
		ucled |= 0x01;
		led_renew();
		time_start = uwTick;
	}
	else if(state && last_adc_value <= th_temper_real[0] && adc_value > th_temper_real[0])
	{
		state = 0;
		ucled &= 0xfe;
		led_renew();
	}
	last_adc_value = adc_value;
}