#ifndef CLCD_PRV_h
#define CLCD_PRV_h
#include "STD_TYPES.h"
#define EIGHT_BIT	1
#define FOUR_BIT	2

#define GND_CONNECTION 		1
#define DIO_CONNECTION		2
static void vSendEnablePulse();

static void vSendHalfData(uint8 cpy_u8Data);


#endif
