/*
 * interrupts.h
 *
 * Created: 23/08/2021 12:12:02
 *  Author: Nico
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

//Vectors
#define INT0_vect         _VECTOR(1)   /* External Interrupt Request 0 */
#define INT1_vect         _VECTOR(2)   /* External Interrupt Request 1 */
#define PCINT0_vect       _VECTOR(3)   /* Pin Change Interrupt Request 0 */
#define PCINT1_vect       _VECTOR(4)   /* Pin Change Interrupt Request 0 */
#define PCINT2_vect       _VECTOR(5)   /* Pin Change Interrupt Request 1 */
#define WDT_vect          _VECTOR(6)   /* Watchdog Time-out Interrupt */
#define TIMER2_COMPA_vect _VECTOR(7)   /* Timer/Counter2 Compare Match A */
#define TIMER2_COMPB_vect _VECTOR(8)   /* Timer/Counter2 Compare Match A */
#define TIMER2_OVF_vect   _VECTOR(9)   /* Timer/Counter2 Overflow */
#define TIMER1_CAPT_vect  _VECTOR(10)  /* Timer/Counter1 Capture Event */
#define TIMER1_COMPA_vect _VECTOR(11)  /* Timer/Counter1 Compare Match A */
#define TIMER1_COMPB_vect _VECTOR(12)  /* Timer/Counter1 Compare Match B */
#define TIMER1_OVF_vect   _VECTOR(13)  /* Timer/Counter1 Overflow */
#define TIMER0_COMPA_vect _VECTOR(14)  /* TimerCounter0 Compare Match A */
#define TIMER0_COMPB_vect _VECTOR(15)  /* TimerCounter0 Compare Match B */
#define TIMER0_OVF_vect   _VECTOR(16)  /* Timer/Couner0 Overflow */
#define SPI_STC_vect      _VECTOR(17)  /* SPI Serial Transfer Complete */
#define USART_RX_vect     _VECTOR(18)  /* USART Rx Complete */
#define USART_UDRE_vect   _VECTOR(19)  /* USART, Data Register Empty */
#define USART_TX_vect     _VECTOR(20)  /* USART Tx Complete */
#define ADC_vect          _VECTOR(21)  /* ADC Conversion Complete */
#define EE_READY_vect     _VECTOR(22)  /* EEPROM Ready */
#define ANALOG_COMP_vect  _VECTOR(23)  /* Analog Comparator */
#define TWI_vect          _VECTOR(24)  /* Two-wire Serial Interface */
#define SPM_READY_vect    _VECTOR(25)  /* Store Program Memory Read */

//Function macros to use ISR

#define _VECTOR(N) __vector_ ## N

#  define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal,used, externally_visible)) __VA_ARGS__; \
void vector (void)

//Registers bit definitions
#define TIMSK0  *((volatile uint8_t *)0x6E)

#define SREG    *((volatile uint8_t *)0x5F)

//Bits in TCCR0A
#define WGM01  0
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

//I is the bit that enables interrupts in the SREG (Status Register) 
#define I    7

#endif /* INTERRUPTS_H_ */