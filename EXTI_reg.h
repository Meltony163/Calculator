#ifndef EXTI_REG_H
#define EXTI_REG_H

#define GICR                    (*((volatile uint8 *)0x5B))
#define MCUCR                   (*((volatile uint8 *)0x55))
#define MCUCSR					(*((volatile uint8 *)0x54))

#define MCUCR_ISC00_BIT                							  0u
#define MCUCR_ISC01_BIT                							  1u
#define MCUCR_ISC10_BIT                							  2u
#define MCUCR_ISC11_BIT                							  3u

#define MCUCSR_ISC2_BIT                							  4u

#define GICR_INT0_ENABLE_PIN									  6u
#define GICR_INT1_ENABLE_PIN									  7u
#define GICR_INT2_ENABLE_PIN									  5u

#endif