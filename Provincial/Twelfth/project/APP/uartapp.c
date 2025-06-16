#include "uartapp.h"

pos_t car_pos[8] = {0};
uint8_t idle_num = 8;
uint8_t cnbr_num = 0;
uint8_t vnbr_num = 0;
//char title_[4];
float cnbr_fee = 3.5f, vnbr_fee = 2.00f;

void uart_proc(void)
{
	if(!uart_buffer_size) return;
//	printf("%d\r\n", uart_buffer_size);
	if(uart_buffer_size == 22)
	{
		// 解析输入
		int state_ = 0;
		if(uart_rx_buffer[0] == 'C')
		{
			state_ = 1;
		}
		else
		{
			state_ = 2;
		}
		char title_[4];
		for(int i = 0; i < 4; ++i)
		{
			title_[i] = uart_rx_buffer[5+i];
		}
		uint32_t hours_ = (
			((uart_rx_buffer[10] - '0') * 10 + uart_rx_buffer[11] - '0') * 8760
		+	((uart_rx_buffer[12] - '0') * 10 + uart_rx_buffer[13] - '0') * 720
		+ ((uart_rx_buffer[14] - '0') * 10 + uart_rx_buffer[15] - '0') * 24
		+ ((uart_rx_buffer[16] - '0') * 10 + uart_rx_buffer[17] - '0')
		);
		
		uint32_t secs_ = (
			((uart_rx_buffer[18] - '0') * 10 + uart_rx_buffer[19] - '0') * 60
		+ ((uart_rx_buffer[20] - '0') * 10 + uart_rx_buffer[21] - '0')
		);
		
		int found = 0;
		// 找一下车库里有没有这个车
		for(int i = 0; i < 8 && !found; ++i)
		{
			if(title_[0] == car_pos[i].title[0]
			&& title_[1] == car_pos[i].title[1] && title_[2] == car_pos[i].title[2] && title_[3] == car_pos[i].title[3]
			)
			{
				// 找到了
				if(state_ == car_pos[i].state)
				{
					found = 1;
					// 类型一样，比较时间早晚
					if(hours_ > car_pos[i].hours || (hours_ == car_pos[i].hours && secs_ > car_pos[i].secs))
					{
						// 出库比入库晚，正常出库
//						printf("out\r\n");
						if(state_ == 1)
						{
							cnbr_num--;
							uint32_t hours_count = (hours_ - car_pos[i].hours) + (secs_ > car_pos[i].secs);
							float fee = hours_count * cnbr_fee;
							printf("CNBR:%c%c%c%c:%d:%.2f", title_[0],title_[1],title_[2],title_[3],hours_count,fee);
						}
						else
						{
							vnbr_num--;
							uint32_t hours_count = (hours_ - car_pos[i].hours) + (secs_ > car_pos[i].secs);
							float fee = hours_count * vnbr_fee;
							printf("VNBR:%c%c%c%c:%d:%.2f", title_[0],title_[1],title_[2],title_[3],hours_count,fee);
						}
						idle_num++;
						car_pos[i].state = 0;
					}
					else
					{
						// 入库比出库晚，错误
						printf("Error");
					}
				}
			}
		}
		if(!found)
		{
			// 未找到，尝试入库
			if(!idle_num)
				printf("Error");
			else
			{
				for(int i = 0; i < 8; ++i)
				{
					if(car_pos[i].state == 0)
					{
						// 空车位
						car_pos[i].state = state_;
						for(int j = 0; j < 4; ++j)
							car_pos[i].title[j] = title_[j];
						car_pos[i].hours = hours_;
						car_pos[i].secs = secs_;
						idle_num--;
						if(state_ == 1) cnbr_num++;
						else vnbr_num++;
						break;
					}
				}
			}
		}
	}
	else{
		printf("Error");
	}
	if(idle_num)
	{
		ucled |= 0x01;
		led_renew();
	}
	else
	{
		ucled &= 0xfe;
		led_renew();
	}
	uart_buffer_size = 0;
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_buffer, sizeof(uart_rx_buffer));
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
}