/*
 * STEPPER_program.c
 *
 *  Created on: Oct 19, 2022
 *      Author: MSAEED99
 */


// AVR libraries
#include <util/delay.h>

// Libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"

// HAL
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "STEPPER_config.h"
#include "STEPPER_interface.h"


// Global Variables
s8 input[10] = {0};
s16 angle;
s8 sign = 1;

u8 edit_mode = 1;
u8 run_mode = 0;

u8 _index = 0;
u8 num_of_digits = 0;
u32 digit_counter;
u32 blink_counter;



// Rotate clockwise
void stepper_motor_CW(void)
{
	blink_counter = 0;

	s16 counter = -1 * 512.0 * angle / 360;

	// Print Direction
	LCD_voidPositionSet(1, 0);
	LCD_voidSendString("Clockwise");

	// Hide Courser
	LCD_voidPositionSet(0, 20);

	DIO_voidSetPortDirection(STEPPER_PORT, DIO_u8PORT_OUTPUT);

	// Clockwise rotation: Pink > Blue > Orange > Yellow
	for(s32 i = 0; i < counter; i++)
	{
		// Step 1 (Coil 1)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);
		_delay_ms(2);

		// Step 2 (Coil 2)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);
		_delay_ms(2);

		// Step 3 (Coil 3)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);
		_delay_ms(2);

		// Step 4 (Coil 4)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_HIGH);
		_delay_ms(2);

		// Blink Buzzer
		buzzer_blink();
	}

	// Stepper Motor OFF
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);

	// Reset Blink Buzzer counter
	DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_LOW);
}


// Rotate counter clockwise
void stepper_motor_CCW(void)
{
	blink_counter = 0;

	s16 counter = 512.0 * angle / 360;

	// Print Direction
	LCD_voidPositionSet(1, 0);
	LCD_voidSendString("Anti-Clockwise");

	// Hide Courser
	LCD_voidPositionSet(0, 20);


	DIO_voidSetPortDirection(STEPPER_PORT, DIO_u8PORT_OUTPUT);

	// Clockwise rotation: Yellow > Orange > Blue > Pink
	for(s16 i = 0; i < counter; i++)
	{
		// Step 4 (Coil 4)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_HIGH);
		_delay_ms(2);

		// Step 3 (Coil 3)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);
		_delay_ms(2);

		// Step 2 (Coil 2)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);
		_delay_ms(2);

		// Step 1 (Coil 1)
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_HIGH);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
		DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);
		_delay_ms(2);

		// Blink Buzzer
		buzzer_blink();
	}

	// Stepper Motor OFF
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL1_PINK__, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL2_BLUE__, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL3_ORANGE, DIO_u8PIN_LOW);
	DIO_voidSetPinValue(STEPPER_PORT, STEPPER_COIL4_YELLOW, DIO_u8PIN_LOW);

	// Reset Blink Buzzer counter
	DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_LOW);
}



// Calculate input value of the angle
void save_angle_value(void)
{
	// Save input to Angle variable
	digit_counter = 1;
	angle = 0;

	for(s8 i = num_of_digits - 1; i >= 0; i--)
	{
		angle += input[i] * digit_counter;
		digit_counter *= 10;
	}

	angle *= sign;
}



// Clear input memories
void reset_input(void)
{
	edit_mode = 1;
	run_mode = 0;

	_index = 0;
	num_of_digits = 0;
	sign = 1;

	for(s8 i = 0; i < 10; i++)
	{
		input[i] = 0;
	}

	// Clear LCD
	LCD_voidInit();

	// Angle input message
	LCD_voidSendString("Angle=");
}


// Blink buzzer (beep beep beep)
void buzzer_blink(void)
{
	DIO_voidSetPinDirection(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_OUTPUT);
	// ON
	if(blink_counter <  BLINK_COUNTER_MAX / 2)
	{
		DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_HIGH);
	}
	// OFF
	else
	{
		DIO_voidSetPinValue(BUZZER_PORT, BUZZER_PIN, DIO_u8PIN_LOW);
	}

	// Reset Blink Buzzer counter
	if(blink_counter > BLINK_COUNTER_MAX)
	{
		blink_counter = 0;
	}

	blink_counter++;
}

