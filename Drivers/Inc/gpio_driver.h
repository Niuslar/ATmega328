/*
 * gpio_driver.h
 *
 * Created: 03/08/2021 13:30:30
 *  Author: Niuslar
 */ 


#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

#include "atmega328.h"

//General macros 
#define OUTPUT 1
#define INPUT  0

#define HIGH   1
#define LOW    0

//Pins definition 
#define PIN_NO_0  (1 << 3)
#define PIN_NO_1  (2 << 3)
#define PIN_NO_2  (4 << 3)
#define PIN_NO_3  (8 << 3)
#define PIN_NO_4  (16 << 3) 
#define PIN_NO_5  (32 << 3)
#define PIN_NO_6  (64 << 3) 
#define PIN_NO_7  (128 << 3)

typedef struct 
{
    uint16_t pin_number; //pin number
    uint8_t pin_mode; //input, output or AF
    uint8_t pin_pu; //internal pull-up (Enable, Disable)
}pin_config_t;

typedef struct  
{
    gpio_reg_t *p_port_x;
    pin_config_t pin_config;
}pin_handle_t;


/*APIs*/

void gpio_init(pin_handle_t *pin_handler);
//This function accepts multiple pins at the same time when using the pin macros (i.e PIN_NO_0 | PIN_NO_1 | etc.) 
//This is not possible when using the direct pin number (i.e 1)
void gpio_write_digital_pin(gpio_reg_t *p_port_x, uint16_t pin_number_def,uint8_t value); 
uint8_t gpio_read_digital_pin(gpio_reg_t *p_port_x, uint16_t pin_number_def);


#endif /* GPIO_DRIVER_H_ */