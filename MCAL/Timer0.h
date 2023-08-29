/*
 * Timer0.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Shawky
 */

#ifndef MCAL_TIMER0_H_
#define MCAL_TIMER0_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "std_types.h"
#include "common_macros.h"

/*The Options Of the Prescaler*/
typedef enum{
	NO_CLK_TIMER0, F_CPU_CLK_TIMER0, F_CPU8_TIMER0, F_CPU64_TIMER0, F_CPU256_TIMER0 ,F_CPU1024_TIMER0
}Timer0_Prescaler;

/*The Options Of The Timers*/
typedef enum{
	NORMAL_MODE_TIMER0, CTC_MODE_TIMER0
}Timer0_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;
 Timer0_Prescaler prescaler;
 Timer0_Mode mode;
} Timer0_ConfigType;

/*Functions Prototype*/

void Timer0_init(const Timer0_ConfigType * Config_Ptr);

void Timer0_deInit(void);

void Timer0_setCallBack(void(*a_ptr)(void));

#endif /* MCAL_TIMER0_H_ */
