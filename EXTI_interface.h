#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

typedef enum
{
    LOW_LEVEL,
    ON_CHANGE,
    FALLING_EDGE,
    RISING_EDGE
}SenseCtrlType;
typedef enum
{
    INT0,
	INT1,
    INT2
}ChannelPin;

uint8 EXTI_u8SetCallBack(ChannelPin Cpy_sPin,void(*Ptr_function)(void));

void EXTI_vInit(void);

uint8 EXTI_u8EnableIntChannel(ChannelPin Cpy_sPin);

uint8 EXTI_u8DisableIntChannel(ChannelPin Cpy_sPin);

uint8 EXTI_u8SetSenseCtrl(ChannelPin Cpy_sPin,SenseCtrlType Cpy_sType);


#endif
