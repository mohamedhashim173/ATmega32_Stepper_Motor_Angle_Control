/*
 * STEPPER_config.h
 *
 *  Created on: Oct 19, 2022
 *      Author: MSAEED99
 */

#ifndef STEPPER_CONFIG_H_
#define STEPPER_CONFIG_H_


#define STEPPER_PORT			DIO_u8PORTB

#define STEPPER_COIL1_PINK__	DIO_u8PIN0
#define STEPPER_COIL2_BLUE__	DIO_u8PIN1
#define STEPPER_COIL3_ORANGE	DIO_u8PIN2
#define STEPPER_COIL4_YELLOW	DIO_u8PIN3

#define BUZZER_PORT				DIO_u8PORTD
#define BUZZER_PIN				DIO_u8PIN7

#define DELAY					2000
#define BLINK_COUNTER_MAX		50


#endif /* STEPPER_CONFIG_H_ */

