/*
 * spi_driver.h
 *
 * Created: 04/08/2021 17:35:47
 *  Author: Niuslar
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

#include "atmega328.h"

//General Macros
#define MASTER 0
#define SLAVE  1

//Data direction macros
#define DD_SS      2 //Pin 2
#define DD_MOSI    3 //Pin 3 
#define DD_MISO    4 //Pin 4
#define DD_SCK     5 //Pin 5

//SPCR Bit definition 
#define SPR0      0
#define SPR1      1
#define CPHA      2
#define CPOL      3
#define MSTR      4
#define DORD      5
#define SPE       6
#define SPIE      7

//SPSR Bit definition
#define SPI2X     0
#define SPIF      7

//Frequency division factor 
#define SCK_DIV_4     0 
#define SCK_DIV_16    1
#define SCK_DIV_64    2
#define SCK_DIV_128   3

#define SCK_DIV_2     4
#define SCK_DIV_8     5
#define SCK_DIV_32    6

typedef struct  
{
    uint8_t spi_mode; //master or slave
    uint8_t spi_speed; //frequency division 
    uint8_t spi_cpol; //clock polarity
    uint8_t  spi_cpha; //clock phase
}spi_config_t;

//APIs prototypes
void spi_init(spi_config_t spi_config);
void spi_send(uint8_t *tx_buf, uint8_t len);
void spi_receive(uint8_t *rx_buf, uint8_t len);

//Power Reduction Register PRSPI bit
#define PRSPI   2



#endif /* SPI_DRIVER_H_ */