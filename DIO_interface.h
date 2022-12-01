/*
 * DIO_interface.h
 *
 *  Created on: Sep 24, 2022
 *      Author: Mohamed Hashim Attiya Said
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

// Set as input or output
void DIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8PinDirection);
void DIO_voidSetPortDirection(u8 copy_u8Port, u8 copy_u8PortDirection);

// Set output value
void DIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8PinValue);
void DIO_voidSetPortValue(u8 copy_u8Port, u8 copy_u8PortValue);

// Read input value
u8 DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin);



// input arguments macros for functions that will be used instead of magic numbers

// Ports Naming
#define DIO_u8PORTA		0
#define DIO_u8PORTB		1
#define DIO_u8PORTC		2
#define DIO_u8PORTD		3

// Pins Naming
#define DIO_u8PIN0		0
#define DIO_u8PIN1		1
#define DIO_u8PIN2		2
#define DIO_u8PIN3		3
#define DIO_u8PIN4		4
#define DIO_u8PIN5		5
#define DIO_u8PIN6		6
#define DIO_u8PIN7		7

// Direction Naming for Pin
#define DIO_u8PIN_INPUT		0
#define DIO_u8PIN_OUTPUT	1
// Direction Naming for Port
#define DIO_u8PORT_INPUT	0x00
#define DIO_u8PORT_OUTPUT	0xFF


// Pin Value Naming for Pin
#define DIO_u8PIN_LOW		0
#define DIO_u8PIN_HIGH		1
// Pin Value Naming for Port
#define DIO_u8PORT_LOW		0x00
#define DIO_u8PORT_HIGH		0xFF



#endif /* DIO_INTERFACE_H_ */






