#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"ErrType.h"
#include"EXTI_prv.h"
#include"EXTI_cfg.h"
#include"EXTI_reg.h"
#include"EXTI_interface.h"
static void (*arr_funcptr[3])(void);
uint8 EXTI_u8SetCallBack(ChannelPin Cpy_sPin,void(*Ptr_function)(void))
{
	uint8 Local_u8ErrState=OK;
	if(Ptr_function!=NULL)
	{
		switch(Cpy_sPin)
		{
			case INT0:arr_funcptr[0]=Ptr_function; break;
			case INT1:arr_funcptr[1]=Ptr_function; break;
			case INT2:arr_funcptr[2]=Ptr_function; break;
			default:Local_u8ErrState=NOK; break;
		}
	}
	else
	{
		Local_u8ErrState=NULL_PTR;
	}
	return Local_u8ErrState;
}
void EXTI_vInit(void)
{

#if INT0_STATE==ENABLE
SET_BIT(GICR,GICR_INT0_ENABLE_PIN);
#elif INT0_STATE==DISABLE
CLR_BIT(GICR,GICR_INT0_ENABLE_PIN);
#else
#warning WRONG CONFIGRATION FOR INT0 STATE
#endif

#if INT1_STATE==ENABLE
SET_BIT(GICR,GICR_INT1_ENABLE_PIN);
#elif INT1_STATE==DISABLE
CLR_BIT(GICR,GICR_INT1_ENABLE_PIN);
#else
#warning WRONG CONFIGRATION FOR INT1 STATE
#endif

#if INT2_STATE==ENABLE
SET_BIT(GICR,GICR_INT2_ENABLE_PIN);
#elif INT2_STATE==DISABLE
CLR_BIT(GICR,GICR_INT2_ENABLE_PIN);
#else
#warning WRONG CONFIGRATION FOR INT2 STATE
#endif



#if INT0_SENSE_CTRL_TYPE==EXTI_u8RISING_EDGE
SET_BIT(MCUCR,MCUCR_ISC00_BIT);
SET_BIT(MCUCR,MCUCR_ISC01_BIT);
#elif INT0_SENSE_CTRL_TYPE==EXTI_u8FALLING_EDGE
CLR_BIT(MCUCR,MCUCR_ISC00_BIT);
SET_BIT(MCUCR,MCUCR_ISC01_BIT);
#elif INT0_SENSE_CTRL_TYPE==EXTI_u8LOGICAL_CHANGE
SET_BIT(MCUCR,MCUCR_ISC00_BIT);
CLR_BIT(MCUCR,MCUCR_ISC01_BIT);
#elif INT0_SENSE_CTRL_TYPE==EXTI_u8LOW_LEVEL
CLR_BIT(MCUCR,MCUCR_ISC00_BIT);
CLR_BIT(MCUCR,MCUCR_ISC01_BIT);
#else
#warning WORNG CONFIGRATION FOR INT0
#endif

#if INT1_SENSE_CTRL_TYPE==EXTI_u8RISING_EDGE
SET_BIT(MCUCR,MCUCR_ISC10_BIT);
SET_BIT(MCUCR,MCUCR_ISC11_BIT);
#elif INT1_SENSE_CTRL_TYPE==EXTI_u8FALLING_EDGE
CLR_BIT(MCUCR,MCUCR_ISC10_BIT);
SET_BIT(MCUCR,MCUCR_ISC11_BIT);
#elif INT1_SENSE_CTRL_TYPE==EXTI_u8LOGICAL_CHANGE
SET_BIT(MCUCR,MCUCR_ISC10_BIT);
CLR_BIT(MCUCR,MCUCR_ISC11_BIT);
#elif INT1_SENSE_CTRL_TYPE==EXTI_u8LOW_LEVEL
CLR_BIT(MCUCR,MCUCR_ISC10_BIT);
CLR_BIT(MCUCR,MCUCR_ISC11_BIT);
#else
#warning WORNG CONFIGRATION FOR INT1
#endif

#if INT2_SENSE_CTRL_TYPE==EXTI_u8RISING_EDGE
SET_BIT(MCUCSR,MCUCSR_ISC2_BIT);
#elif INT2_SENSE_CTRL_TYPE==EXTI_u8FALLING_EDGE
CLR_BIT(MCUCR,MCUCSR_ISC2_BIT);
#else
#warning WORNG CONFIGRATION FOR INT1
#endif
}

