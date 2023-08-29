/*
 * timer1.c
 *
 *  Created on: May 11, 2023
 *      Author: Shawky
 */

#include "Timer1.h"


static void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	switch(Config_Ptr -> mode)
	{
	case NORMAL_MODE: TCCR1A = (1<<FOC1A) | (1<<FOC1B);
					  TCCR1B = 0;
					  TIMSK |= (1<<TOIE1);						    break;
	case CTC_MODE: 	  TCCR1A = (1<<FOC1A) | (1<<FOC1B);
					  TCCR1B = (1<<WGM12);
					  TIMSK |= (1<<OCIE1A);							break;
	default:                                                        break;
	}

	switch(Config_Ptr -> prescaler)
	{
	case NO_CLK: 	TCCR1B = (TCCR1B & 0xF8) | NO_CLK;				break;
	case F_CPU_CLK: TCCR1B = (TCCR1B & 0xF8) | F_CPU_CLK;			break;
	case F_CPU8:	TCCR1B = (TCCR1B & 0xF8) | F_CPU8;				break;
	case F_CPU64:	TCCR1B = (TCCR1B & 0xF8) | F_CPU64;				break;
	case F_CPU256:  TCCR1B = (TCCR1B & 0xF8) | F_CPU256;			break;
	case F_CPU1024: TCCR1B = (TCCR1B & 0xF8) | F_CPU1024;			break;
	default:                                                        break;
	}

	TCNT1 = Config_Ptr -> initial_value;
	OCR1A = Config_Ptr -> compare_value;
}

void Timer1_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	CLEAR_BIT(TIMSK,TOIE1);
	CLEAR_BIT(TIMSK,OCIE1A);
	TCNT1 = 0;
	OCR1A = 0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
