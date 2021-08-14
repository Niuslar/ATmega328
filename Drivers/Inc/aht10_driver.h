/*
 * aht10_driver.h
 *
 * Created: 13/08/2021 21:58:22
 *  Author: Nico
 */ 


#ifndef AHT10_DRIVER_H_
#define AHT10_DRIVER_H_

#include "atmega328.h"
#include "twi_driver.h"

#define AHT10_ADDR 0x38

//commands 
#define AHT10_INIT_CMD     0xE1 
#define AHT10_SOFT_RESET   0xBA
#define AHT10_TRIG_MEAS    0xAC
#define AHT10_DAT1_CMD     0x33
#define AHT10_DAT2_CMD     0x00

//General 
#define HUMIDITY    0
#define TEMPERATURE 1

//APIs 
void aht10_init();
float read_temperature();
float read_humidity();


#endif /* AHT10_DRIVER_H_ */