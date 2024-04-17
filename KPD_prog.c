#include"DIO_interface.h"
#include"BIT_MATH.h"
#include"ErrType.h"
#include"STD_TYPES.h"
#include"KPD_interface.h"
#include"KPD_cfg.h"
#include"KPD_prv.h"

uint8 KPD_u8GetPressedButton()
{
	uint8 Local_au8RowsPins[u8ROWNUM]={KPD_u8ROW1,KPD_u8ROW2,KPD_u8ROW3,KPD_u8ROW4};
	uint8 Local_au8CouloumsPins[u8COLNUM]={KPD_u8COLOUM1,KPD_u8COLOUM2,KPD_u8COLOUM3,KPD_u8COLOUM4};
	uint8 Local_u8RowIterator=0;
	uint8 Local_u8CouloumIterator=0;
	uint8 Local_u8PressedButton=DIO_u8PIN_HIGH;
	uint8 Local_au8KeyValue[u8COLNUM][u8ROWNUM]=KPD_au8BUTTONSVALUE;
	for(Local_u8CouloumIterator=0;Local_u8CouloumIterator<u8COLNUM;Local_u8CouloumIterator++)
	{
		DIO_u8SetPinValue(KPD_u8COLOUM_PORT, Local_au8CouloumsPins[Local_u8CouloumIterator], DIO_u8PIN_LOW);
		for(Local_u8RowIterator=0;Local_u8RowIterator<u8COLNUM;Local_u8RowIterator++)
		{
			DIO_u8ReadPinValue(KPD_u8ROW_PORT, Local_au8RowsPins[Local_u8RowIterator], &Local_u8PressedButton);
			if(Local_u8PressedButton==DIO_u8PIN_LOW)
			{
				while(Local_u8PressedButton==DIO_u8PIN_LOW)
				{
					DIO_u8ReadPinValue(KPD_u8ROW_PORT, Local_au8RowsPins[Local_u8RowIterator], &Local_u8PressedButton);
				}
				DIO_u8SetPinValue(KPD_u8COLOUM_PORT, Local_au8CouloumsPins[Local_u8CouloumIterator], DIO_u8PIN_HIGH);
				return Local_au8KeyValue[Local_u8RowIterator][Local_u8CouloumIterator];
			}
		}
		DIO_u8SetPinValue(KPD_u8COLOUM_PORT, Local_au8CouloumsPins[Local_u8CouloumIterator], DIO_u8PIN_HIGH);
	}
	return KPD_u8UNPRESSEDBUTTON;
}
