/*!
 *  \file    main.c
 *  \author  Patrick Taling 
 *  \date    20/04/2017
 *  \version 1.0
 *
 *  \brief
 *		Simple function to read two Sensirion Humidity and Temperature sensors with the same I2C ADRESS through a TCA9548A I2C Switch
 *		Rights are owned by the original authors (Atmel, w.e.dolman, Noel200 (Elektroda), Sensirion and Texas Instruments/ Adafruit)
 *
 *	\Hardware
 *		# 1602 I2c HD44780 LCD from HobbyElectronica https://www.hobbyelectronica.nl/product/1602-lcd-i2c-blauw-backlight/
 *		# HvA Xmega-bord (ATxmega256a3u with programmer/ USB-RS232-interface ATxmega32a4u)
 *		# 3.3V - 5V levelshifter with two BS170 N-channel MOSFET
 *		# Two Humidity/ temperature sensor module (EBM016) https://www.elektor.nl/humidity-sensor-module-ebm016
 *		# TCA9548A I2C Multiplexer (Adafruit) from https://www.hobbyelectronica.nl/product/tca9548a-i2c-multiplexer/?gclid=CKOCppyXrtMCFQiNGwodOc8EsQ
 *
 *	\development
 *		# Atmel Studio 7 (version: 7.0.118)
 *		# OS Version: Microsoft Windows NT 6.2.9200.0 (Platform: Win32NT)
 *		# Atmel Gallary (7.8)
 *
 *  \details 
 *		#The file main.c is the main to write text to a I2C lcd (PCF8574T adress 0x27) with the ATxmega256a3u.
 *		#For the use of the main code you need the i2c library from w.e.dolman (<a href="mailto:w.e.dolman@hva.nl">w.e.dolman@hva.nl</a>)
 *		#For i2c.c use code 21.8 from "de taal C en de Xmega tweede druk" http://dolman-wim.nl/xmega/book/index.php
 *		#For i2c.h use code 21.9 from "de taal C en de Xmega tweede druk" http://dolman-wim.nl/xmega/book/index.php
 *     
 *		#The library code needs some parts of the i2c_lcd library from Noel200 from http://www.elektroda.pl/rtvforum/topic2756081.html. 
 *		#The library can be downloaded from: http://www.elektroda.pl/rtvforum/login.php?redirect=download.php&id=670533.
 *		#Go to LCD_PCF8574T/lcd_pcf/ and use i2c_lcd.c and i2c_lcd.h from the pakkage
 *
 *		#The library needs some parts of the the SHT2x library from SENIRION from https://www.sensirion.com/en/products/humidity-sensors/humidity-temperature-sensor-sht2x-digital-i2c-accurate/
 *		#The library can be download from: https://www.sensirion.com/en/products/all-documents-of-sensirions-humidity-sensors-for-download/
 *		# Go to SHT2x/ Sample Code SHT21 and download the zip file Sensirion_Humidity_Sensors_SHT21_Sample_Code_C-file
 *		\note	the following files aren't fully used. Most parts are used in other .c of .h files or disabled.
 *			DisplayDip204.C, DisplayDip204.h,
 *			I2C_HAL.c, I2C_HAL.h,
 *			System.c, System.h and
 *			io70f3740.h.
 *		\note for the use of two SHT2X you should use different IOs for SDA or additional hardware such as I2C multiplexer/ switch.
 *			The adress of the SHT2x can’t be changed.
 *
 *		#For the Adafruit TCA9548A I2C Switch you can use information from Adafruit https://learn.adafruit.com/adafruit-tca9548a-1-to-8-i2c-multiplexer-breakout/overview
 *		#To understand the library you needs some understanding of the device TCA9548A of Texas Instruments
 *		#To understand the library you needs some understanding of I2C protocol for the TCA9548A of Texas Instruments
 *
 * \verbatim
 *		#include <i2c_lcd.h>
 *		#include <I2C_SHT2x.h>
   \endverbatim
 *           \par
 *
 *           \note An AVR-project can use multiple I2C's. One shoud take care that
 *           in different source files there are no multiple i2c_init
 *           definitions for the same I2C.
 */

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD_100K	100000UL
#include "i2c_lcd.h"
#include "I2C_SHT2x.h"

volatile float Temperature = 0;
volatile float Humidity = 0;

#define CHANNEL_0	0
#define CHANNEL_1	1
#define CHANNEL_2	2
#define CHANNEL_3	3
#define CHANNEL_4	4
#define CHANNEL_5	5
#define CHANNEL_6	6
#define CHANNEL_7	7

int main(void)
{

	i2c_init(&TWIE, TWI_BAUD(F_CPU, BAUD_100K));
	PORTE.DIRSET = PIN1_bm|PIN0_bm; //SDA 0 SCL 1
	i2c_lcd_init();
	i2c_lcd_led_on();
	i2c_lcd_set_cursor(0,0);

	while(1)
	{
		i2c_lcd_clear();
		_delay_us(1500);
		Sht2x_Temperature_Humidity(CHANNEL_0);
		_delay_ms(5000);
		Sht2x_Temperature_Humidity(CHANNEL_1);
		_delay_ms(5000);
	}
}