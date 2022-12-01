/*
 * main.c
 *
 *  Created on: Oct 18, 2022
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
extern s8 input[10];
extern s16 angle;
extern s8 sign;
extern u8 edit_mode;
extern u8 _index;
extern u8 num_of_digits;

// Local variables
u8 local_u8PressedKey;



/*
 * Stepper Motor Angle Control
 * Energizing Stepper Motor coils by MCU output port via interfacing with Darlington Pair (ULN2003).
 * Keypad driver is configured to enter the desired angle of rotation.
 * LCD driver is configured as a visual interfacing to display the entered value of rotation and motion info.
 */


void main(void)
{

	// LCD and Keypad Initialization
	LCD_voidInit();
	KEYPAD_voidPinInit();

	// Angle input message
	LCD_voidSendString("Angle=");


	while(1)
	{
		// Store pressed key
		local_u8PressedKey = KEYPAD_u8GetPressedKey();



		// ====================================================
		// Edit Mode
		// ====================================================
		if(1 == edit_mode)
		{
			// Input angle of rotation
			if(local_u8PressedKey >= '0'  && local_u8PressedKey <= '9')
			{
				// Print on LCD
				LCD_voidSendCharacter(local_u8PressedKey);

				// Store in input array
				input[_index] = local_u8PressedKey - '0';
				_index++;
				num_of_digits++;
			}

			// Accept negative value
			if('-' == local_u8PressedKey)
			{
				sign *= -1;

				// Print on LCD
				LCD_voidSendCharacter(local_u8PressedKey);
			}
		}



		// ====================================================
		// Run Mode
		// ====================================================

		// Rotate Stepper Motor with the entered value
		if('=' == local_u8PressedKey)
		{
			// Disable Edit Mode
			edit_mode = 0;

			// Calculate input angle
			save_angle_value();

			// Rotate Stepper Motor
			if(angle > 360 || angle < -360)
			{
				LCD_voidPositionSet(0, 0);
				LCD_voidSendString(" Invalid angle! ");
				LCD_voidPositionSet(1, 0);
				LCD_voidSendString("-360< Angle <360");

				// Hide Courser
				LCD_voidPositionSet(0, 20);

				_delay_ms(DELAY);
			}
			else
			{
				if(angle > 0)
				{
					stepper_motor_CCW();
				}
				else  if(angle < 0)
				{
					stepper_motor_CW();
				}

				// Feedback message
				LCD_voidPositionSet(0, 0);
				LCD_voidSendString("Rotated by ");
				LCD_voidWriteNum(angle);

				// Degree symbol
				LCD_voidSendCharacter(0b11011111);

				// Clear row 2
				LCD_voidPositionSet(1, 0);
				LCD_voidSendString("                ");

				// Hide Courser
				LCD_voidPositionSet(0, 20);

				_delay_ms(DELAY);
			}

			// Clear for new input
			reset_input();
		}


		// ====================================================
		// Clear LCD
		// ====================================================

		if('c' == local_u8PressedKey)
		{
			// Clear memories
			reset_input();
		}
	}
}





