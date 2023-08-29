/*
 * Keypad1.c
 *
 *  Created on: Aug 19, 2023
 *      Author: Shawky
 */

#include "keypad.h"

//uint8 keypad_adjust(uint8 button_number);


void Keypad_init(void)
{

	DIO_SetPinDir(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN0, DIO_PIN_INPUT);
	DIO_SetPinDir(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN1, DIO_PIN_INPUT);
	DIO_SetPinDir(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN2, DIO_PIN_INPUT);
	DIO_SetPinDir(KEYPAD_COLUMN_PORT, KEYPAD_COLUMN3, DIO_PIN_INPUT);


	DIO_SetPinDir(KEYPAD_ROW_PORT, KEYPAD_ROW0, DIO_PIN_INPUT);
	DIO_SetPinDir(KEYPAD_ROW_PORT, KEYPAD_ROW1, DIO_PIN_INPUT);
	DIO_SetPinDir(KEYPAD_ROW_PORT, KEYPAD_ROW2, DIO_PIN_INPUT);
	DIO_SetPinDir(KEYPAD_ROW_PORT, KEYPAD_ROW3, DIO_PIN_INPUT);
}

uint8 KeyPad_GetValue(void)
{
	uint8 col;
	ubit8 row;
	uint8 read = 1;

	while(1)
	{
		read = 1;
		for(row = 0; row<4 ; row++)
		{

			DIO_SetPinDir(KEYPAD_ROW_PORT, KEYPAD_ROW0-row, DIO_PIN_OUTPUT);

			DIO_SetPinVal(KEYPAD_ROW_PORT,KEYPAD_ROW0-row,LOGIC_LOW);

			for(col=0 ;col<5;col++)
			{

				if(col != 3)
				{
					read =  DIO_ReadPin(KEYPAD_COLUMN_PORT ,KEYPAD_COLUMN0-col);
					if(read == 0)
					{
						if(col == 4)
							{
								return ((row*4)+col);
							}
						return ((row*4)+col+1);
					}
				}
			}
			DIO_SetPinDir(KEYPAD_ROW_PORT, KEYPAD_ROW0-row, DIO_PIN_INPUT);


		}
	}
}
/*
uint8 keypad_adjust(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 1: keypad_button = 7;
				break;
		case 2: keypad_button = 8;
				break;
		case 3: keypad_button = 9;
				break;
		case 4: keypad_button = '%';
				break;
		case 5: keypad_button = 4;
				break;
		case 6: keypad_button = 5;
				break;
		case 7: keypad_button = 6;
				break;
		case 8: keypad_button = '*';
				break;
		case 9: keypad_button = 1;
				break;
		case 10: keypad_button = 2;
				break;
		case 11: keypad_button = 3;
				break;
		case 12: keypad_button = '-';
				break;
		case 13: keypad_button = 13;
				break;
		case 14: keypad_button = 0;
				break;
		case 15: keypad_button = '=';
				break;
		case 16: keypad_button = '+';
				break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;

}*/
