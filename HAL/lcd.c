/*
 * lcd.c
 *
 *  Created on: Aug 18, 2023
 *      Author: Shawky
 */
#include <avr/io.h>
#include <util/delay.h>
#include "GPIO.h"
#include "lcd_cfg.h"
#include "common_macros.h"
#include "lcd.h"
#include "std_types.h"



void LCD_Init(void)
{
	DIO_SetPinDir(LCD_CMD_PORTID,LCD_RS,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_CMD_PORTID,LCD_EN,DIO_PIN_OUTPUT);

	_delay_ms(20);

	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D4,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D5,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D6,DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_DATA_PORTID,LCD_D7,DIO_PIN_OUTPUT);

	LCD_WriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_WriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	LCD_WriteCommand(LCD_TWO_LINES_FOUR_BITS_MODE);


	LCD_WriteCommand(LCD_CLEAR_COMMAND);
	LCD_WriteCommand(0x0F);
	LCD_WriteCommand(LCD_CURSOR_OFF);

}

void LCD_WriteCommand(uint8 cmd)
{
   //MODE OF 4 BITS
   //SET THE RS LOW TO ENABLE COMMAND MODE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_RS,LOGIC_LOW);
	_delay_ms(1);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE MOST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(cmd,4));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(cmd,5));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(cmd,6));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(cmd,7));

   //REFRESHING PULSE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE lEST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(cmd,0));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(cmd,1));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(cmd,2));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(cmd,3));



	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);

}

void LCD_Writechar(uint8 chr)
{
	   //SET THE RS HIGH TO ENABLE DATA MODE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_RS,LOGIC_HIGH);
	_delay_ms(1);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE MOST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(chr,4));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(chr,5));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(chr,6));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(chr,7));

   //REFRESHING PULSE
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);
	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_HIGH);
	_delay_ms(1);

   //SET THE lEST SIG 4 BITS IN THE DATA BUS 
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D4,GET_BIT(chr,0));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D5,GET_BIT(chr,1));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D6,GET_BIT(chr,2));
	DIO_SetPinVal(LCD_DATA_PORTID,LCD_D7,GET_BIT(chr,3));


	DIO_SetPinVal(LCD_CMD_PORTID,LCD_EN,LOGIC_LOW);

}

void LCD_WriteString(const char *str)
{
	uint8 i=0;
	while(str[i] != '\0')
	{
		LCD_Writechar(str[i]);
		i++;
	}
}


void LCD_intgerToString(uint32 data)
{
   char buff[16]; /* String to hold the ascii result */
   ltoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
   LCD_WriteString(buff); /* Display the string */
}


void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_GOTO_XY(uint8 line,  uint8 position){
	
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(line)
	{
		case 1:
			lcd_memory_address=position;
				break;
		case 2:
			lcd_memory_address=position+0x40;
				break;
		case 3:
			lcd_memory_address=position+0x14;
				break;
		case 4:
			lcd_memory_address=position+0x54;
				break;
		default: 
			break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_WriteCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}


