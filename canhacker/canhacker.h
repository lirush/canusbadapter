#ifndef _CANHACKER_H
#define _CANHACKER_H

#include "canhacker_impl.h"
#include "can.h"
#include "leds.h"

typedef struct{
	uint8_t connect;
	uint8_t disconnect;
	uint8_t numch;
	uint8_t mode;
}CANHacker_typedef;

void Lawicel(void);
void SenTestCANHacker(void);
void SendToCANHacker(uint8_t ch);

#endif
