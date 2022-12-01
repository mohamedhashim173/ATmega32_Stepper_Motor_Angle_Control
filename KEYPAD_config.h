/*
 * Keypad_config.h
 *
 *  Created on: Oct 7, 2022
 *      Author: MSAEED99
 */


#ifndef KEYPAD_CONFIG_H_
#define KEYPAD_CONFIG_H_


#define KEYPAD_PORT				DIO_u8PORTA

#define KEY_PAD_COLUMN0_PIN		DIO_u8PIN0
#define KEY_PAD_COLUMN1_PIN		DIO_u8PIN1
#define KEY_PAD_COLUMN2_PIN		DIO_u8PIN2
#define KEY_PAD_COLUMN3_PIN		DIO_u8PIN3

#define KEY_PAD_ROW0_PIN		DIO_u8PIN4
#define KEY_PAD_ROW1_PIN		DIO_u8PIN5
#define KEY_PAD_ROW2_PIN		DIO_u8PIN6
#define KEY_PAD_ROW3_PIN		DIO_u8PIN7


#define KEYPAD_DEFAULT_KEY		0xFF

#define KEYPAD_ARR_VAL			{{'7' ,'8' , '9', '-'}, {'1', '2', '3', '6'}, {'4', '5', '6', 0}, {'c', '0', '=', 0}}



#endif /* KEYPAD_CONFIG_H_ */

