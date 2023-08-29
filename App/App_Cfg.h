/*
 * App_Cfg.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Shawky
 */

#ifndef APP_APP_CFG_H_
#define APP_APP_CFG_H_

#include <util/delay.h>
#include "Timer1.h"
#include "GPIO.h"
#include "pwm.h"
#include "Timer0.h"

#define PRESCALER_VALUE_TIMER1					F_CPU256
#define TIMER1_MODE								CTC_MODE
#define COMPARE_VALUE_TIMER1					62500

#define PRESCALER_VALUE_TIMER0					F_CPU1024_TIMER0
#define TIMER0_MODE								CTC_MODE_TIMER0
#define COMPARE_VALUE_TIMER0					248

void Stop_timer1(void);
void Start_timer1(void);
void Timer0_ISR(void);
void Start_timer0(void);
void Stop_timer0(void);
void Diming(void);

#endif /* APP_APP_CFG_H_ */
