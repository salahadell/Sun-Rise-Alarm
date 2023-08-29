/*
 * pwm.h
 *
 *  Created on: Aug 27, 2023
 *      Author: Shawky
 */

#ifndef PWM_H_
#define PWM_H_

#include <util/delay.h>
#include <avr/io.h>
#include "GPIO.h"
#include "std_types.h"

void PwmSetDutyCycle(uint8 dutycycle);
void PwmInit(void);
void PwmDenit(void);

#endif /* PWM_H_ */
