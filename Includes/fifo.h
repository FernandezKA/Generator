#ifndef _fifo_h_
#define _fifo_h_
#include "main.h"

#define TypeFifo uint8_t

struct fifo
{
	TypeFifo Data[64U];
	uint16_t Head;
	uint16_t Tail;
};

typedef struct fifo FIFO;

void FifoInit(FIFO *buf);

void Push(FIFO *buf, TypeFifo data);

TypeFifo Pull(FIFO *buf);

uint16_t GetSize(FIFO *buf);

void Clear(FIFO *buf);
#endif
