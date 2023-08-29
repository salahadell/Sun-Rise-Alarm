/*
 * App_Cnfg.c
 *
 *  Created on: Aug 28, 2023
 *      Author: Shawky
 */

#include "App_Cfg.h"

void Start_timer1(void)
{
	Timer1_ConfigType* timer_configurations = 0;
	/*	configure timer parameters using pre-defined values	*/
	timer_configurations->compare_value = COMPARE_VALUE_TIMER1;
	timer_configurations->mode = TIMER1_MODE;
	timer_configurations->prescaler = PRESCALER_VALUE_TIMER1;

	Timer1_init(timer_configurations);	/*	initialise timer and start counting a 1 sec delay	*/
}

void Stop_timer1(void)
{
	Timer1_deInit();	/*	stop timer1 by removing clock source	*/
}

void Start_timer0(void)
{
	Timer0_ConfigType* timer_configurations = 0;
	/*	configure timer parameters using pre-defined values	*/
	timer_configurations->compare_value = COMPARE_VALUE_TIMER0;
	timer_configurations->mode = TIMER0_MODE;
	timer_configurations->prescaler = PRESCALER_VALUE_TIMER0;

	Timer0_init(timer_configurations);	/*	initialise timer and start counting a 1 sec delay	*/
}

void Stop_timer0(void)
{
	Timer0_deInit();	/*	stop timer1 by removing clock source	*/
}

void Diming(void)
{
	uint8 i;
	DIO_SetPinDir(DIO_PORTB,DIO_PIN3 , DIO_PIN_OUTPUT);
	for(i=0;i<254;i++)
	{
		PwmSetDutyCycle(i);
		_delay_ms(10);
	}
	_delay_ms(10);
	for(i=255;i>0;i--)
	{
		PwmSetDutyCycle(i);
		_delay_ms(10);
	}
	DIO_SetPinDir(DIO_PORTB,DIO_PIN3 , DIO_PIN_INPUT);
}



