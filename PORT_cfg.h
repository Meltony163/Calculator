#ifndef PORT_CFG_h
#define PORT_CFG_h
#include"PORT_prv.h"
/*
*/
#define PORTA_PIN0_DIR              INPUT
#define PORTA_PIN1_DIR              OUTPUT
#define PORTA_PIN2_DIR              OUTPUT
#define PORTA_PIN3_DIR              OUTPUT
#define PORTA_PIN4_DIR              OUTPUT
#define PORTA_PIN5_DIR              OUTPUT
#define PORTA_PIN6_DIR              OUTPUT
#define PORTA_PIN7_DIR              INPUT

#define PORTB_PIN0_DIR              INPUT
#define PORTB_PIN1_DIR              INPUT
#define PORTB_PIN2_DIR              INPUT
#define PORTB_PIN3_DIR              INPUT
#define PORTB_PIN4_DIR              INPUT
#define PORTB_PIN5_DIR              INPUT
#define PORTB_PIN6_DIR              INPUT
#define PORTB_PIN7_DIR              INPUT

#define PORTC_PIN0_DIR              INPUT
#define PORTC_PIN1_DIR              INPUT
#define PORTC_PIN2_DIR              INPUT
#define PORTC_PIN3_DIR              INPUT
#define PORTC_PIN4_DIR              INPUT
#define PORTC_PIN5_DIR              INPUT
#define PORTC_PIN6_DIR              INPUT
#define PORTC_PIN7_DIR              INPUT

#define PORTD_PIN0_DIR              INPUT
#define PORTD_PIN1_DIR              INPUT
#define PORTD_PIN2_DIR              OUTPUT
#define PORTD_PIN3_DIR              OUTPUT
#define PORTD_PIN4_DIR              OUTPUT
#define PORTD_PIN5_DIR              OUTPUT
#define PORTD_PIN6_DIR              INPUT
#define PORTD_PIN7_DIR              INPUT

/*
*/
#define PORTA_PIN0_INIT             LOW
#define PORTA_PIN1_INIT             LOW
#define PORTA_PIN2_INIT             LOW
#define PORTA_PIN3_INIT             LOW
#define PORTA_PIN4_INIT             LOW
#define PORTA_PIN5_INIT             LOW
#define PORTA_PIN6_INIT             LOW
#define PORTA_PIN7_INIT             LOW

#define PORTB_PIN0_INIT             LOW
#define PORTB_PIN1_INIT             LOW
#define PORTB_PIN2_INIT             PULL_UP
#define PORTB_PIN3_INIT             LOW
#define PORTB_PIN4_INIT             PULL_UP
#define PORTB_PIN5_INIT             PULL_UP
#define PORTB_PIN6_INIT             PULL_UP
#define PORTB_PIN7_INIT             PULL_UP

#define PORTC_PIN0_INIT             PULL_UP
#define PORTC_PIN1_INIT         	PULL_UP
#define PORTC_PIN2_INIT      	    PULL_UP
#define PORTC_PIN3_INIT         	PULL_UP
#define PORTC_PIN4_INIT         	LOW
#define PORTC_PIN5_INIT         	LOW
#define PORTC_PIN6_INIT         	LOW
#define PORTC_PIN7_INIT         	LOW

#define PORTD_PIN0_INIT     	    LOW
#define PORTD_PIN1_INIT         	LOW
#define PORTD_PIN2_INIT         	HIGH
#define PORTD_PIN3_INIT         	HIGH
#define PORTD_PIN4_INIT         	HIGH
#define PORTD_PIN5_INIT         	HIGH
#define PORTD_PIN6_INIT         	LOW
#define PORTD_PIN7_INIT         	LOW

#endif
