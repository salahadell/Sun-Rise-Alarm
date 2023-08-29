/*
 * SunRiseAlarm.h
 *
 *  Created on: Aug 28, 2023
 *      Author: Shawky
 */

#ifndef APP_SUNRISEALARM_H_
#define APP_SUNRISEALARM_H_

#include "std_types.h"
#include "common_macros.h"
#include "Keypad.h"
#include "lcd.h"
#include "LDR.h"
#include "pwm.h"
#include "buzzer.h"
#include "App_Cfg.h"
#include "leds.h"


#define SET_ALARM         1
#define Cancel_ALARM      2
#define SHOW_ALARM_LIST   3
#define ALARM_FIRED		  4


void HomePage(void);
void set_alarm_page(void);
void set_alarm_page_interface(void);
void cancel_alarm_page(void);
void show_alarms_page(void);
void SysInit(void);
void AlarmTimeOut(void);
void OneMinHandler(void);
void AlarmIsFired(void);
void Timer0_ISR(void);
void Timer1_ISR(void);
void InitLeds(void);

#endif /* APP_SUNRISEALARM_H_ */
