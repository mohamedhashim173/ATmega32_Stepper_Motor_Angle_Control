/*
 * STEPPER_interface.h
 *
 *  Created on: Oct 19, 2022
 *      Author: MSAEED99
 */

#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_

// Rotate clockwise
void stepper_motor_CW(void);

// Rotate counter clockwise
void stepper_motor_CCW(void);

// Calculate input value of the angle
void save_angle_value(void);

// Clear input memories
void reset_input(void);

// Blink buzzer (beep beep beep)
void buzzer_blink(void);


#endif /* STEPPER_INTERFACE_H_ */

