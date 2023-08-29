/*
 * Timer0.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Shawky
 */


#include "Timer0.h"

static void (*g_callBackPtr)(void) = NULL_PTR;

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

void Timer0_init(const Timer0_ConfigType * Config_Ptr)
{
	switch(Config_Ptr -> mode)
	{
	case NORMAL_MODE_TIMER0: TCCR0 = (1<<FOC0);
					  TIMSK |= (1<<TOIE0);							break;


	case CTC_MODE_TIMER0: 	  TCCR0 = (1<<FOC0) | (1<<WGM01);
					  TIMSK |= (1<<OCIE0);							break;
    default:                                                        break;
	}

	switch(Config_Ptr -> prescaler)
	{
	case NO_CLK_TIMER0: 	TCCR0 = (TCCR0 & 0xF8) | NO_CLK_TIMER0;					break;
	case F_CPU_CLK_TIMER0:  TCCR0 = (TCCR0 & 0xF8) | F_CPU_CLK_TIMER0;				break;
	case F_CPU8_TIMER0:		TCCR0 = (TCCR0 & 0xF8) | F_CPU8_TIMER0;					break;
	case F_CPU64_TIMER0:	TCCR0 = (TCCR0 & 0xF8) | F_CPU64_TIMER0;				break;
	case F_CPU256_TIMER0:   TCCR0 = (TCCR0 & 0xF8) | F_CPU256_TIMER0;				break;
	case F_CPU1024_TIMER0:  TCCR0 = (TCCR0 & 0xF8) | F_CPU1024_TIMER0;				break;
    default:				                                                        break;

	}
	TCNT0 = Config_Ptr -> initial_value;
	OCR0 = Config_Ptr -> compare_value;
}

void Timer0_deInit(void)
{
	TCCR0 = 0;
	CLEAR_BIT(TIMSK,TOIE0);
	CLEAR_BIT(TIMSK,OCIE0);
	TCNT0 = 0;
	OCR0 = 0;
}

void Timer0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
