/*
 * main.c
 *
 *  Created on: Apr 9, 2024
 *      Author: moame
 */
#include"BIT_MATH.h"
#include"ErrType.h"
#include"STD_TYPES.h"
#include"ArrayStack.h"
#include"ArrayQueue.h"
#include"DIO_interface.h"
#include"PORT_interface.h"
#include"EXTI_interface.h"
#include"GIE_interface.h"
#include"CLCD_interface.h"
#include"KPD_interface.h"
#include"math.h"
#include"util/delay.h"

uint8 Glob_u8MathErr=0,Glob_u8Reset=0;

void ISR(void)
{
	Glob_u8Reset=1;
}

uint32 POW(uint32 base,uint32 exp)
{
	uint32 Local_u32Num=1;
	for(uint8 Local_u8Iterator=0;Local_u8Iterator<exp;Local_u8Iterator++)
	{
		Local_u32Num=Local_u32Num*base;
	}
	return Local_u32Num;
}
uint32 FromHexToDec(StackUint8* Ps)
{
    uint32 Local_u32Decimal=0;
    uint8 Local_u8Current=0;
    uint8 Local_u8Iterator=0;
    while(!Stack_u8IsEmptyOp(Ps))
    {
        Local_u8Current=StackChar_u8Pop(Ps);
        if(Local_u8Current<='9')
        {
            Local_u32Decimal=Local_u32Decimal+(Local_u8Current-'0')*POW(16,Local_u8Iterator);
        }
        else
        {
            Local_u32Decimal=Local_u32Decimal+(Local_u8Current-'A'+10)*POW(16,Local_u8Iterator);
        }
        Local_u8Iterator++;
    }
    return Local_u32Decimal;
}

uint32 FromOctalToDec(StackUint8* Ps)
{
    uint32 Local_u32Decimal=0;
    uint8 Local_u8Current=0;
    uint8 Local_u8Iterator=0;
    while(!Stack_u8IsEmptyOp(Ps))
    {
        Local_u8Current=StackChar_u8Pop(Ps);
        Local_u32Decimal=Local_u32Decimal+(Local_u8Current-'0')*POW(8,Local_u8Iterator);
        Local_u8Iterator++;
    }
    return Local_u32Decimal;
}

uint32 FromBinToDec(StackUint8* Ps)
{
    uint32 Local_u32Decimal=0;
    uint8 Local_u8Current=0;
    uint8 Local_u8Iterator=0;
    while(!Stack_u8IsEmptyOp(Ps))
    {
        Local_u8Current=StackChar_u8Pop(Ps);
        Local_u32Decimal=Local_u32Decimal+(Local_u8Current-'0')*POW(2,Local_u8Iterator);
        Local_u8Iterator++;
    }
    return Local_u32Decimal;
}

 void FromDecToBin(uint32 Cpy_u32Num,StackUint8* Ptr_sBin)
{
    while(Cpy_u32Num!=0)
    {
        StackChar_vPushOp(Ptr_sBin,((Cpy_u32Num%2)+'0'));
        Cpy_u32Num/=2;
    }
}
void FromDecToOctal(uint32 Cpy_u32Num,StackUint8* Ptr_sBin)
{
    while(Cpy_u32Num!=0)
    {
        StackChar_vPushOp(Ptr_sBin,((Cpy_u32Num%8)+'0'));
        Cpy_u32Num/=8;
    }
}
void FromDecToHex(uint32 Cpy_u32Num,StackUint8* Ptr_sBin)
{
    uint8 Local_u8Current=0;
    while(Cpy_u32Num!=0)
    {
        Local_u8Current=Cpy_u32Num%16;
        if(Local_u8Current>=10)
        {
            Local_u8Current=Local_u8Current+'A'-10;
            StackChar_vPushOp(Ptr_sBin,Local_u8Current);
        }
        else
        {
            StackChar_vPushOp(Ptr_sBin,((Cpy_u32Num%16)+'0'));
        }
        Cpy_u32Num/=16;
    }
}