uint8 EXTI_u8EnableIntChannel(ChannelPin Cpy_sPin)
{
	uint8 Local_u8ErrState=OK;
	if(Cpy_sPin==INT0)
	{
		SET_BIT(GICR,GICR_INT0_ENABLE_PIN);
	}
	else if(Cpy_sPin==INT1)
	{
		SET_BIT(GICR,GICR_INT1_ENABLE_PIN);
	}
	else if(Cpy_sPin==INT2)
	{
		SET_BIT(GICR,GICR_INT2_ENABLE_PIN);
	}
	else
	{
		Local_u8ErrState=NOK;
	}
	return Local_u8ErrState;
}

uint8 EXTI_u8DisableIntChannel(ChannelPin Cpy_sPin)
{
	uint8 Local_u8ErrState=OK;
	if(Cpy_sPin==INT0)
	{
		CLR_BIT(GICR,GICR_INT0_ENABLE_PIN);
	}
	else if(Cpy_sPin==INT1)
	{
		CLR_BIT(GICR,GICR_INT1_ENABLE_PIN);
	}
	else if(Cpy_sPin==INT2)
	{
		CLR_BIT(GICR,GICR_INT2_ENABLE_PIN);
	}
	else
	{
		Local_u8ErrState=NOK;
	}
	return Local_u8ErrState;
}

uint8 EXTI_u8SetSenseCtrl(ChannelPin Cpy_sPin,SenseCtrlType Cpy_sType)
{
	uint8 Local_u8ErrState=OK;
	if(Cpy_sPin==INT0)
	{
		switch(Cpy_sType)
		{
			case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC00_BIT); SET_BIT(MCUCR,MCUCR_ISC01_BIT); break;
			case RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC00_BIT); SET_BIT(MCUCR,MCUCR_ISC01_BIT); break;
			case LOW_LEVEL:CLR_BIT(MCUCR,MCUCR_ISC00_BIT); CLR_BIT(MCUCR,MCUCR_ISC01_BIT); break;
			case ON_CHANGE:SET_BIT(MCUCR,MCUCR_ISC00_BIT); CLR_BIT(MCUCR,MCUCR_ISC01_BIT); break;
			default:Local_u8ErrState=NOK; break;
		}
	}
	else if(Cpy_sPin==INT1)
	{
		switch(Cpy_sType)
		{
			case FALLING_EDGE:CLR_BIT(MCUCR,MCUCR_ISC10_BIT); SET_BIT(MCUCR,MCUCR_ISC11_BIT); break;
			case RISING_EDGE:SET_BIT(MCUCR,MCUCR_ISC10_BIT); SET_BIT(MCUCR,MCUCR_ISC11_BIT); break;
			case LOW_LEVEL:CLR_BIT(MCUCR,MCUCR_ISC10_BIT); CLR_BIT(MCUCR,MCUCR_ISC11_BIT); break;
			case ON_CHANGE:SET_BIT(MCUCR,MCUCR_ISC10_BIT); CLR_BIT(MCUCR,MCUCR_ISC11_BIT); break;
			default:Local_u8ErrState=NOK; break;
		}
	}
	else if(Cpy_sPin==INT2)
	{
		switch(Cpy_sType)
		{
			case FALLING_EDGE:CLR_BIT(MCUCR,MCUCSR_ISC2_BIT); break;
			case RISING_EDGE:SET_BIT(MCUCSR,MCUCSR_ISC2_BIT); break;
			default:Local_u8ErrState=NOK; break;
		}
	}
	else
	{
		Local_u8ErrState=NOK;
	}
	return Local_u8ErrState;
}
__attribute__((signal)) void __vector_2(void);
void __vector_2(void)
{
	if(arr_funcptr[1]!=NULL)
	{
		arr_funcptr[1]();
		return;
	}
}
__attribute__((signal)) void __vector_1(void);
void __vector_1(void)
{
	if(arr_funcptr[0]!=NULL)
	{
		arr_funcptr[0]();
		return;
	}
}
