/*
 * aht10_driver.c
 *
 * Created: 13/08/2021 21:59:12
 *  Author: Niuslar
 */ 


#include "aht10_driver.h"
#include <util/delay.h>
#include <math.h>

static float read_sensor(uint8_t temp_or_hum);

//Commands to trigger measurement 
uint8_t trig_cmd[3] = {AHT10_TRIG_MEAS, AHT10_DAT1_CMD, AHT10_DAT2_CMD};

void aht10_init()
{
    twi_init(TWI_SPEED_STD); 
    uint8_t init = AHT10_INIT_CMD;
    twi_master_send(TWI, &init, 1, AHT10_ADDR, NO_RS);
}

float read_humidity()
{
    return read_sensor(HUMIDITY);
}

float read_temperature()
{
    return read_sensor(TEMPERATURE);
}

static float read_sensor(uint8_t temp_or_hum)
{
        uint8_t rx_buf[6];
        twi_master_send(TWI, trig_cmd, 3, AHT10_ADDR, NO_RS);
        _delay_ms(75);
        twi_master_receive(TWI, rx_buf, AHT10_ADDR, 6, NO_RS);
        
        //check if the device is busy and try to read data again
        while(rx_buf[0] & (1 << 7))
        {
            twi_master_receive(TWI, rx_buf, AHT10_ADDR, 6, NO_RS);
        }
        
        uint32_t humidity_reading = ((uint32_t)rx_buf[1] << 12) | ((uint16_t)rx_buf[2] << 4) | (rx_buf[3] >> 4) ;
        
        uint32_t temp_reading = (((uint32_t)rx_buf[3] & 0x0F) << 16) | ((uint16_t)rx_buf[4] << 8) | (rx_buf[5]) ;
        
        float humidity = (((float)humidity_reading) / (pow(2,20))) * 100;
        
        float temperature = ((((float)temp_reading) / (pow(2,20))) * 200) - 50;
        
        if(temp_or_hum == HUMIDITY)
        {
            return humidity;
        }
        else if(temp_or_hum == TEMPERATURE)
        {
            return temperature;
        }
        
        return 999.0f; //return unrealistic value 
        
}