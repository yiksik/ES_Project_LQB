#include "uartapp.h"

uint8_t size_rx = 0;

void uart_proc(void)
{
	if(!size_rx) return;
	if(size_rx == 1 && uart_rx_buffer[0] == '?')
	{
		printf("X:%.1f,Y:%.1f", x_value, y_value);
	}
	
	size_rx = 0;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_buffer, sizeof(uart_rx_buffer));
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}