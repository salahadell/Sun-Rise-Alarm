/*
 * LDR.h
 *
 * Created: 8/27/2023 12:16:14 PM
 *  Author: Lenovo
 */ 


#ifndef LDR_H_
#define LDR_H_

#include "GPIO.h"
#include "ADC.h"
#include "lcd.h"
#include <avr/io.h>

typedef enum{
	pressed,
	released
}LDR_state;

void LDR_init();

LDR_state readLDR();
#endif /* LDR_H_ */
