#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 16

typedef struct stackFloat
{
    sint8 top;
    f32 arr[MAX_SIZE];
}StackF32;

typedef struct stackChar
{
    sint8 top;
    uint8 arr[MAX_SIZE];
}StackUint8;

void StackNum_vInit(StackF32 *ps);

void StackChar_vInit(StackUint8 *ps);

void StackNum_vPushNum(StackF32 *ps, f32 num);

void StackChar_vPushOp(StackUint8 *ps, uint8 Op);

uint8 Stack_u8IsEmptyOp(StackUint8 *ps);

uint8 Stack_u8IsEmptyNum(StackF32 *ps);

f32 StackNum_u8Pop(StackF32 *ps);

uint8 StackChar_u8Pop(StackUint8 *ps);

#endif
