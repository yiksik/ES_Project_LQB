#include "adcapp.h"

uint32_t adc_buffer[10] = {0};
float adc_value = 0.0f;
uint8_t led3_state = 0;

void adc_init(void)
{
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(&hadc1, adc_buffer, 10);
}

void adc_proc(void)
{
	float temp = 0.0f;
	for(int i = 0; i < 10; ++i)
	{
		temp += adc_buffer[i];
	}
	adc_value = temp * 0.33f / 4096.0f;
	
	if(!led3_state && (adc_value <= pd_value || adc_value >= pu_value))
	{
		led3_state = 1;
		ucled |= 0x04;
		led_renew();
	}
	else if(led3_state && (adc_value > pd_value && adc_value < pu_value))
	{
		led3_state = 0;
		ucled &= 0xfb;
		led_renew();
	}
	
	if(lock) return;
	duty_pa1 = adc_value * 100 / 3.3f;
	duty_pa2 = 100 - duty_pa1;
	
	add_reset2 = add_set1 = duty_pa1 * add_all / 100;
	add_set2 = add_reset1 = add_all - add_set1;
	
}