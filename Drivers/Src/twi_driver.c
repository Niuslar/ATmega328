/*
 * twi_driver.c
 *
 * Created: 03/08/2021 13:16:20
 *  Author: Niuslar
 */ 

#include "twi_driver.h"

static uint8_t twi_bit_rate(uint32_t twi_speed);
static void ERROR();

void twi_init(uint32_t twi_speed)
{
    //1. Set PRTWI bit in the PRR to zero
    PRR &= ~(1 << PRTWI);
    
    //2. SCL Frequency
    //Define bit rate  based on SCL frequency 
    uint8_t bit_rate = twi_bit_rate(twi_speed);
    
    //Write value to the TWIBR Register
    TWI->TWBR = bit_rate;

}
void twi_master_send(twi_reg_t *twi_reg, uint8_t *tx_buf, uint8_t len, uint8_t slave_addr, uint8_t rep_start)
{
    
    //1. Generate start condition (check first if there was a repeated start)
    if( (twi_reg->TWSR & 0xF8) != TWI_SC_RS)
    {
        twi_reg->TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); 
        
        //2.Wait for TWINT Flag set. This indicates START condition has been transmitted
        while(!(twi_reg->TWCR & (1 << TWINT)));
            
        //3. Check TWI Status Register
        if( (twi_reg->TWSR & 0xF8) != TWI_SC_START)
        {
            ERROR();
        }
    }
   
    //4.Load SLA+W to Data Register
    uint8_t slaw = (slave_addr << 1);  
    twi_reg->TWDR = slaw;
    
    //5.Clear TWINT to start transmission of address 
    twi_reg->TWCR = (1 << TWINT) | (1 << TWEN);
    
    //6.Wait for TWINT Flag set. This indicates SLA+W has been transmitted
    while(! (twi_reg->TWCR & (1 << TWINT)));
    
    //7. Check TWI Status Register
    if( (twi_reg->TWSR & 0xF8) != TWI_SC_SLAW_ACK)
    {
        ERROR();
    }
    
    //8.send data byte by byte 
    while(len>0)
    {
         //9. Load data from buffer into Data Register
         twi_reg->TWDR = *tx_buf;
         
         //10. Clear TWINT bit to start transmission of data
         twi_reg->TWCR = (1 << TWINT) | (1 << TWEN);
         
         //11.Wait for TWINT Flag set. This indicates 1 byte of data has been transmitted
         while(! (twi_reg->TWCR & (1 << TWINT)));
             
         //11.  Check TWI Status Register
         if( (twi_reg->TWSR & 0xF8) != TWI_SC_DB_ACK)
         {
             ERROR();
         }   
         
         len--;
         tx_buf++;    
    }
    
    //11. Transmit stop condition or repeated start 
    if( rep_start == ENABLE)
    {
        //Repeated START
        twi_reg->TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); 
    }
    else
    {
        //STOP
        twi_reg->TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    }
    
    
}
void twi_master_receive(twi_reg_t *twi_reg, uint8_t *rx_buf, uint8_t slave_addr,uint8_t len, uint8_t rep_start)
{
    //1. Generate start condition (check first if there was a repeated start)
    if((twi_reg->TWSR & 0xF8) != TWI_SC_RS)
    {
        //No RS, continue with START transmission
        twi_reg->TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
        
        //2.Wait for TWINT Flag set. This indicates START condition has been transmitted
        while(! (twi_reg->TWCR & (1 << TWINT)));
        
        //3. Check TWI Status Register
        if( (twi_reg->TWSR & 0xF8) != TWI_SC_START)
        {
            ERROR();
        }
    }
    
    //4.Load SLA+R to Data Register
    uint8_t slar = (slave_addr << 1) | 1;
    twi_reg->TWDR = slar;
    
    //5. Clear TWINT to start address transmission 
    twi_reg->TWCR = (1 << TWINT) | (1 << TWEN);
    
    //6. Wait for TWINT flag 
    while(! ((twi_reg->TWCR) & (1 << TWINT)));
    
    //7. Check TWSR 
    if((twi_reg->TWSR & 0xF8) != TWI_SC_SLAR_ACK)
    {
        ERROR();
    }
    
    //8. Read data from TWDR until len is 0 
    while(len>0)
    {
         if(len == 1)
         {
             //Clear TWINT flag to receive last byte and at the same time send NACK
             twi_reg->TWCR = (1 << TWINT) | (1 << TWEN);
             
             //Wait until TWINT is set again (Data received)
             while (! ((twi_reg->TWCR) & (1 << TWINT)));
             
             //Read data
             *rx_buf = twi_reg->TWDR;
             
             len--;           
         }
         
         else
         {
             //Clear TWINT flag to receive data and at the same time enable ACK
             twi_reg->TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
             
             //Wait until TWINT is set again (Data received)
             while (! ((twi_reg->TWCR) & (1 << TWINT)));
             
             //Read data
             *rx_buf = twi_reg->TWDR;
             
             len--;
             rx_buf++;             
         }

    }
    
    //11. Send STOP or RS 
    if(rep_start == ENABLE)
    {
        //Generate Repeated Start
        twi_reg->TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    }
    
    else
    {
        //STOP
        twi_reg->TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
    }    
}

static uint8_t twi_bit_rate(uint32_t twi_speed)
{
    uint32_t sys_freq = F_CPU;
    uint8_t bit_rate = ((sys_freq / (twi_speed)) - 16)/2;
    //NOTE: This assumes the CPU frequency is at least 8 Mhz and there is no prescaler
    return bit_rate;
    
}

void ERROR()
{
    while(1); //hang in infinite loop 
    
    //TODO: Change this to actually display an error 
}