/*
 * lcd_driver.c
 *
 * Created: 11/08/2021 20:16:29
 *  Author: Nico
 */ 


#include "lcd_driver.h"
#include <util/delay.h>

static void send_4_bits(uint8_t data);
//static uint8_t read_bf();
static void send_cmd(uint8_t cmd);
static void lcd_enable();

pin_handle_t pin_handler;

void lcd_init()
{    
    //Initialise all the pins starting with RS (PB1)
    pin_handler.p_port_x = LCD_CMD_PORT; 
    pin_handler.pin_config.pin_mode = OUTPUT;
    pin_handler.pin_config.pin_number = LCD_RS;
    pin_handler.pin_config.pin_pu = DISABLE; 
    gpio_init(&pin_handler);
    
    //Pin E 
    pin_handler.pin_config.pin_number  = LCD_EN; 
    gpio_init(&pin_handler);
    
    //Pin R/W
    pin_handler.pin_config.pin_number = LCD_RW;
    gpio_init(&pin_handler);
    
    //Pins DB4-DB7 
    pin_handler.p_port_x = LCD_DATA_PORT;
    pin_handler.pin_config.pin_mode = OUTPUT; 
    pin_handler.pin_config.pin_pu =  DISABLE; 
    pin_handler.pin_config.pin_number = LCD_DB4; 
    
    gpio_init(&pin_handler);
    
    pin_handler.pin_config.pin_number = LCD_DB5; 
    gpio_init(&pin_handler);
    
    pin_handler.pin_config.pin_number = LCD_DB6; 
    gpio_init(&pin_handler);
    
    pin_handler.pin_config.pin_number = LCD_DB7;
    gpio_init(&pin_handler);
    
    //set all pins to LOW for initial config 
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RS, LOW);
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RW, LOW);
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_EN, LOW);
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB4, LOW);
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB5, LOW);
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB6, LOW);
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB7, LOW);
    
    //Initialisation by instruction 
    
    //Wait for 40 ms
     _delay_ms(40);
     
    //RS and RW LOW
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RS, LOW);
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RW, LOW);
    
    send_4_bits(0x3);

    _delay_ms(5);

    send_4_bits(0x3);

    _delay_us(150);

    send_4_bits(0x3);

    send_4_bits(0x2);
    
    //Set function 
    send_cmd(LCD_SET_FUNC);

    //Display ON with blinking cursor
    send_cmd(LCD_BLINK_CUR);
    
    //Clear Display 
    lcd_clear();

    //Entry mode
    send_cmd(LCD_ENTRY_MODE);
    
}
void lcd_clear()
{
    //Clear Display
    send_cmd(LCD_CLEAR_DISP);
    _delay_ms(2);    
}
void lcd_print_char(uint8_t data)
{
    //For data, RS must be high
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RS, HIGH);
    
    //Set RW to write 
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RW, LOW);
    
    //send upper nibble 
    send_4_bits((data >> 4));
    
    //send lower nibble 
    send_4_bits((data & 0x0F));
    
    //wait until BF is clear 
   //while(read_bf());
    
}
void lcd_set_cursor_xy(uint8_t row, uint8_t column)
{
    column--;
    if(row == 1)
    {
        //for the first row, the starting position address is 0 and the command is 0x80
        send_cmd((column | 0x80));
    }
    else if(row == 2)
    {
        //for the sencond row the sarting address is 0x40 (0x40 + 0x80 = 0xC0);
        send_cmd((column | 0xC0));
    }
    
}
void lcd_print_string(char *string)
{
    while(*string != '\0')
    {
        lcd_print_char((uint8_t)*string);
        string++;
    }
}

static void send_cmd(uint8_t cmd)
{
    //For commands, RS must be low 
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RS, LOW);
    
    //Set RW to write 
    gpio_write_digital_pin(LCD_CMD_PORT,LCD_RW, LOW);
    
    //send upper nibble 
    send_4_bits((cmd >> 4));
    
    //send lower nibble 
    send_4_bits((cmd & 0x0F));
    
    //wait until BF is clear 
   //while(read_bf());
}

static void send_4_bits(uint8_t data)
{

    
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB4, ((data >> 0) & 0x1));
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB5, ((data >> 1) & 0x1));
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB6, ((data >> 2) & 0x1));
    gpio_write_digital_pin(LCD_DATA_PORT, LCD_DB7, ((data >> 3) & 0x1));
    


    lcd_enable();
} 

#if 0

static uint8_t read_bf()
{
    //Set RS for DR 
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RS, HIGH);
    
    //Set RW to read 
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_RW, HIGH);
    
    uint8_t bf_status = gpio_read_digital_pin(LCD_DATA_PORT, LCD_DB7);
    
    lcd_enable();
    return bf_status;
}

#endif

static void lcd_enable()
{
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_EN, HIGH);
    _delay_us(10);
    
    gpio_write_digital_pin(LCD_CMD_PORT, LCD_EN, LOW);
    _delay_us(50);
}