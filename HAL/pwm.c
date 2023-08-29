/*
 * main.c
 *
 *  Created on: Aug 27, 2023
 *      Author: Shawky
 */

#include "pwm.h"

void PwmInit(void)
{
	DIO_SetPinDir(DIO_PORTB,DIO_PIN3 , DIO_PIN_OUTPUT);
	TCCR0 = 0xFB;
	TCNT0 = 0;
}

void PwmSetDutyCycle(uint8 dutycycle)
{
	OCR0 = dutycycle;
}


void PwmDenit(void)
{
	TCCR0 = 0;
	TCNT0 = 0;
}


