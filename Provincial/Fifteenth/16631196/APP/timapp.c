#include "timapp.h"

uint32_t tim2_buffer[10] = {1};
uint32_t tim3_buffer[10] = {1};
float freq_pa = 0.0f, freq_pb = 0.0f;
float period_pa_us = 0.0f, period_pb_us = 0.0f;
float last_freq_pa = 20000.0f, last_freq_pb = 20000.0f;
float freq_pa_buffer[60] = {0.0f}, freq_pb_buffer[60] = {0.0f};
uint8_t index_pa = 0, index_pb = 0;
uint8_t led2_state = 0, led3_state = 0;
uint8_t led8_state = 0;

void tims_init(void)
{
	HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, tim2_buffer, 10);
	HAL_TIM_IC_Start_DMA(&htim3, TIM_CHANNEL_1, tim3_buffer, 10);
}

void ic_proc(void)
{
	uint32_t temp1 = 0, temp2 = 0;
	for(int i = 0; i < 10; ++i)
	{
		temp1 += tim2_buffer[i];
		temp2 += tim3_buffer[i];
	}
	freq_pa = 50000000 / temp1;
	freq_pb = 50000000 / temp2;
	freq_pa += px_value;
	freq_pb += px_value;
	period_pa_us = 1000000 / freq_pa;
	period_pb_us = 1000000 / freq_pb;
	if(last_freq_pa < ph_value && freq_pa > ph_value)
	{
		nha_value++;
	}
	if(last_freq_pb < ph_value && freq_pb > ph_value)
	{
		nhb_value++;
	}
	
	freq_pa_buffer[index_pa++] = freq_pa;
	freq_pb_buffer[index_pb++] = freq_pb;
	if(index_pa == 30)
	{
		index_pa = index_pb = 0;
		float max_a = 0.0f;
		float max_b = 0.0f;
		float min_a = 20000.0f;
		float min_b = 20000.0f;
		for(int i = 0; i < 30; ++i)
		{
			if(max_a < freq_pa_buffer[i])
				max_a = freq_pa_buffer[i];
			else if(min_a > freq_pa_buffer[i] && freq_pa_buffer[i] > 0)
				min_a = freq_pa_buffer[i];
			if(max_b < freq_pb_buffer[i])
				max_b = freq_pb_buffer[i];
			else if(min_b > freq_pb_buffer[i] && freq_pb_buffer[i] > 0)
				min_b = freq_pb_buffer[i];
		}
		if(max_a - min_a >= pd_value)
		{
			nda_value++;
		}
		if(max_b - min_b >= pd_value)
		{
			ndb_value++;
		}
	}
	if(freq_pa > ph_value && !led2_state)
	{
		led2_state = 1;
		ucled |= 0x02;
		led_renew();
	}
	else if(freq_pa < ph_value && led2_state)
	{
		led2_state = 0;
		ucled &= 0xfd;
		led_renew();
	}
	if(freq_pb > ph_value && !led3_state)
	{
		led3_state = 1;
		ucled |= 0x04;
		led_renew();
	}
	else if(freq_pb < ph_value && led3_state)
	{
		led3_state = 0;
		ucled &= 0xfb;
		led_renew();
	}
	if(!led8_state && (nda_value >= 3 || ndb_value >= 3))
	{
		led8_state = 1;
		ucled |= 0x80;
		led_renew();
	}
	last_freq_pa = freq_pa;
	last_freq_pb = freq_pb;
}