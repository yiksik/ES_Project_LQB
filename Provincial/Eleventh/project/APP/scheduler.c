#include "scheduler.h"

typedef struct{
	void (*func)(void);
	uint32_t rate_ms;
	uint32_t last_run;
} task_t;

task_t tasks[] = {
	{lcd_proc, 100, 0},
	{adc_proc, 50, 0},
	{key_proc, 10, 0},
};

void scheduler_run(void)
{
	static uint8_t tasks_num = sizeof(tasks) / sizeof(task_t);
	for(uint8_t i = 0; i < tasks_num; ++i)
	{
		if(uwTick >= tasks[i].last_run + tasks[i].rate_ms)
		{
			tasks[i].func();
			tasks[i].last_run = uwTick;
		}
	}
}