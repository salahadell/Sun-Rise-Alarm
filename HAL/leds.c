/*
 * leds.c
 *
 * Created: 8/20/2023 10:12:51 AM
 *  Author: salah
 */ 
#include "leds.h"
//Set the direction of the led pins
void Set_led_green(){
	DIO_SetPinDir(GREEN_LED_PORT,GREEN_LED_PIN,DIO_PIN_OUTPUT);
}
void Set_led_blue(){
	DIO_SetPinDir(BLUE_LED_PORT,BLUE_LED_PIN,DIO_PIN_OUTPUT);
}
void Set_led_red()
{	
	DIO_SetPinDir(RED_LED_PORT,RED_LED_PIN,DIO_PIN_OUTPUT);
}
void Set_led_yellow(){
	DIO_SetPinDir(YELLOW_LED_PORT,YELLOW_LED_PIN,DIO_PIN_OUTPUT);
}

//Return if the leds HIGH or LOW
uint8 isGreen_ON(){
	return 	DIO_ReadPin(GREEN_LED_PORT,GREEN_LED_PIN);
}
uint8 isBlue_ON(){
	return DIO_ReadPin(BLUE_LED_PORT,BLUE_LED_PIN);
}
uint8 isRed_ON(){
	return DIO_ReadPin(RED_LED_PORT,RED_LED_PIN);
}
uint8 isYellow_ON(){
	return DIO_ReadPin(YELLOW_LED_PORT,YELLOW_LED_PIN);
}

//Set the leds HIGH
void letGreen_ON(){
		DIO_SetPinVal(GREEN_LED_PORT,GREEN_LED_PIN,DIO_PIN_HIGH);
}
void letBlue_ON(){
		DIO_SetPinVal(BLUE_LED_PORT,BLUE_LED_PIN,DIO_PIN_HIGH);
}
void letYellow_ON(){
		DIO_SetPinVal(YELLOW_LED_PORT,YELLOW_LED_PIN,DIO_PIN_HIGH);
}
void letRed_ON(){
		DIO_SetPinVal(RED_LED_PORT,RED_LED_PIN,DIO_PIN_HIGH);
}

//Set the leds LOW
void letGreen_OFF(){
		DIO_SetPinVal(GREEN_LED_PORT,GREEN_LED_PIN,DIO_PIN_LOW);
}
void letBlue_OFF(){
		DIO_SetPinVal(BLUE_LED_PORT,BLUE_LED_PIN,DIO_PIN_LOW);
}
void letYellow_OFF(){
		DIO_SetPinVal(YELLOW_LED_PORT,YELLOW_LED_PIN,DIO_PIN_LOW);
}
void letRed_OFF(){
		DIO_SetPinVal(RED_LED_PORT,RED_LED_PIN,DIO_PIN_LOW);
}
