/*
 * ATMega328.c
 *
 * Author : Niuslar
 */ 



#include "atmega328.h"
#include "timers.h"

pin_handle_t pin_handler;
void read_print_temperature();
void read_print_humidity();

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
    enable_8_bit_timer();
    lcd_init();
    aht10_init();

    
    read_print_temperature();
    read_print_humidity();
    
    uint32_t init_time = millis();
    
    uint16_t lcd_refresh_interval = 500; //refresh LCD every 500 ms

    while(1)
    {   
        if((millis() - init_time) > lcd_refresh_interval)
        {
            read_print_humidity();
            read_print_temperature();
            init_time = millis();
        }
    }

}

void read_print_temperature()
{
    char temp_buf[3];
    float temp = read_temperature();
    number_to_string((int)temp,temp_buf);
    
    //print temperature first row
    lcd_set_cursor_xy(1,1);
    lcd_print_string("Temp: ");
    lcd_set_cursor_xy(1,8);
    lcd_print_string(temp_buf);
    lcd_set_cursor_xy(1,11);
    lcd_print_string("C");
}
void read_print_humidity()
{
    char hum_buf[3];
    float humidity = read_humidity();
    number_to_string((int)humidity,hum_buf);
    
     //print humidity second row
     lcd_set_cursor_xy(2,1);
     lcd_print_string("Hum: ");
     lcd_set_cursor_xy(2,8);
     lcd_print_string(hum_buf);
     lcd_set_cursor_xy(2,11);
     lcd_print_string("%");
}



