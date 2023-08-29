/*
 * lids.h
 *
 * Created: 8/20/2023 10:12:29 AM
 *  Author: salah
 */ 


#ifndef LIDS_H_
#define LIDS_H_

#include "GPIO.h"

//Pins numbers
#define BLUE_LED_PIN    DIO_PIN5
#define RED_LED_PIN     DIO_PIN7
#define GREEN_LED_PIN   DIO_PIN4
#define YELLOW_LED_PIN  DIO_PIN6

//Pins Ports
#define BLUE_LED_PORT    DIO_PORTA
#define RED_LED_PORT     DIO_PORTB
#define GREEN_LED_PORT   DIO_PORTA
#define YELLOW_LED_PORT  DIO_PORTA

//Set the direction of the led pins
void Set_led_green();
void Set_led_blue();
void Set_led_red();
void Set_led_yellow();

//Return if the leds HIGH or LOW
uint8 isGreen_ON();
uint8 isBlue_ON();
uint8 isRed_ON();
uint8 isYellow_ON();

//Set the leds HIGH
void letGreen_ON();
void letBlue_ON();
void letYellow_ON();
void letRed_ON();

//Set the leds LOW
void letGreen_OFF();
void letBlue_OFF();
void letYellow_OFF();
void letRed_OFF();




#endif /* LIDS_H_ */
