#include"STD_TYPES.h"
#include"ArrayQueue.h"

uint8 Queue_u8IsEmptyNum(Queue_f32 *pq)
{
    if((pq->front==-1)||(pq->front==pq->rear+1))
    {
        return 1;
    }
    return 0;
}

uint8 Queue_u8IsEmptyOp(Queue_uint8 *pq)
{
    if((pq->front==-1)||(pq->front==pq->rear+1))
    {
        return 1;
    }
    return 0;
}

void Queue_vInitQueueNum(Queue_f32 *pq)
{
    pq->front=-1;
    pq->rear=-1;
    return;
}

void Queue_vInitQueueOp(Queue_uint8 *pq)
{
    pq->front=-1;
    pq->rear=-1;
    return;
}

void Queue_vEnqueueNum(Queue_f32 *pq,f32 num)
{
    if(pq->front==-1)
    {
        pq->front=0;
        pq->rear=0;
        pq->arr[pq->front]=num;
        return;
    }
    pq->rear++;
    pq->arr[pq->rear]=num;
    return;
}

void Queue_vEnqueueOp(Queue_uint8 *pq,uint8 num)
{
    if(pq->front==-1)
    {
        pq->front=0;
        pq->rear=0;
        pq->arr[pq->front]=num;
        return;
    }
    pq->rear++;
    pq->arr[pq->rear]=num;
    return;
}

f32 Queue_f32DequeueNum(Queue_f32 *pq)
{
	f32 Local_f32Num=pq->arr[pq->front];
    pq->front++;
    return Local_f32Num;
}

uint8 Queue_f32DequeueOp(Queue_uint8 *pq)
{
	uint8 Local_u8Num=pq->arr[pq->front];
    pq->front++;
    return Local_u8Num;
}

uint8 Queue_u8CountNumb(Queue_f32* pq)
{
	uint8 Local_u8Num=0;
    if(Queue_u8IsEmptyNum(pq))
    {
        return 0;
    }
    for(int i=pq->front;i<=pq->rear;i++)
    {
    	Local_u8Num++;
    }
    return Local_u8Num;
}

uint8 Queue_u8CountOp(Queue_uint8* pq)
{
	uint8 Local_u8Num=0;
    if(Queue_u8IsEmptyOp(pq))
    {
        return 0;
    }
    for(int i=pq->front;i<=pq->rear;i++)
    {
    	Local_u8Num++;
    }
    return Local_u8Num;
}

