#ifndef CLCD_CFG_H
#define CLCD_CFG_H
#include"CLCD_prv.h"
#define CLCD_u8MODE 		 FOUR_BIT
#define CONNECTION_TYPE      GND_CONNECTION
#if CLCD_u8MODE==EIGHT_BIT
#define CLCD_u8DATA_PORT   	 DIO_u8PORTB

#elif CLCD_u8MODE==FOUR_BIT

#define CLCD_u8DATA_PORT   	 DIO_u8PORTA

#define CLCD_u8DATA_PIN4	 DIO_u8PIN3
#define CLCD_u8DATA_PIN5	 DIO_u8PIN4
#define CLCD_u8DATA_PIN6	 DIO_u8PIN5
#define CLCD_u8DATA_PIN7	 DIO_u8PIN6

#endif

#define CLCD_u8CONTROL_PORT  DIO_u8PORTA

#define CLCD_u8RS_PIN        DIO_u8PIN1

#if CONNECTION_TYPE==DIO_CONNECTION
#define CLCD_u8RW_PIN        DIO_u8PIN1
#endif

#define CLCD_u8ENABLE_PIN    DIO_u8PIN2




#endif