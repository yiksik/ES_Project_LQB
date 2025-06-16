#include "uartapp.h"

uint16_t uart_buffer_size = 0;

void uart_proc(void)
{
	if(!uart_buffer_size) return;

	// 串口处理逻辑
	// 设置场景
	if(uart_buffer_size == 3 && uart_rx_buffer[0] == '[' && uart_rx_buffer[2] == ']' && uart_rx_buffer[1] >= '1' && uart_rx_buffer[1] <= '4')
	{
		if(device_state != 2)
		{
			printf("Device offline");
		}
		else
		{
			printf("Got it");
			uint8_t temp = uart_rx_buffer[1] - '0';
			if(temp != scene_current)
			{
				// 场景变化，更新输出脉冲频率
				scene_current = temp;
				ucled &= 0x0f;	// 高八位熄灭
				ucled |= (0x08 << scene_current);		//点亮对应led
				led_renew();
				tim16_tim17_pwm_freq_renew();
			}
		}
	}
	// 查询设备状态
	else if(uart_buffer_size == 1 && uart_rx_buffer[0] == '?')
	{
		switch(device_state)
		{
			case 0:
				printf("Idle");
			break;
			case 1:
				printf("Wait");
			break;
			case 2:
				printf("Busy");
			break;
			default:break;
		}
	}
	// 查询设备位置
	else if(uart_buffer_size == 1 && uart_rx_buffer[0] == '#')
	{
		printf("(%d,%d)", (uint16_t)points_buffer[point_start].x, (uint16_t)points_buffer[point_start].y);
	}
	else if(uart_buffer_size >= 5 && uart_buffer_size <= 9 && uart_rx_buffer[0] == '{' && uart_rx_buffer[uart_buffer_size-1] == '}')
	{
		int temp_x = 0;
		int temp_y = 0;
		int temp = 0;
		uint8_t flag = 0;
		for(int i = 1; ;i++)
		{
			if(uart_rx_buffer[i] == ',')
			{
				temp_x = temp;
				temp = 0;
			}
			else if(uart_rx_buffer[i] == '}')
			{
				temp_y = temp;
				break;
			}
			else
			{
				temp = temp * 10 + (uart_rx_buffer[i] - '0');
			}
		}
		// 遍历整个队列
		for(int i = point_start + 1; i != point_end;)
		{
			if(points_buffer[i].x == temp_x && points_buffer[i].y == temp_y)
			{
				// 需要删除
				for(int j = i; j != point_end; j = (j+1)%100)
				{
					points_buffer[j] = points_buffer[j+1];
				}
				point_end = (point_end + 99) % 100;
				if(device_state == 2 && point_end == (point_start+1)%100)
				{
					// 运行中，但没有目标点了
					device_state = 0;
					v_value_real = 0;
				}
				flag = 1;
			}
			else
			{
				 i = (i+1)%100;
			}
		}
		if(flag)
		{
			printf("Got it");
		}
		else
		{
			printf("Nonexistent");
		}
	}
	else if(uart_buffer_size > 4 && uart_rx_buffer[0] == '(' && uart_rx_buffer[uart_buffer_size-1] == ')')
	{
		// 长指令，且首尾是 ( 和 )
		if(device_state != 0)
		{
			printf("Busy");
		}
		else
		{
			printf("Got it");
			uint8_t flag_xy = 0;	// 区分x坐标还是y坐标
			uint16_t temp_xy = 0;	// 坐标中间量
			for(int i = 1; ; ++i)
			{
				// 遍历坐标列表
				if(uart_rx_buffer[i] == ',' || uart_rx_buffer[i] == ')')
				{
					// 一个坐标结束
					if(!flag_xy)
					{
						// 存储为x坐标
						points_buffer[point_end].x = temp_xy;
					}
					else
					{
						points_buffer[point_end].y = temp_xy;
						// 尾指针后移动
						point_end = (point_end + 1) % 100;
					}
					flag_xy ^= 1;
					temp_xy = 0;
					if(uart_rx_buffer[i] == ')')
						break;
				}
				else
				{
					temp_xy = temp_xy * 10 + (uart_rx_buffer[i] - '0');
				}
			}
		}
	}
	else
	{
		// 无效指令
		printf("Error");
	}
	// 复位中断
	memset(uart_rx_buffer, 0, uart_buffer_size);
	uart_buffer_size = 0;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_buffer, sizeof(uart_rx_buffer));
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}