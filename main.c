/*
 * ATMega328.c
 *
 * Author : Niuslar
 */ 



#include "atmega328.h"
#include <util/delay.h>

pin_handle_t pin_handler;

void number_to_string(uint8_t num, char* buf)
{
    if(num < 10)
    {
        buf[0] = '0';
        buf[1] = num + 48; //ASCII value
    }
    else
    {
        buf[0] = (num/10) + 48;
        buf[1] = (num%10) + 48;
    }
    
    buf[2] = '\0';
}

int main(void)
{
    
    lcd_init();
    lcd_print_string("Hello World");
    _delay_ms(1000);
    lcd_clear();   
    
    char hum_buf[3]; 
    char temp_buf[3];


   
    while(1)
    {   
        float humidity = read_humidity();
        float temp = read_temperature();
        
        number_to_string((int)humidity,hum_buf);
        
        number_to_string((int)temp,temp_buf);
        
        //print temperature first row
        lcd_set_cursor_xy(1,1);
        lcd_print_string("Temp: ");
        lcd_set_cursor_xy(1,8);
        lcd_print_string(temp_buf);
        lcd_set_cursor_xy(1,11);
        lcd_print_string("C");
        
        //print humidity second row
        lcd_set_cursor_xy(2,1);
        lcd_print_string("Hum: ");
        lcd_set_cursor_xy(2,8);
        lcd_print_string(hum_buf);
        lcd_set_cursor_xy(2,11);
        lcd_print_string("%");        
        
        _delay_ms(500);
    }

}



