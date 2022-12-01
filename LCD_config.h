/*
 * LCD_config.h
 *
 *  Created on: Sep 30, 2022
 *      Author: Mohamed Hashim Attiya Said
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


// LCD control port
#define LCD_CONTROL_PORT	DIO_u8PORTD

// LCD data port
#define LCD_DATA_PORT		DIO_u8PORTC

// LCD register select pin
#define LCD_RS_PIN			DIO_u8PIN0
// LCD read/write pin
#define LCD_RW_PIN			DIO_u8PIN1
// LCD enable pin
#define LCD_E_PIN			DIO_u8PIN2



#endif /* LCD_CONFIG_H_ */
