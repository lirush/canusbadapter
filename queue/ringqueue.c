#include "ringqueue.h"
#include <string.h>

void RingQueInit(RingQueue_typedef *q, uint8_t *data, uint16_t size)
{
	q->buffer = data;
	q->head=0;
	q->tail=0;
	q->size=size;
	q->avail=0;
}

uint8_t uiRingQueEmpty(RingQueue_typedef *q)
{
	return (q->tail==q->head)?1:0;
}

void RingQuePut(RingQueue_typedef *q, uint8_t *data, uint16_t size)
{
	if(q->size-q->avail<size)return;
	
	uint16_t q1 = min(size,q->size-q->tail);
	uint16_t q2 = size - q1;
	
	memcpy(q->buffer+q->tail,data,q1);
	memcpy(q->buffer,data+q1,q2);
	
	q->tail = (q->tail+size) % q->size;
	q->avail += size;
}

void RingQueGet(RingQueue_typedef *q, uint8_t *data, uint16_t size)
{
	if(q->avail<size)return;
	
	uint16_t q1 = min(size,q->size-q->head);
	uint16_t q2 = size - q1;
	
	memcpy(data,q->buffer+q->head,q1);
	memcpy(data+q1,q->buffer,q2);
	
	q->head = (q->head+size) % q->size;
	q->avail -= size;	
}

void RingQueClear(RingQueue_typedef *q)
{
	q->head=0;
	q->tail=0;
	q->avail=0;
}

uint8_t uiRingQueIsFull(RingQueue_typedef *q)
{
	return (q->avail==q->size)?1:0;
}
