/*
 * timer1.h
 *
 *  Created on: May 11, 2023
 *      Author: Shawky
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include <avr\interrupt.h>
#include <avr\io.h>
#include "std_types.h"
#include "common_macros.h"

/*The Options Of the Prescaler*/
typedef enum{
	NO_CLK, F_CPU_CLK, F_CPU8, F_CPU64, F_CPU256 ,F_CPU1024
}Timer1_Prescaler;

/*The Options Of The Timers*/
typedef enum{
	NORMAL_MODE, CTC_MODE
}Timer1_Mode;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*Functions Prototype*/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

void Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
