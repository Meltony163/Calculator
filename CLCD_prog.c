#include"CLCD_cfg.h"
#include<util/delay.h>
#include"DIO_interface.h"
#include"CLCD_cfg.h"
#include"CLCD_prv.h"
#include"BIT_MATH.h"
#include"ErrType.h"
static void vSendEnablePulse()
{
	DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8ENABLE_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8ENABLE_PIN, DIO_u8PIN_LOW);
}

static void vSendHalfData(uint8 cpy_u8Data)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8DATA_PIN4,GET_BIT(cpy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8DATA_PIN5,GET_BIT(cpy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8DATA_PIN6,GET_BIT(cpy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8DATA_PIN7,GET_BIT(cpy_u8Data,3));
	vSendEnablePulse();
}

void CLCD_vSendCommand(uint8 cpy_u8Command)
{
	DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_LOW);
    #if CONNECTION_TYPE==DIO_CONNECTION
	DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);
	#endif

	#if CLCD_u8MODE==EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, cpy_u8Command);
	vSendEnablePulse();
	#elif CLCD_u8MODE==FOUR_BIT
	vSendHalfData((cpy_u8Command>>4));
	vSendHalfData(cpy_u8Command);
	#endif
}

void CLCD_vSendData(uint8 cpy_u8Data)
{
	DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RS_PIN, DIO_u8PIN_HIGH);
	#if CONNECTION_TYPE==DIO_CONNECTION
	DIO_u8SetPinValue(CLCD_u8CONTROL_PORT, CLCD_u8RW_PIN, DIO_u8PIN_LOW);
	#endif
	#if CLCD_u8MODE==EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, cpy_u8Data);
	vSendEnablePulse();
	#elif CLCD_u8MODE==FOUR_BIT
	vSendHalfData((cpy_u8Data>>4));
	vSendHalfData(cpy_u8Data);
	#endif
}

void CLCD_vInitLcd()
{
	_delay_ms(40);
	#if CLCD_u8MODE==EIGHT_BIT
	CLCD_vSendCommand(0b00111000);
	#elif CLCD_u8MODE==FOUR_BIT
	vSendHalfData(0b0010);
	vSendHalfData(0b0010);
	vSendHalfData(0b1000);
	#endif
	CLCD_vSendCommand(0b00001100);
	CLCD_vSendCommand(1);
}
void CLCD_vSendString(uint8* ptr_u8Data)
{
	uint8 Loc_u8Iterator=0;
	while(ptr_u8Data[Loc_u8Iterator])
	{
		CLCD_vSendData(ptr_u8Data[Loc_u8Iterator]);
		Loc_u8Iterator++;
	}
}

void CLCD_vSendNumber(sint32 cpy_s32Data)
{
	if(cpy_s32Data<0)
	{
		CLCD_vSendData('-');
		cpy_s32Data=-1*cpy_s32Data;
	}
	if(cpy_s32Data==0)
	{
		CLCD_vSendData('0');
	}
	sint32 Loc_u32Num=0,Loc_u32Counter=0;
	while(cpy_s32Data>0)
	{
		Loc_u32Num*=10;
		Loc_u32Counter++;
		Loc_u32Num+=(cpy_s32Data%10);
		cpy_s32Data/=10;
	}
	while(Loc_u32Num)
	{
		CLCD_vSendData((uint8)(Loc_u32Num%10)+'0');
		Loc_u32Num/=10;
		Loc_u32Counter--;
	}
	while(Loc_u32Counter--)
	{
		CLCD_vSendData('0');
	}
}
void CLCD_vSendPosition(uint8 cpy_u8XPosition,uint8 cpy_u8YPosition)
{
	uint8 Loc_u8Position=0;
	Loc_u8Position=(0x40)*cpy_u8YPosition+cpy_u8XPosition;
	SET_BIT(Loc_u8Position,7);
	CLCD_vSendCommand(Loc_u8Position);
}
uint8 CLCD_u8SendPattern(uint8 cpy_u8MemoryLocation,uint8* ptr_u8Pattern)
{
	uint8 Loc_u8ErrorState=OK;
	if(ptr_u8Pattern!=NULL)
	{
		uint8 Loc_u8Location=cpy_u8MemoryLocation*8;
		SET_BIT(Loc_u8Location,6);
		CLCD_vSendCommand(Loc_u8Location);
		uint8 Loc_u8Iterator=0;
		for(;Loc_u8Iterator<8;Loc_u8Iterator++)
		{
			CLCD_vSendData(ptr_u8Pattern[Loc_u8Iterator]);
		}
	}
	else
	{
		Loc_u8ErrorState=NULL_PTR;
	}
	return Loc_u8ErrorState;
}
void CLCD_vClear()
{
	CLCD_vSendCommand(1);
}
