/*
 * spi_driver.c
 *
 * Created: 04/08/2021 17:35:26
 *  Author: Niuslar
 */ 


#include "spi_driver.h"


void spi_init(spi_config_t spi_config)
{
    //1. Set PRSPI bit in the PRR to zero
    PRR &= ~(1 << PRSPI);
    
    if(spi_config.spi_mode == MASTER)
    {
        //2. Initialize as master
        //Set MOSI, SCK and SS as output, the rest as input. 
        PORTB->DDRx = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
        
        //Keep SS as High 
        PORTB->PORTx |= (1 << DD_SS);
        
        //Enable SPI and Master mode
        SPI->SPCR = (1 << SPE) | (1 << MSTR);
        
        //Set clock rate
        if(spi_config.spi_speed < 4)
        {
            SPI->SPCR |= (spi_config.spi_speed << SPR0);    
        }
        else if(spi_config.spi_speed > 3)
        {
            SPI->SPSR |= (1 << SPI2X);
            SPI->SPCR |= ((spi_config.spi_speed & 0x3) << SPR0);
        }
       
    }
    else
    {
        //2. Initialize as slave
        //Set MISO as output, the rest as input
        PORTB->DDRx = (1 << DD_MISO);
        
        //Enable SPI
        SPI->SPCR = (1 << SPE);
        
    }
    
    //3. CPOL Config
    SPI->SPCR |= (spi_config.spi_cpol << CPOL);
    
    //4. CPHA Config
    SPI->SPCR |= (spi_config.spi_cpha << CPHA);
    
}

void spi_send(uint8_t *tx_buf, uint8_t len)
{

    while(len > 0)
    {
        //start transmission 
        SPI->SPDR = *tx_buf;
        
        //wait for transmission complete
        while(!(SPI->SPSR & (1 << SPIF)));
        
        len--;
        tx_buf++;
    }    
}

void spi_receive(uint8_t *rx_buf, uint8_t len)
{
    while(len>0)
    {
        *rx_buf = SPI->SPDR;
        rx_buf++;
        len--;
    }    
}
