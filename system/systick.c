#include "systick.h"

volatile uint32_t TimingDelay_ms;
uint32_t Ticks=0;
uint32_t Time=0;

void SysTick_Handler(void)
{
  if (TimingDelay_ms > 0x00)
  {
    TimingDelay_ms--;
  }
	Ticks++; Time ++;
	NVIC_ClearPendingIRQ(SysTick_IRQn);
}

uint32_t uiGetTimeMs(void)
{
	return Time;
}

uint8_t uiTimer(uint32_t setting)
{
	uint8_t tcatch=0;
	if(Ticks>=setting)
	{
		Ticks=0; tcatch=1;
	}
	else tcatch=0;
	
	return tcatch;
}