uint8 MathErrCheck(Queue_f32* Ptr_qNumbers,Queue_uint8* Ptr_qOp)
{
	if((Queue_u8CountNumb(Ptr_qNumbers)-Queue_u8CountOp(Ptr_qOp))==1)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void ReverseStackNum(StackF32* Ps)
{
	Queue_f32 Local_qNumbers;
	Queue_vInitQueueNum(&Local_qNumbers);
	while(!Stack_u8IsEmptyNum(Ps))
	{
		Queue_vEnqueueNum(&Local_qNumbers, StackNum_u8Pop(Ps));
	}
	while(!Queue_u8IsEmptyNum(&Local_qNumbers))
	{
		StackNum_vPushNum(Ps, Queue_f32DequeueNum(&Local_qNumbers));
	}
	return;
}
void ReverseStackOp(StackUint8* Ps)
{
	Queue_uint8 Local_qOp;
	Queue_vInitQueueOp(&Local_qOp);
	while(!Stack_u8IsEmptyOp(Ps))
	{
		Queue_vEnqueueOp(&Local_qOp, StackChar_u8Pop(Ps));
	}
	while(!Queue_u8IsEmptyOp(&Local_qOp))
	{
		StackChar_vPushOp(Ps, Queue_f32DequeueOp(&Local_qOp));
	}
	return;
}
f32 Calculate(StackF32* Ptr_sNumbers,StackUint8* Ptr_sOp)
{
	Glob_u8MathErr=0;
	StackF32 Local_qNumbers;
	StackUint8 Local_qOp;
	StackChar_vInit(&Local_qOp);
	StackNum_vInit(&Local_qNumbers);
	f32 Local_f32Current,Local_f32Previous;
	uint8 Local_u8Op;
	ReverseStackNum(Ptr_sNumbers);
	ReverseStackOp(Ptr_sOp);
	while(!Stack_u8IsEmptyOp(Ptr_sOp))
	{
		Local_u8Op=StackChar_u8Pop(Ptr_sOp);
		Local_f32Previous=StackNum_u8Pop(Ptr_sNumbers);
		if(Local_u8Op=='/')
		{
			Local_f32Current=StackNum_u8Pop(Ptr_sNumbers);
			if(Local_f32Current==0)
			{
				Glob_u8MathErr=1;
				return 0;
			}
			else
			{
				Local_f32Current=Local_f32Previous/Local_f32Current;
				StackNum_vPushNum(Ptr_sNumbers, Local_f32Current);
			}
		}
		else if(Local_u8Op=='*')
		{
			Local_f32Current=StackNum_u8Pop(Ptr_sNumbers);
			Local_f32Current=Local_f32Previous*Local_f32Current;
			StackNum_vPushNum(Ptr_sNumbers, Local_f32Current);
		}
		else
		{
			StackChar_vPushOp(&Local_qOp, Local_u8Op);
			StackNum_vPushNum(&Local_qNumbers, Local_f32Previous);
		}
	}
	StackNum_vPushNum(&Local_qNumbers, StackNum_u8Pop(Ptr_sNumbers));
	ReverseStackNum(&Local_qNumbers);
	ReverseStackOp(&Local_qOp);
	while(!Stack_u8IsEmptyOp(&Local_qOp))
	{
		Local_u8Op=StackChar_u8Pop(&Local_qOp);
		Local_f32Previous=StackNum_u8Pop(&Local_qNumbers);
		Local_f32Current=StackNum_u8Pop(&Local_qNumbers);
		if(Local_u8Op=='+')
		{
			Local_f32Current=Local_f32Current+Local_f32Previous;
			StackNum_vPushNum(&Local_qNumbers, Local_f32Current);
		}
		else if(Local_u8Op=='-')
		{
			Local_f32Current=Local_f32Previous-Local_f32Current;
			StackNum_vPushNum(&Local_qNumbers, Local_f32Current);
		}
	}
	return StackNum_u8Pop(&Local_qNumbers);
}
void SimpleCalculator()
{
	CLCD_vClear();
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	StackF32 Local_sNumbers;
	StackUint8 Local_sOperators;
	StackChar_vInit(&Local_sOperators);
	StackNum_vInit(&Local_sNumbers);
	uint32 Local_u32Number=0;
	while((1)&&(Glob_u8Reset==0))
	{
		while((Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)&&(Glob_u8Reset==0))
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		if(Local_u8PressedButton=='A')
		{
			StackChar_vInit(&Local_sOperators);
			StackNum_vInit(&Local_sNumbers);
			CLCD_vClear();
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		}
		else if((Local_u8PressedButton=='+')||(Local_u8PressedButton=='-')||(Local_u8PressedButton=='*')||(Local_u8PressedButton=='/'))
		{
			CLCD_vSendData(Local_u8PressedButton);
			StackNum_vPushNum(&Local_sNumbers, (f32)Local_u32Number);
			StackChar_vPushOp(&Local_sOperators, Local_u8PressedButton);
			Local_u32Number=0;
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		}
		else if((Local_u8PressedButton>='0')&&(Local_u8PressedButton<='9'))
		{
			CLCD_vSendData(Local_u8PressedButton);
			Local_u32Number=Local_u32Number*10+(Local_u8PressedButton-'0');
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		}
		else if(Local_u8PressedButton=='=')
		{
			CLCD_vSendPosition(0, 1);
			CLCD_vSendData(Local_u8PressedButton);
			StackNum_vPushNum(&Local_sNumbers, (f32)Local_u32Number);
			CLCD_vSendNumber((sint32)(Calculate(&Local_sNumbers, &Local_sOperators)));
			StackChar_vInit(&Local_sOperators);
			StackNum_vInit(&Local_sNumbers);
			Local_u32Number=0;
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while((Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)&&(Glob_u8Reset==0))
			{
				Local_u8PressedButton=KPD_u8GetPressedButton();
			}
			CLCD_vClear();
		}
	}
	if(Glob_u8Reset==1)
	{
		Glob_u8Reset=0;
	}
	return;
}

void PreCalculator()
{
	StackUint8 Local_sOperators;
	StackChar_vInit(&Local_sOperators);
	StackF32 Local_sNumbers;
	StackNum_vInit(&Local_sNumbers);
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	uint8 Local_u8Counter=0;
	while(Glob_u8Reset==0)
	{
		CLCD_vClear();
		CLCD_vSendString("Enter Operations");
		CLCD_vSendPosition(0, 1);
		Local_u8Counter=0;
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
		{
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while((Glob_u8Reset==0)&&(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON))
			{
				Local_u8PressedButton=KPD_u8GetPressedButton();
			}
			if((Local_u8PressedButton=='+')||(Local_u8PressedButton=='-')||(Local_u8PressedButton=='*')||(Local_u8PressedButton=='/'))
			{
				CLCD_vSendData(Local_u8PressedButton);
				StackChar_vPushOp(&Local_sOperators, Local_u8PressedButton);
				Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
				Local_u8Counter++;
			}
		}
		uint32 Local_u32Number=0;
		for(uint8 Local_u8Iterator=1;Local_u8Iterator<=Local_u8Counter+1;Local_u8Iterator++)
		{
			CLCD_vClear();
			CLCD_vSendString("Enter Number");
			CLCD_vSendData(Local_u8Iterator+'0');
			CLCD_vSendPosition(0, 1);
			Local_u32Number=0;
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
			{
				 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
				while((Glob_u8Reset==0)&&(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON))
				{
					Local_u8PressedButton=KPD_u8GetPressedButton();
				}
				if((Local_u8PressedButton>='0')&&(Local_u8PressedButton<='9'))
				{
					CLCD_vSendData(Local_u8PressedButton);
					Local_u32Number=Local_u32Number*10+(Local_u8PressedButton-'0');
					Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
				}
			}
			StackNum_vPushNum(&Local_sNumbers, Local_u32Number);
		}
		CLCD_vClear();
		CLCD_vSendNumber((sint32)Calculate(&Local_sNumbers, &Local_sOperators));
		while((Local_u8PressedButton!='A')&&(Glob_u8Reset==0))
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		CLCD_vClear();
	}
	if(Glob_u8Reset==1)
	{
		Glob_u8Reset=0;
	}
	return;
}

void PostCalculator()
{
	StackUint8 Local_sOperators;
	StackChar_vInit(&Local_sOperators);
	StackF32 Local_sNumbers;
	StackNum_vInit(&Local_sNumbers);
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	uint8 Local_u8Counter=0;
	while(Glob_u8Reset==0)
	{
		CLCD_vClear();
		CLCD_vSendString("Enter Numbers");
		CLCD_vSendPosition(0, 1);
		Local_u8Counter=0;
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		uint32 Local_u32Number=0;
		while((Glob_u8Reset==0)&&(Local_u8PressedButton!='A'))
		{
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while((Glob_u8Reset==0)&&(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON))
			{
				Local_u8PressedButton=KPD_u8GetPressedButton();
			}
			if((Local_u8PressedButton>='0')&&(Local_u8PressedButton<='9'))
			{
				CLCD_vSendData(Local_u8PressedButton);
				Local_u32Number=Local_u32Number*10+Local_u8PressedButton-'0';
				Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			}
			else if(Local_u8PressedButton=='=')
			{
				Local_u8Counter++;
				StackNum_vPushNum(&Local_sNumbers, Local_u32Number);
				Local_u32Number=0;
				Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
				CLCD_vClear();
				CLCD_vSendString("Enter Numbers");
				CLCD_vSendPosition(0, 1);
			}
		}
		CLCD_vClear();
		CLCD_vSendString("Enter ");
		CLCD_vSendData(Local_u8Counter-1+'0');
		CLCD_vSendString("operation");
		uint8 Local_u8OpCounter=0;
		CLCD_vSendPosition(0, 1);
		while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
		{
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while((Glob_u8Reset==0)&&(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON))
			{
				Local_u8PressedButton=KPD_u8GetPressedButton();
			}
			if((Local_u8PressedButton=='+')||(Local_u8PressedButton=='-')||(Local_u8PressedButton=='*')||(Local_u8PressedButton=='/'))
			{
				CLCD_vSendData(Local_u8PressedButton);
				StackChar_vPushOp(&Local_sOperators, Local_u8PressedButton);
				Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
				Local_u8OpCounter++;
			}
		}
		if((Local_u8OpCounter>=Local_u8Counter)||(Local_u8Counter-Local_u8OpCounter!=1))
		{
			CLCD_vClear();
			CLCD_vSendString("Math Error");
		}
		else
		{
			CLCD_vClear();
			CLCD_vSendNumber((sint32)Calculate(&Local_sNumbers, &Local_sOperators));
		}
		while((Local_u8PressedButton!='A')&&(Glob_u8Reset==0))
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		CLCD_vClear();
	}
	if(Glob_u8Reset==1)
	{
		Glob_u8Reset=0;
	}
	return;

}

void GetBin(StackUint8* Ptr_sBin)
{
	CLCD_vClear();
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
	{
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		while(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		if((Local_u8PressedButton=='1')||(Local_u8PressedButton=='0'))
		{
			CLCD_vSendData(Local_u8PressedButton);
			StackChar_vPushOp(Ptr_sBin, Local_u8PressedButton);
		}
	}
	return;
}

void GetOctal(StackUint8* Ptr_sBin)
{
	CLCD_vClear();
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
	{
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		while(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		if((Local_u8PressedButton>='0')&&(Local_u8PressedButton<='7'))
		{
			CLCD_vSendData(Local_u8PressedButton);
			StackChar_vPushOp(Ptr_sBin, Local_u8PressedButton);
		}
	}
	return;
}

void GetHex(StackUint8* Ptr_sBin)
{
	CLCD_vClear();
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
	{
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		while(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		if((Local_u8PressedButton>='0')&&(Local_u8PressedButton<='9'))
		{
			CLCD_vSendData(Local_u8PressedButton);
			StackChar_vPushOp(Ptr_sBin, Local_u8PressedButton);
		}
	}
	return;
}

uint32 GetDecimal()
{
	CLCD_vClear();
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	uint32 Local_u32Number=0;
	while((Glob_u8Reset==0)&&(Local_u8PressedButton!='='))
	{
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		while(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		if((Local_u8PressedButton>='0')&&(Local_u8PressedButton<='9'))
		{
			CLCD_vSendData(Local_u8PressedButton);
			Local_u32Number=Local_u32Number*10+Local_u8PressedButton-'0';
		}
	}
	return Local_u32Number;
}

uint8 BaseSelect()
{
	uint8 Local_u8PinValue=DIO_u8PIN_HIGH;
	while((Glob_u8Reset==0))
	{
		DIO_u8ReadPinValue(DIO_u8PORTC, DIO_u8PIN0, &Local_u8PinValue);
		if(Local_u8PinValue==DIO_u8PIN_LOW)
		{
			return 0;
		}
		DIO_u8ReadPinValue(DIO_u8PORTC, DIO_u8PIN1, &Local_u8PinValue);
		if(Local_u8PinValue==DIO_u8PIN_LOW)
		{
			return 1;
		}
		DIO_u8ReadPinValue(DIO_u8PORTC, DIO_u8PIN2, &Local_u8PinValue);
		if(Local_u8PinValue==DIO_u8PIN_LOW)
		{
			return 2;
		}
		DIO_u8ReadPinValue(DIO_u8PORTC, DIO_u8PIN3, &Local_u8PinValue);
		if(Local_u8PinValue==DIO_u8PIN_LOW)
		{
			return 3;
		}
	}
	return 4;
}

void PrintNumber(StackUint8* Ptr_sNumber)
{
	while(!Stack_u8IsEmptyOp(Ptr_sNumber))
	{
		CLCD_vSendData(StackChar_u8Pop(Ptr_sNumber));
	}
}

void Base(void)
{
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON,Local_u8PinValue;
	while(1&&(Glob_u8Reset==0))
	{
		CLCD_vClear();
		CLCD_vSendString("Convert From:");
		Local_u8PinValue=BaseSelect();
		if(Local_u8PinValue==0)
		{
			StackUint8 Local_sBinary;
			StackChar_vInit(&Local_sBinary);
			GetBin(&Local_sBinary);
			uint32 Local_u32Number=0;
			if(Glob_u8Reset==0)
			{
				CLCD_vClear();
				CLCD_vSendString("Convert To:");
				Local_u8PinValue=BaseSelect();
				if(Local_u8PinValue==0)
				{
					CLCD_vClear();
					PrintNumber(&Local_sBinary);
				}
				else if(Local_u8PinValue==1)
				{
					CLCD_vClear();
					Local_u32Number=FromBinToDec(&Local_sBinary);
					FromDecToOctal(Local_u32Number, &Local_sBinary);
					PrintNumber(&Local_sBinary);
				}
				else if(Local_u8PinValue==2)
				{
					CLCD_vClear();
					Local_u32Number=FromBinToDec(&Local_sBinary);
					CLCD_vSendNumber((sint32)Local_u32Number);
				}
				else if(Local_u8PinValue==3)
				{
					CLCD_vClear();
					Local_u32Number=FromBinToDec(&Local_sBinary);
					FromDecToHex(Local_u32Number, &Local_sBinary);
					PrintNumber(&Local_sBinary);
				}
			}
		}
		else if(Local_u8PinValue==1)
		{
			StackUint8 Local_sOctal;
			StackChar_vInit(&Local_sOctal);
			GetOctal(&Local_sOctal);
			if(Glob_u8Reset==0)
			{
				CLCD_vClear();
				CLCD_vSendString("Convert To:");
				Local_u8PinValue=BaseSelect();
				uint32 Local_u32Number=0;
				if(Local_u8PinValue==0)
				{
					CLCD_vClear();
					Local_u32Number=FromOctalToDec(&Local_sOctal);
					FromDecToBin(Local_u32Number, &Local_sOctal);
					PrintNumber(&Local_sOctal);
				}
				else if(Local_u8PinValue==1)
				{
					CLCD_vClear();
					PrintNumber(&Local_sOctal);
				}
				else if(Local_u8PinValue==2)
				{
					CLCD_vClear();
					Local_u32Number=FromOctalToDec(&Local_sOctal);
					CLCD_vSendNumber((sint32)Local_u32Number);
				}
				else if(Local_u8PinValue==3)
				{
					CLCD_vClear();
					Local_u32Number=FromOctalToDec(&Local_sOctal);
					FromDecToHex(Local_u32Number, &Local_sOctal);
					PrintNumber(&Local_sOctal);
				}
			}
		}
		else if(Local_u8PinValue==2)
		{
			uint32 Local_u32Number=0;
			Local_u32Number=GetDecimal();
			CLCD_vClear();
			CLCD_vSendString("Convert To:");
			Local_u8PinValue=BaseSelect();
			StackUint8 Local_sNumber;
			StackChar_vInit(&Local_sNumber);
			if(Local_u8PinValue==0)
			{
				CLCD_vClear();
				FromDecToBin(Local_u32Number, &Local_sNumber);
				PrintNumber(&Local_sNumber);
			}
			else if(Local_u8PinValue==1)
			{
				CLCD_vClear();
				FromDecToOctal(Local_u32Number, &Local_sNumber);
				PrintNumber(&Local_sNumber);
			}
			else if(Local_u8PinValue==2)
			{
				CLCD_vClear();
				CLCD_vSendNumber((sint32)Local_u32Number);
			}
			else if(Local_u8PinValue==3)
			{
				CLCD_vClear();
				FromDecToHex(Local_u32Number, &Local_sNumber);
				PrintNumber(&Local_sNumber);
			}
		}
		else if(Local_u8PinValue==3)
		{
			StackUint8 Local_sHex;
			StackChar_vInit(&Local_sHex);
			GetHex(&Local_sHex);
			CLCD_vClear();
			CLCD_vSendString("Convert To:");
			Local_u8PinValue=BaseSelect();
			uint32 Local_u32Number=0;
			if(Local_u8PinValue==0)
			{
				CLCD_vClear();
				Local_u32Number=FromHexToDec(&Local_sHex);
				FromDecToBin(Local_u32Number, &Local_sHex);
				PrintNumber(&Local_sHex);
			}
			else if(Local_u8PinValue==1)
			{
				CLCD_vClear();
				Local_u32Number=FromHexToDec(&Local_sHex);
				FromDecToOctal(Local_u32Number, &Local_sHex);
				PrintNumber(&Local_sHex);
			}
			else if(Local_u8PinValue==2)
			{
				CLCD_vClear();
				Local_u32Number=FromHexToDec(&Local_sHex);
				CLCD_vSendNumber((sint32)Local_u32Number);
			}
			else if(Local_u8PinValue==3)
			{
				CLCD_vClear();
				PrintNumber(&Local_sHex);
			}
		}
		while((Local_u8PressedButton!='A')&&(Glob_u8Reset==0))
		{
			Local_u8PressedButton=KPD_u8GetPressedButton();
		}
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	}
	if(Glob_u8Reset==1)
	{
		Glob_u8Reset=0;
	}
}
void main(void)
{
	PORT_vInitDirection();
	GIE_vEnableGlobalInterrupt();
	CLCD_vInitLcd();
	EXTI_u8SetSenseCtrl(INT2, FALLING_EDGE);
	EXTI_u8SetCallBack(INT2, &ISR);
	uint8 Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
	uint8 Local_u8Flag=0;
	while(1)
	{
		CLCD_vClear();
		Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
		Local_u8Flag=0;
		while(1)
		{
			if(Local_u8Flag==1)
			{
				CLCD_vClear();
				CLCD_vSendString("Wrong Choice");
				_delay_ms(300);
				CLCD_vClear();
			}
			CLCD_vSendString("Press");
			CLCD_vSendPosition(0, 1);
			CLCD_vSendString("1-Simple 2-Base");
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while(Local_u8PressedButton==KPD_u8UNPRESSEDBUTTON)
			{
				Local_u8PressedButton=KPD_u8GetPressedButton();
			}
			Local_u8Flag=1;
			if((Local_u8PressedButton=='1')||(Local_u8PressedButton=='2'))
			{
				break;
			}
		}
		if(Local_u8PressedButton=='1')
		{
			EXTI_u8EnableIntChannel(INT2);
			CLCD_vClear();
			CLCD_vSendString("Press 1-In");
			CLCD_vSendPosition(0, 1);
			CLCD_vSendString("2-Post  3-Pre");
			Local_u8PressedButton=KPD_u8UNPRESSEDBUTTON;
			while((Glob_u8Reset==0))
			{
				Local_u8PressedButton=KPD_u8GetPressedButton();
				if((Local_u8PressedButton=='1')||(Local_u8PressedButton=='2')||(Local_u8PressedButton=='3'))
				{
					break;
				}
			}
			switch (Local_u8PressedButton) {
				case '1':SimpleCalculator();break;
				case '2':PostCalculator();break;
				case '3':PreCalculator();break;
			}
			EXTI_u8DisableIntChannel(INT2);
		}
		else if(Local_u8PressedButton=='2')
		{
			EXTI_u8EnableIntChannel(INT2);
			Base();
			EXTI_u8DisableIntChannel(INT2);
		}
	}
}
