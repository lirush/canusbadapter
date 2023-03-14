#include "task.h"
#include "config.h"

volatile int timeslots;

void xRunTask(void (*func)(void))
{
    func();
}

void (*p_addr[QUANTITY_TASKS])(void);
unsigned char ucQTasks=0;

void xCreateTask(void (*func)(void))
{
    p_addr[ucQTasks]= func;
    ucQTasks++;
}

void vTaskScheduler(void)
{
//    while(1)
			{
        { 
					xRunTask(p_addr[timeslots]);
					if(timeslots++>=QUANTITY_TASKS-1)timeslots=0;
        }
    }
}
