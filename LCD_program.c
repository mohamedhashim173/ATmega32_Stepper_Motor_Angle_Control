/*
 * LCD_program.c
 *
 *  Created on: Sep 30, 2022
 *      Author: Mohamed Hashim Attiya Said
 */

// libraries
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

// MCAL
#include "DIO_interface.h"

// HAL
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"


// initiate LCD (see LCD Initialization in LCD data sheet)
void LCD_voidInit(void)
{
	// Set port as output
	DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_u8PORT_OUTPUT);

	// Set control pins as output
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8PIN_OUTPUT);

	// wait more than 30ms (from data sheet)
	_delay_ms(40);

	// Initialize LCD configurations with: 0b0011NFXX
	// N: Number of lines (0: one line, 1: two lines)
	// F: Font size (0: 5*8, 1: 5*11)
	// X: Don't care
	LCD_voidSendCommand(0b00111000);

	// Display ON/OFF control: 0b00001DCB
	// D: Display(0: OFF, 1: ON)
	// C: Cursor (0: Disable, 1: Enable)
	// B: Cursor Blink (0: Disable, 1: Enable)
	LCD_voidSendCommand(0b00001100);

	// Clear the display
	LCD_voidSendCommand(0b00000001);
}


void LCD_voidSendCommand(u8 copy_u8Command)
{
	// To send command, Set RS pin as output LOW (0: Send Command, 1: Send Data)
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8PIN_LOW);

	// Enable write mode, Set RW pin as output low (0: Write, 1: Read)
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8PIN_LOW);

	// Set the data port to send the command
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Command);

	// Enable pulse (write data at the falling edge of E)
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);		// wait 2ms till the LCD initializes
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8PIN_LOW);
}


// print character (argument in single quotes 'a')
void LCD_voidSendCharacter(u8 copy_u8Character)
{
	// To send Data, Set RS pin as output HIGH (0: Send Command, 1: Send Data)
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RS_PIN, DIO_u8PIN_HIGH);

	// Enable write mode, Set RW pin as output low (0: Write, 1: Read)
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_RW_PIN, DIO_u8PIN_LOW);

	// Set the data port to send the character
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Character);

	// Enable pulse (write data at the falling edge of E)
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8PIN_HIGH);
	_delay_ms(2);		// wait 2ms till the LCD initializes
	DIO_voidSetPinValue(LCD_CONTROL_PORT, LCD_E_PIN, DIO_u8PIN_LOW);
}


// String to display (input argument is a pointer to the beginning of the string
void LCD_voidSendString(char* copy_pcString)
{
	while(*copy_pcString != '\0')
	{
		LCD_voidSendCharacter(*copy_pcString);
		copy_pcString++;
	}
}


void LCD_voidWriteNum(u32 copy_u32Number)
{
	u8 firstDigit = 0;
	for(u32 i = 1000000000; i > 0; i /= 10)
	{
		if(copy_u32Number / i > 0)
		{
			LCD_voidSendCharacter(copy_u32Number / i + 48);
			copy_u32Number %= i;
			firstDigit = 1;
		}
		// Print 0 after the 1st digit
		else if(firstDigit == 1)
		{
			LCD_voidSendCharacter(48);
		}
	}
}


// Control the position of the printed characters
void LCD_voidPositionSet(u8 copy_u8RowNum, u8 copy_u8ColNum)
{
	u8 local_u8Address;

	// Check on row #
	if(copy_u8RowNum == 0)
	{
		// address for the 1st row
		local_u8Address = copy_u8ColNum;
	}
	else if (copy_u8RowNum == 1)
	{
		// address for the 2nd row
		local_u8Address = copy_u8ColNum + 0x40;
	}

	// send the position command to DDRAM, and add 128 to set the MSB to 1 (see data sheet)
	LCD_voidSendCommand(local_u8Address + 128);
}


// Draw special character
void LCD_voidDrawSpecialCharacter(u8* copy_pu8Pattern, u8 copy_u8LocationNum, u8 copy_u8RowNum, u8 copy_u8ColNum)
{
	u8 local_u8CGRAMaddr;

	// Calculate CGRAM address location. Each location is 8-Byte size
	local_u8CGRAMaddr = copy_u8LocationNum * 8;

	// Accessing CGRAM of LCD, and add 64 to set 00100000 (see data sheet)
	LCD_voidSendCommand(local_u8CGRAMaddr + 64);

	// Write the pattern on CGRAM
	for(s8 i = 0; i < 8; i++)
	{
		LCD_voidSendCharacter(copy_pu8Pattern[i]);
	}

	// Send the pattern to DDRAM to be displayed
	LCD_voidPositionSet(copy_u8RowNum, copy_u8ColNum);

	// Display the pattern
	LCD_voidSendCharacter(copy_u8LocationNum);
}


