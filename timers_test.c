/*
 * main2.c
 *
 * Created: 19/08/2021 22:31:37
 *  Author: Niuslar
 * 
 * File to test the 8-bit and 16-bit timers, do not compile with main
 */ 


#include "atmega328.h"
#include "interrupts.h"

//Only one of the following define should be commented
//#define BIT_8_TIMER 
#define BIT_16_TIMER

int extra_time = 0;

int main()
{
    
    PORTB->DDRx = 0x01; 
    
    //Using the 8-bit timer
    #ifdef BIT_8_TIMER
    
    TCR0->TCCR0A = (1 << WGM01); //CTC Mode selected 
    
    TCR0->OCR0A = 78; //Clicks to get approx 0.01s, calculated with the AVR Timer Calculator online
    
    TIMSK0 = (1 << OCIE0A);
    
    SREG |= (1 << I); //Enable interrupts
    
    TCR0->TCCR0B |= (1 << CS02) | (1 << CS00); //Set prescaler to 1024 and start
    
    #endif
    
    //Using the 16-bit timer
    #ifdef BIT_16_TIMER
    TCR1->TCCR1B = (1 << WGM12); 
    
    TCR1->OCR1A = 7812; //clicks to get approx 1 sec
    
    TIMSK1 = (1 << OCIE1A);
    
    SREG |= (1 << I); //Enable interrupts 
    
    TCR1->TCCR1B |= (1 << CS12) | (1 << CS10);  //Set prescaler to 1024 and start
    
    #endif
    
    
    while(1)
    {
        
    }
}


#ifdef BIT_8_TIMER
ISR(TIMER0_COMPA_vect)
{
    extra_time++;
    
    if(extra_time > 100)
    {
       PORTB->PORTx ^= (1 << 0); //Toggle pin PB0
       extra_time = 0;
    }
}
#endif

#ifdef BIT_16_TIMER
ISR(TIMER1_COMPA_vect)
{
    PORTB->PORTx ^= (1 << 0); //Toggle pin PB0
}
#endif