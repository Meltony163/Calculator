#include<stdio.h>
#include"STD_TYPES.h"
#include"ArrayStack.h"

void StackNum_vInit(StackF32 *ps)
{
    ps->top=-1;
    return;
}

void StackChar_vInit(StackUint8 *ps)
{
    ps->top=-1;
    return;
}


void StackNum_vPushNum(StackF32 *ps, f32 num)
{
    ps->top++;
    ps->arr[ps->top]=num;
    return;
}

void StackChar_vPushOp(StackUint8 *ps, uint8 Op)
{
    ps->top++;
    ps->arr[ps->top]=Op;
    return;
}

uint8 Stack_u8IsEmptyNum(StackF32 *ps)
{
    if(ps->top==-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

uint8 Stack_u8IsEmptyOp(StackUint8 *ps)
{
    if(ps->top==-1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

f32 StackNum_u8Pop(StackF32 *ps)
{
	f32 Local_u32Num=ps->arr[ps->top];
    ps->top=ps->top-1;
	return Local_u32Num;
}

uint8 StackChar_u8Pop(StackUint8 *ps)
{
	uint8 Local_u8Op=ps->arr[ps->top];
    ps->top=ps->top-1;
	return Local_u8Op;
}
