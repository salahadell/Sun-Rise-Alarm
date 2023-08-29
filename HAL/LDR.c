/*
 * LDR.c
 *
 * Created: 8/27/2023 12:16:01 PM
 *  Author: Lenovo
 */ 

#include "LDR.h"

ADC_Config_t ADC_Config;
uint16 ADC_Data;
char buffer[10];

void ADC_Callback(void){
	if(ADC_Config.ADC_Result_Presentation == ADC_Result_Presentation_RIGHT){
		ADC_Data = (ADCL | ((ADCH & (0x03)) << 8));
	}
	else{
		ADC_Data = ((ADCL & (0xC0)) >> 6) | (ADCH << 2);
	}
	
//	SET_BIT(ADCSRA, 4);
}

void LDR_init(){
	
	//-----------------------------
	//1) Initialize ADC
	//-----------------------------
	ADC_Config.ADC_MODE = ADC_MODE_SINGLE_CONVERSION;
	ADC_Config.ADC_PRESCALER = ADC_PRESCALER_128;
	ADC_Config.ADC_Result_Presentation = ADC_Result_Presentation_RIGHT;
	ADC_Config.ADC_VREF = ADC_VREF_AVCC;
	ADC_Config.IRQ_Enable = ADC_IRQ_ENABLE;
	ADC_Config.P_CallBack = ADC_Callback;
	ADC_init(&ADC_Config);
	
/*	LCD_Init();
	LCD_Clear();
	*/
	//-----------------------------
	//2) Initialize LDR (PA0)
	//-----------------------------
	DIO_SetPinDir(DIO_PORTA, DIO_PIN0, DIO_PIN_INPUT);
}

LDR_state readLDR()
{
	uint8 value;
	
	ADC_ReadData(ADC1, &ADC_Data, Polling_DISABLE);

	if(ADC_Data > 400){
		value=pressed;
	}
	else{
		value=released;
	}
	return value;
}



