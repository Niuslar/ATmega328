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
    
}tcr_reg_t;



//GPIO relevant addresses
//PORTx Base address
#define PORTB_BASE_ADDR    0x23
#define PORTC_BASE_ADDR    0x26
#define PORTD_BASE_ADDR    0x29

//Power reduction register
#define PRR   *((volatile uint8_t *)0x62)

//8-bit timer/counter 0 register base address
#define TCR0    ((tcr_reg_t*)0x44)


//Ports registers
#define PORTB  ((gpio_reg_t*)PORTB_BASE_ADDR)
#define PORTC  ((gpio_reg_t*)PORTC_BASE_ADDR)
#define PORTD  ((gpio_reg_t*)PORTD_BASE_ADDR)

//TWI registers base address
#define TWI    ((twi_reg_t*)0xB8)

//SPI registers base address 
#define SPI    ((spi_reg_t*)0x4C)

//Timer Interrupt Mask Register
#define TIMSK0  *((volatile uint8_t *)0x6E)

//AVR Status Register
#define SREG    *((volatile uint8_t *)0x5F)

#include "twi_driver.h"
#include "gpio_driver.h"
#include "spi_driver.h"
#include "lcd_driver.h"
#include "aht10_driver.h"

#endif /* ATMEGA328_H_ */