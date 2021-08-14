/*
 * lcd_driver.h
 *
 * Created: 11/08/2021 20:16:14
 *  Author: Nico
 */ 


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "atmega328.h"

//List of commands 
#define LCD_CLEAR_DISP  0x01
#define LCD_RETURN_HOME 0x02
#define LCD_NO_SHIFT    0x04
#define LCD_BLINK_CUR   0x0F
#define LCD_NO_CURS     0x0C
#define LCD_ENTRY_MODE  0x06
#define LCD_SET_FUNC    0x28 //4-bit data transmission, 2 display lines and font 5x8


//Pin definition 
//Pins for the RS, R/W and E line use PORT B
#define LCD_CMD_PORT PORTB
#define LCD_RS      1
#define LCD_RW      2
#define LCD_EN      3
//Pins DB4-DB7 use PORT C 
#define LCD_DATA_PORT PORTC
#define LCD_DB4     0 
#define LCD_DB5     1
#define LCD_DB6     2
#define LCD_DB7     3

void lcd_init();
void lcd_clear();
void lcd_print_char(uint8_t data);
void lcd_set_cursor_xy(uint8_t row, uint8_t column);
void lcd_print_string(char *string);


#endif /* LCD_DRIVER_H_ */