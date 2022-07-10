#define F_CPU 16000000UL
//#define AVR_USE_HW_I2C
#define SSD1306_ADDR 0x78
#include<stdio.h>
#include<stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/power.h>
#include <u8g2.h>
#include <u8x8_avr.h>

void main(void){

	int counter = 0;
	char * message = malloc(sizeof(char)*4);
	//setup pin 10 as output
	DDRB |= (1 << 2);

	//setup i2c oled
	u8g2_t u8g2;
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_avr_hw_i2c, u8x8_avr_delay);
	u8g2_SetI2CAddress(&u8g2, SSD1306_ADDR);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);

	//write on screen
	u8g2_ClearBuffer(&u8g2);
	u8g2_SendBuffer(&u8g2);
	u8g2_SetFont(&u8g2, u8g2_font_ncenB14_tr);
	u8g2_SetFontRefHeightText(&u8g2);

	u8g2_SetFontPosTop(&u8g2);
	while(1){
		u8g2_ClearBuffer(&u8g2);
		PORTB |=  (1 << 2);
		_delay_ms(500);
		PORTB &=  ~(1 << 2);
		_delay_ms(500);

		if(counter >= 100)
			counter =0;
		sprintf(message,"%d",counter);
		u8g2_DrawStr(&u8g2, 0, 0, message);
		u8g2_SendBuffer(&u8g2);
		counter++;

	}

}

