#include"PORT_prv.h"
#include"PORT_cfg.h"
#include"PORT_interface.h"
#include"PORT_reg.h"
void PORT_vInitDirection(void)
{
	DDRA=PORTA_DIR;
	DDRB=PORTB_DIR;
	DDRC=PORTC_DIR;
	DDRD=PORTD_DIR;
	PORTA=PORTA_INIT;
	PORTB=PORTB_INIT;
	PORTC=PORTC_INIT;
	PORTD=PORTD_INIT;
}
