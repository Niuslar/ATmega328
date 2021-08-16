/*
 * gpio_driver.c
 *
 * Created: 03/08/2021 13:30:44
 *  Author: Niuslar
 */ 


#include "gpio_driver.h"

void gpio_init(pin_handle_t *pin_handle)
{
    //1. Select the mode (Input, Output)
    if(pin_handle->pin_config.pin_mode == OUTPUT)
    {
        pin_handle->p_port_x->DDRx |= pin_handle->pin_config.pin_number;
    }
    else if(pin_handle->pin_config.pin_mode == INPUT)
    {
        pin_handle->p_port_x->DDRx &= ~pin_handle->pin_config.pin_number;

        //2. Enable or Disable internal pull-up when the mode is INPUT
        if(pin_handle->pin_config.pin_pu == ENABLE)
        {
            pin_handle->p_port_x->PORTx |= pin_handle->pin_config.pin_number;
        }
        else
        {
            pin_handle->p_port_x->PORTx &= ~pin_handle->pin_config.pin_number;
        }
    }

}

void gpio_write_digital_pin(gpio_reg_t *p_port_x, uint8_t pin_number, uint8_t value)
{
    //Read register to get current status 
    uint8_t temp_port = p_port_x->PORTx; 
    
    //Combine this with the new value 
    if(value == LOW)
    {
        temp_port &= ~(pin_number);
        p_port_x->PORTx = temp_port;
    }
    //NOTE: Numbers different from 0 will drive the pin HIGH
    else
    {
        temp_port |= pin_number;
        p_port_x->PORTx = temp_port;
    }

}

//Note: This function can read multiple pins at once, but it will return only 0 (no pins HIGH) or 1 (at least one pin HIGH)
uint8_t gpio_read_digital_pin(gpio_reg_t *p_port_x, uint8_t pin_number)
{
    uint8_t value; 
    value = p_port_x->PINx & pin_number;
    if(value == LOW)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

