#include "uartapp.h"

void uart_proc(void)
{
	if(!uart_buffer_size) return;
	if(uart_buffer_size == 1 && uart_buffer[0] == 'C')
	{
		printf("%02d%02d%02d: %dC, %d%%\r\n", sTime.Hours, sTime.Minutes, sTime.Seconds, th_temper, th_wet);
	}
	else if(uart_buffer_size == 1 && uart_buffer[0] == 'T')
	{
		if(record_times >= 60)
		{
			// 记录超过60组, 按时间先后发, 只发60组
			int j = 0;
			for(int i = record_index; i < 60; ++i, ++j)
				printf("(%d)%02d%02d%02d: %dC, %d%%\r\n", j+1, record_arr[i].hour, record_arr[i].min, record_arr[i].sec, record_arr[i].temper, record_arr[i].wet);
			for(int i = 0; i < record_index && j < 60; ++i, ++j)
				printf("(%d)%02d%02d%02d: %dC, %d%%\r\n", j+1, record_arr[i].hour, record_arr[i].min, record_arr[i].sec, record_arr[i].temper, record_arr[i].wet);
		}
		else
		{
			// 未记录超过60组，直接发到record_index前一个
			int j = 0;
			for(int i = 0; i < record_index; ++i, ++j)
				printf("(%d)%02d%02d%02d: %dC, %d%%\r\n", j+1, record_arr[i].hour, record_arr[i].min, record_arr[i].sec, record_arr[i].temper, record_arr[i].wet);
		}
	}
	uart_buffer_size = 0;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_buffer, sizeof(uart_buffer));
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}