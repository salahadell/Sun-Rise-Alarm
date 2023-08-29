/*
 * buzzer.c
 *
 *  Created on: May 11, 2023
 *      Author: Shawky
 */

#include "std_types.h"
#include "common_macros.h"
#include "gpio.h"

void Buzzer_init(void)
{
	DIO_SetPinDir(DIO_PORTC , DIO_PIN6 , DIO_PIN_OUTPUT);
	DIO_SetPinVal(DIO_PORTC , DIO_PIN6 , LOGIC_LOW);
}

void Buzzer_on(void)
{
	DIO_SetPinVal(DIO_PORTC , DIO_PIN6 , LOGIC_HIGH);
}

void Buzzer_off(void)
{
	DIO_SetPinVal(DIO_PORTC , DIO_PIN6 , LOGIC_LOW);
}
