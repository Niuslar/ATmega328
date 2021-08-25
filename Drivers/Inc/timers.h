/*
 * interrupts.h
 *
 * Created: 23/08/2021 12:12:02
 *  Author: Nico
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

#include "atmega328.h"

//Registers bit definitions

#define SREG    *((volatile uint8_t *)0x5F)

//I is the bit that enables interrupts in the SREG (Status Register)
#define I    7

//Bits in TCCR0A
#define WGM00  0
#define WGM01  1
#define COM0B0 4
#define COM0B1 5
#define COM0A0 6
#define COM0A1 7

//Bits in TCCR0B
#define CS00   0
#define CS01   1
#define CS02   2
#define WGM02  3
#define FOC0B  6
#define FOC0A  7

//Bits in TIMSK0
#define TOIE0   0
#define OCIE0A  1
#define OCIE0B  2

//Bits in TCCR1B 
#define CS10  0
#define CS11  1
#define CS12  2
#define WGM12 3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

//Bits in TIMSK1 
#define TOIE1  0 
#define OCIE1A 1
#define OCIE1B 2
#define ICIE1  5

//Functions 
void enable_8_bit_timer();
uint32_t millis();
uint32_t micros();


#endif /* TIMERS_H_ */