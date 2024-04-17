#ifndef CLCD_INTERFACE_h
#define CLCD_INTERFACE_h
#include"STD_TYPES.h"
void CLCD_vSendCommand(uint8 cpy_u8Command);

void CLCD_vSendData(uint8 cpy_u8Data);

void CLCD_vInitLcd();

void CLCD_vSendString(uint8* ptr_u8Data);

void CLCD_vSendNumber(sint32 cpy_s32Data);

void CLCD_vSendPosition(uint8 cpy_u8XPosition,uint8 cpy_u8YPosition);

uint8 CLCD_u8SendPattern(uint8 cpy_u8MemoryLocation,uint8* ptr_u8Pattern);

void CLCD_vClear();
#endif
