/*
 * Keypad1.h
 *
 *  Created on: Aug 19, 2023
 *      Author: Shawky
 */

#ifndef KEYPAD1_H_
#define KEYPAD1_H_

#include "common_macros.h"
#include "GPIO.h"

#define KEYPAD_COLUMN_PORT				DIO_PORTD
#define	KEYPAD_ROW_PORT					DIO_PORTC


#define KEYPAD_COLUMN0					DIO_PIN7
#define KEYPAD_COLUMN1					DIO_PIN6
#define KEYPAD_COLUMN2					DIO_PIN5
#define KEYPAD_COLUMN3					DIO_PIN3


#define KEYPAD_ROW0						DIO_PIN5
#define KEYPAD_ROW1						DIO_PIN4
#define KEYPAD_ROW2						DIO_PIN3
#define KEYPAD_ROW3						DIO_PIN2

uint8 KeyPad_GetValue(void);

void Keypad_init(void);



#endif /* KEYPAD1_H_ */
