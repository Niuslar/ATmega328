/*
 * timers.c
 *
 * Created: 25/08/2021 15:27:04
 *  Author: Nico
 ***********NOTE: This file's functions and defines are based on the Arduino millis() and micros() functions*****
 */ 

#include "timers.h"

static uint32_t timer0_millis = 0;
static uint32_t timer0_fract = 0;

#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))

#define MILLIS_INC (MICROSECONDS_PER_TIMER0_OVERFLOW / 1000)

#define FRACT_INC ((MICROSECONDS_PER_TIMER0_OVERFLOW % 1000) >> 3)
#define FRACT_MAX (1000 >> 3)

void enable_8_bit_timer()
{
    TCR0->TCCR0A = 0x00; //Normal mode selected
    
    SREG |= (1 << I); //Enable interrupts
    
    TIMSK0 |= (1 << TOIE0); //Enable Timer overflow interrupt 
    
    TCR0->TCCR0B |= (1 << CS01) | (1 << CS00); //Set prescaler to 64 and Start timer
    
}

ISR(TIMER0_OVF_vect)
{
    //Every 256 clicks, the ISR will begin 
    
    //Get current value for millis and fract
    unsigned long m = timer0_millis; 
    unsigned char f = timer0_fract;
 
    //Add corresponding value depending on F_CPU
    m += MILLIS_INC;
    f += FRACT_INC;
    if (f >= FRACT_MAX) {
        f -= FRACT_MAX;
        m += 1;
    }
 
    //Update values of millis and frac
    timer0_fract = f;
    timer0_millis = m;
}

//Note: with a system clock of 8MHz, 2 ms is the minimum resolution
uint32_t millis()
{
    unsigned long m;
    uint8_t oldSREG = SREG;
        
    // disable interrupts while we read timer0_millis or we might get an
    // inconsistent value (e.g. in the middle of a write to timer0_millis)
    SREG &= ~(1 << I);
    m = timer0_millis;
    SREG = oldSREG;
        
    return m;
}
uint32_t micros()
{
    //TODO: Implement micros function
}