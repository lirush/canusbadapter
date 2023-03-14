#ifndef _RING_QUEUE_H
#define _RING_QUEUE_H

#include "stdint.h"

typedef struct{
	uint8_t *buffer;
	uint16_t size;
	uint16_t head;
	uint16_t tail;
	uint16_t avail;
}RingQueue_typedef;
extern RingQueue_typedef QueUSB;
extern RingQueue_typedef QueCAN1;
extern RingQueue_typedef QueCAN2;

static inline uint8_t min(uint16_t a, uint16_t b)
{
	return (a<b?a:b);
}

void RingQueInit(RingQueue_typedef *q, uint8_t *data, uint16_t size);
void RingQuePut(RingQueue_typedef *q, uint8_t *data, uint16_t size);
void RingQueGet(RingQueue_typedef *q, uint8_t *data, uint16_t size);
void RingQueClear(RingQueue_typedef *q);
uint8_t uiRingQueIsFull(RingQueue_typedef *q);
uint8_t uiRingQueEmpty(RingQueue_typedef *q);

#endif
