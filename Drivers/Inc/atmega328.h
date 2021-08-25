/*
 * atmega328.h
 *
 * Created: 03/08/2021 13:17:23
 *  Author: Niuslar
 */ 


#ifndef ATMEGA328_H_
#define ATMEGA328_H_

#include <stdint.h>


//System Clock Frequency
#define F_CPU 8000000UL

//General use macros 
#define ENABLE   1
#define DISABLE  0
#define NO_RS    DISABLE 
#define YES_RS   ENABLE

//GPIO Register Definition 
typedef struct 
{
    volatile uint8_t PINx;  //Port Input 
    volatile uint8_t DDRx;  //Data Direction Register
    volatile uint8_t PORTx; //Port Register 
}gpio_reg_t;

//2-wire interface Register Definition 
typedef struct  
{
    volatile uint8_t TWBR; //Bit rate register
    volatile uint8_t TWSR; //Status Register
    volatile uint8_t TWAR; //(Slave) Address Register
    volatile uint8_t TWDR; //Data Register
    volatile uint8_t TWCR; //Control Register
    volatile uint8_t TWAMR; //(Slave) Address Mask Register
}twi_reg_t;

//SPI Register Definition 
typedef struct 
{
    volatile uint8_t SPCR; //Control Register
    volatile uint8_t SPSR; //Status Register
    volatile uint8_t SPDR; //Data Register
}spi_reg_t;

//8-bit timer register definition 
typedef struct
{
    volatile uint8_t TCCR0A; //Timer/counter control register  A
    volatile uint8_t TCCR0B; //Timer/counter control register  B
    volatile uint8_t TCNT0;  //Time/Counter register 
    volatile uint8_t OCR0A;  //Output compare register A
    volatile uint8_t OCR0B;  //Output compare register B
    
}tcr8_reg_t;


//16-bit timer register definition
typedef struct
{
    volatile uint8_t   TCCR1A; //Timer/counter control register  A
    volatile uint8_t   TCCR1B; //Timer/counter control register  B
    volatile uint8_t   TCCR1C; //Timer/counter control register  B
    volatile uint8_t   reserved;
    volatile uint8_t   TCNT1L;  //Timer/Counter1 - Counter Register Low Byte
    volatile uint8_t   TCNT1H;  //Timer/Counter1 - Counter Register High Byte
    volatile uint8_t   ICR1L;   //Timer/Counter1 - Input Capture Register Low Byte
    volatile uint8_t   ICR1H;   //Timer/Counter1 - Input Capture Register High Byte
    volatile uint16_t  OCR1A; //Timer/Counter1 - Output Compare Register A 
    volatile uint16_t  OCR1B; //Timer/Counter1 - Output Compare Register B 
    
}tcr16_reg_t;


//GPIO relevant addresses
//PORTx Base address
#define PORTB_BASE_ADDR    0x23
#define PORTC_BASE_ADDR    0x26
#define PORTD_BASE_ADDR    0x29

//Power reduction register
#define PRR   *((volatile uint8_t *)0x62)

//8-bit timer/counter 0 register base address
#define TCR0    ((tcr8_reg_t*)0x44)

//16-bit timer/counter 1 register base address
#define TCR1    ((tcr16_reg_t*)0x80)

//Ports registers
#define PORTB  ((gpio_reg_t*)PORTB_BASE_ADDR)
#define PORTC  ((gpio_reg_t*)PORTC_BASE_ADDR)
#define PORTD  ((gpio_reg_t*)PORTD_BASE_ADDR)

//TWI registers base address
#define TWI    ((twi_reg_t*)0xB8)

//SPI registers base address 
#define SPI    ((spi_reg_t*)0x4C)

//Timer Interrupt Mask Register 0
#define TIMSK0  *((volatile uint8_t *)0x6E)

//Timer Interrupt Mask Register 1
#define TIMSK1  *((volatile uint8_t *)0x6F)

//AVR Status Register
#define SREG    *((volatile uint8_t *)0x5F)

//Vectors table
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

#define ISR(vector, ...)            \
void vector (void) __attribute__ ((signal,used, externally_visible)) __VA_ARGS__; \
void vector (void)


#include "twi_driver.h"
#include "gpio_driver.h"
#include "spi_driver.h"
#include "lcd_driver.h"
#include "aht10_driver.h"

#endif /* ATMEGA328_H_ */