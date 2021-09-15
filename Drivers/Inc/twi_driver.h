/*
 * i2c_driver.h
 *
 * Created: 03/08/2021 13:17:05
 *  Author: Niuslar
 */ 


#ifndef TWI_DRIVER_H_
#define TWI_DRIVER_H_

#include "atmega328.h"

//General macros 
#define TWI_SPEED_STD  100000UL //SCL Standard Frequency of 100kHz
#define TWI_SPEED_FAST 400000UL //SCL Fast Frequency of 400kHz

//TWI Control Register bits
#define TWIE   0 
#define TWEN   2
#define TWWC   3
#define TWSTO  4
#define TWSTA  5
#define TWEA   6
#define TWINT  7

//Status codes for master transmitter mode (TWSR masked with 0xF8)
#define TWI_SC_START     0x08 
#define TWI_SC_RS        0x10 //Repeated Start
#define TWI_SC_SLAW_ACK  0x18 //SLA+W and ACK received
#define TWI_SC_SLAW_NACK 0x20 //SLA+W sent and NACK received
#define TWI_SC_DB_ACK    0x28 //Data Byte transmitted and ACK received 
#define TWI_SC_DB_NACK   0x30 //Data Byte transmitted and NACK received 
#define TWI_SC_AL        0x38 //Arbitration Lost

//Status codes for master receiver mode 
#define TWI_SC_SLAR_ACK  0x40 //SLA+R has been transmitted and ACK received 
#define TWI_SC_SLAR_NACK 0x48 //SLA+R has been transmitted and NACK received
#define TWI_SC_DR_ACK    0x50 //Data Byte has been received and ACK returned
#define TWI_SC_DR_NACK   0x58 //Data Byte has been received and NACK returned

//Busy state macros 
#define TWI_READY  0
#define BUSY_IN_RX 1
#define BUSY_IN_TX 2


//Power Reduction Register PRTWI bit 
#define PRTWI   7


void twi_init(uint32_t twi_speed);
void twi_master_send(twi_reg_t *twi_reg, uint8_t *tx_buf, uint8_t len, uint8_t slave_addr, uint8_t rep_start);
void twi_master_receive(twi_reg_t *twi_reg, uint8_t *rx_buf, uint8_t slave_addr,uint8_t len, uint8_t rep_start);


#endif /* TWI_DRIVER_H_ */