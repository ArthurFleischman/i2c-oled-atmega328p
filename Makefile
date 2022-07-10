CC=avr-gcc
CFLAGS= -Os -DF_CPU=16000000UL -mmcu=atmega328p
OBJCPY = avr-objcopy
SIZE = avr-size
MCU=m328p
PROG=usbasp
EFUSE= -U efuse:w:0xFA:m
LFUSE= -U lfuse:w:0x62:m
HFUSE= -U hfuse:w:0xD9:m

all: main.out

%.out: %.c
	$(CC) $(CFLAGS) $(OBJ) $< -o $@

%.hex: %.out
	avr-objcopy -O ihex -R .eeprom $< $@

install.%: %.hex
	avrdude -V -c $(PROG) -p $(MCU) -b 115200 -U flash:w:$< 

clean:
	rm -f *.hex *.out

