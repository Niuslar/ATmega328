# Simple Makefile to compile and upload these drivers. 
# Note: This is a VERY simple file

#To use it: 
#   First make a 'build' subfolder (mkdir build)
#Then you can use: 
# 	make -> compiles main.c with all the dependencies 
#   make install -> uploads code to microcontroller
#   make clean -> removes all the files 

INC = ./Drivers/Inc
SRC = Drivers/Src

#AVR GCC OPTIONS
MCU = atmega328p
CFLAGS = -c -I $(INC) -mmcu=$(MCU) -Os
OBJ=twi_driver.o gpio_driver.o spi_driver.o lcd_driver.o aht10_driver.o timers.o
OBJCOPY = avr-objcopy
CC = avr-gcc

# AVR DUDE OPTIONS 
ISP = stk500v1
BAUD_RATE = 19200
CURR_DIR = $(shell pwd)
CONF_FILE = ~/Desktop/arduino-1.8.16/hardware/tools/avr/etc/avrdude.conf
AVR_MCU = m328p
PORT = /dev/ttyACM0

all: main.hex

# Convert binary to hex 
main.hex : main.out
	$(OBJCOPY) -O ihex -j .text -j .data build/main.out build/main.hex

#Link all the object files 
main.out : $(OBJ) main.o
	$(CC) -mmcu=$(MCU) -o build/main.out build/main.o $(addprefix build/, $(OBJ))

#Compile main.c 
main.o : main.c
	$(CC) $(CFLAGS) -o build/main.o main.c

#Compile source files (except main.c) 
$(OBJ) : %.o : $(SRC)/%.c
	$(CC) $(CFLAGS) $< -o build/$@

#Upload code to microcontroller 
install: 
	avrdude -C $(CONF_FILE) -p $(AVR_MCU) -c $(ISP) -b $(BAUD_RATE)\
	 -P $(PORT) -U flash:w:"$(CURR_DIR)/build/main.hex":i

.PHONY = clean 
clean: 
	rm $(addprefix build/, $(OBJ))
	rm build/main.out
	rm build/main.o
	rm build/main.hex
