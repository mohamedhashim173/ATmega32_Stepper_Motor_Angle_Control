/*
 * DIO_program.c
 *
 *  Created on: Sep 24, 2022
 *      Author: Mohamed Hashim Attiya Said
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_register.h"
#include "DIO_config.h"
#include "DIO_private.h"


// Set as input or output for a pin
void DIO_voidSetPinDirection(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8PinDirection)
{
	if (copy_u8PinDirection == DIO_u8PIN_INPUT)
	{
		switch(copy_u8Port)
		{
		case DIO_u8PORTA: CLR_BIT(DDRA, copy_u8Pin); break;
		case DIO_u8PORTB: CLR_BIT(DDRB, copy_u8Pin); break;
		case DIO_u8PORTC: CLR_BIT(DDRC, copy_u8Pin); break;
		case DIO_u8PORTD: CLR_BIT(DDRD, copy_u8Pin); break;
		}
	}
	else if(copy_u8PinDirection == DIO_u8PIN_OUTPUT)
	{
		switch(copy_u8Port)
		{
		case DIO_u8PORTA: SET_BIT(DDRA, copy_u8Pin); break;
		case DIO_u8PORTB: SET_BIT(DDRB, copy_u8Pin); break;
		case DIO_u8PORTC: SET_BIT(DDRC, copy_u8Pin); break;
		case DIO_u8PORTD: SET_BIT(DDRD, copy_u8Pin); break;
		}
	}
	else
	{
		// empty else according to MISRA Rules
	}
}


// Set as input or output for the whole port
void DIO_voidSetPortDirection(u8 copy_u8Port, u8 copy_u8PortDirection)
{
	switch(copy_u8Port)
	{
	case DIO_u8PORTA: DDRA = copy_u8PortDirection; break;
	case DIO_u8PORTB: DDRB = copy_u8PortDirection; break;
	case DIO_u8PORTC: DDRC = copy_u8PortDirection; break;
	case DIO_u8PORTD: DDRD = copy_u8PortDirection; break;
	}
}


// Set output value for a pin
void DIO_voidSetPinValue(u8 copy_u8Port, u8 copy_u8Pin, u8 copy_u8PinValue)
{
	if (copy_u8PinValue == DIO_u8PIN_LOW)
	{
		switch(copy_u8Port)
		{
		case DIO_u8PORTA: CLR_BIT(PORTA, copy_u8Pin); break;
		case DIO_u8PORTB: CLR_BIT(PORTB, copy_u8Pin); break;
		case DIO_u8PORTC: CLR_BIT(PORTC, copy_u8Pin); break;
		case DIO_u8PORTD: CLR_BIT(PORTD, copy_u8Pin); break;
		}
	}
	else if(copy_u8PinValue == DIO_u8PIN_HIGH)
	{
		switch(copy_u8Port)
		{
		case DIO_u8PORTA: SET_BIT(PORTA, copy_u8Pin); break;
		case DIO_u8PORTB: SET_BIT(PORTB, copy_u8Pin); break;
		case DIO_u8PORTC: SET_BIT(PORTC, copy_u8Pin); break;
		case DIO_u8PORTD: SET_BIT(PORTD, copy_u8Pin); break;
		}
	}
	else
	{
		// empty else according to MISRA Rules
	}
}

// Set output value for a whole port
void DIO_voidSetPortValue(u8 copy_u8Port, u8 copy_u8PortValue)
{
	switch(copy_u8Port)
	{
	case DIO_u8PORTA: PORTA = copy_u8PortValue; break;
	case DIO_u8PORTB: PORTB = copy_u8PortValue; break;
	case DIO_u8PORTC: PORTC = copy_u8PortValue; break;
	case DIO_u8PORTD: PORTD = copy_u8PortValue; break;
	}
}


// Read input value from a pin
u8 DIO_u8GetPinValue(u8 copy_u8Port, u8 copy_u8Pin)
{
	u8 local_u8Pin_Val = 0;
	switch(copy_u8Port)
	{
	case DIO_u8PORTA: local_u8Pin_Val = GET_BIT(PINA, copy_u8Pin); break;
	case DIO_u8PORTB: local_u8Pin_Val = GET_BIT(PINB, copy_u8Pin); break;
	case DIO_u8PORTC: local_u8Pin_Val = GET_BIT(PINC, copy_u8Pin); break;
	case DIO_u8PORTD: local_u8Pin_Val = GET_BIT(PIND, copy_u8Pin); break;
	}
	return local_u8Pin_Val;
}













