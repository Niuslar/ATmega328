/*
 * gpio_driver.c
 *
 * Created: 03/08/2021 13:30:44
 *  Author: Niuslar
 */ 


#include "gpio_driver.h"

static uint8_t pin_validation(uint16_t pin_int);

void gpio_init(pin_handle_t *pin_handle)
{
    //Validate pin number 
    pin_handle->pin_config.pin_number = pin_validation(pin_handle->pin_config.pin_number);
    
    //Select the mode (Input, Output)
    if(pin_handle->pin_config.pin_mode == OUTPUT)
    {
        pin_handle->p_port_x->DDRx |= pin_handle->pin_config.pin_number;
    }
    else if(pin_handle->pin_config.pin_mode == INPUT)
    {
        pin_handle->p_port_x->DDRx &= ~pin_handle->pin_config.pin_number;

        //Enable or Disable internal pull-up when the mode is INPUT
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

void gpio_write_digital_pin(gpio_reg_t *p_port_x, uint16_t pin_number, uint8_t value)
{
    //validate the pin number 
    pin_number = pin_validation(pin_number);
    
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
uint8_t gpio_read_digital_pin(gpio_reg_t *p_port_x, uint16_t pin_number)
{
    //validate the pin number 
    pin_number = pin_validation(pin_number);
    
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

//If the user enters a pin number without using the definitions, this function will return the corresponding def
static uint8_t pin_validation(uint16_t pin_int)
{
    if(pin_int < 7)
    {
        switch(pin_int)
        {
            case 0:
                return (PIN_NO_0 >> 3);
            case 1:
                return (PIN_NO_1 >> 3);
            case 2:
                return (PIN_NO_2 >> 3);
            case 3:
                return (PIN_NO_3 >> 3);
            case 4: 
                return (PIN_NO_4 >> 3);
            case 5: 
                return (PIN_NO_5 >> 3); 
            case 6:
                return (PIN_NO_6 >> 3);
            case 7:
                return (PIN_NO_7 >> 3);
            default: 
                return 99;
        }
    }
    
    else
    {
        return pin_int >> 3;
    }
    
}

