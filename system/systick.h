#ifndef __SYSTICK_H_
#define __SYSTICK_H_

#include <MDR32Fx.h>

#define _1SEC		(1000)
#define _2SEC		(2000)
#define _2p5SEC	(2500)
#define _3SEC		(3000)

extern volatile uint32_t TimingDelay_ms;
extern uint32_t Ticks;

uint32_t uiGetTimeMs(void);
uint8_t uiTimer(uint32_t setting);


#endif // __SYSTICK_H_
