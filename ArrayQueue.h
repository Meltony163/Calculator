#ifndef ARRAY_H
#define ARRAY_H

#define MAX_SIZEQ 10
typedef struct queueNum
{
    f32 arr[MAX_SIZEQ];
    sint8 front;
    sint8 rear;
}Queue_f32;

typedef struct queueOp
{
    uint8 arr[MAX_SIZEQ];
    sint8 front;
    sint8 rear;
}Queue_uint8;

uint8 Queue_u8IsEmptyNum(Queue_f32 *pq);

uint8 Queue_u8IsEmptyOp(Queue_uint8 *pq);

void Queue_vInitQueueNum(Queue_f32 *pq);

void Queue_vInitQueueOp(Queue_uint8 *pq);

void Queue_vEnqueueNum(Queue_f32 *pq,f32 num);

void Queue_vEnqueueOp(Queue_uint8 *pq,uint8 num);

f32 Queue_f32DequeueNum(Queue_f32 *pq);

uint8 Queue_f32DequeueOp(Queue_uint8 *pq);

uint8 Queue_u8CountNumb(Queue_f32* pq);

uint8 Queue_u8CountOp(Queue_uint8* pq);

#endif
