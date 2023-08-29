/*
 * SunRiseAlarm.c
 *
 *  Created on: Aug 28, 2023
 *      Author: Shawky
 */

#include "SunRiseAlarm.h"

uint8 g_KeyPadButton;
uint32 Alarms[3] = {0xFFFF,0xFFFF,0xFFFF};
uint8 g_number_of_alarms = 0;
uint32 g_TimeInMins = 0;
uint32 	g_alarm_value = 0;
uint8 g_buzzer_Flag = 0;
sint8 g_buzzer_count = 10;
sint8 g_LDR_count = 0;
uint8 g_Timer0_tick = 0;
uint8 ToggleLedsFlag = 0;

void Timer0_ISR(void)
{
	g_Timer0_tick++;
	if(g_Timer0_tick == 32)
	{
		g_Timer0_tick = 0;
		if(ToggleLedsFlag == 0)
		{
			letBlue_ON();
			letGreen_ON();
			letRed_ON();
			letYellow_ON();
			ToggleLedsFlag = 1;
		}
		else if(ToggleLedsFlag == 1)
		{
			letBlue_OFF();
			letGreen_OFF();
			letRed_OFF();
			letYellow_OFF();
			ToggleLedsFlag = 0;
		}
	}
}

void Timer1_ISR(void)
{
	++g_alarm_value;
	if(g_alarm_value == 60)
	{
		g_TimeInMins++;
		g_alarm_value = 0;
		OneMinHandler();
		AlarmTimeOut();
	}
	else
	{
		/*Do Nothing*/
	}

	if(g_buzzer_Flag == 1)
	{
		g_buzzer_count--;

	}
	else
	{
		Buzzer_off();
	}

	if(g_buzzer_count < 0)
	{
		Buzzer_on();

	}
	else
	{
		/*Do Nothing*/
	}

	if(readLDR() == pressed)
	{
		g_LDR_count++;

	}
	else if(readLDR() == released)
	{
		g_LDR_count = 0;
	}
	else
	{
		/*Do Nothing*/
	}

	if(g_LDR_count >= 3)
	{
		g_buzzer_Flag = 0;
		g_buzzer_count = 10;
		g_LDR_count = 0;
		Stop_timer0();
		letBlue_OFF();
		letGreen_OFF();
		letRed_OFF();
		letYellow_OFF();
	}
	else
	{
		/*Do Nothing*/
	}

}

int main(void)
{
	SysInit();
	HomePage();
}

sint8 firstAlarm()
{
	uint8 i;
	if(g_number_of_alarms > 0)
	{
		uint8 mnm = Alarms[0];
		for(i=1 ;i<g_number_of_alarms ; i++)
		{
			if(Alarms[i] < mnm)
			{
				mnm = Alarms[i];
			}
		}
		return mnm ;
	}
	return -1 ;
}
void homePage_interface()
{
	LCD_GOTO_XY(1,0);
	LCD_WriteString("1 Set Alarm    |");
	LCD_GOTO_XY(2,0);
	LCD_WriteString("2 Cancel Alarm |");
	LCD_GOTO_XY(3,0);
	LCD_WriteString("3 Show Alarms  |");
	LCD_GOTO_XY(4,0);
	sint8 nearest_alarm = firstAlarm();
	if(nearest_alarm == -1)
	{
		LCD_WriteString("NO alarm created yet");
	}
	else
	{
		LCD_WriteString("Nearest alarm in ");
		LCD_intgerToString(nearest_alarm);
	}
}

void HomePage(void)
{
	while(1)
	{
		LCD_Clear();
		homePage_interface();
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
		while(g_KeyPadButton > 3)
		{
			g_KeyPadButton = KeyPad_GetValue();
			_delay_ms(500);
		}
		switch(g_KeyPadButton){

		case SET_ALARM :
			set_alarm_page();
			break;

		case Cancel_ALARM:
			cancel_alarm_page();
			break;

		case SHOW_ALARM_LIST:
			show_alarms_page();
			break;

		default :
			break;
		}
	}
}

void set_alarm_page()
{
	uint8 i;
	if(g_number_of_alarms < 3)
	{
		set_alarm_page_interface();
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
		for(i=0 ;i<g_number_of_alarms;i++)
		{
			if(g_KeyPadButton == Alarms[i])
			{
				LCD_WriteString("You Cannot Set");
				LCD_GOTO_XY(2,0);
				LCD_WriteString("The Same duration");
				return;
			}
		}
		Alarms[g_number_of_alarms] = g_KeyPadButton;
		g_number_of_alarms++;
		LCD_Clear();
		LCD_WriteString("The Alarm is set");
		LCD_GOTO_XY(2,0);
		LCD_WriteString("Press'16'to continue");
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}
	else
	{
		LCD_Clear();
		LCD_WriteString("You Exceed The Max");
		LCD_GOTO_XY(1,0);
		LCD_WriteString("Alarm Numbers");
		LCD_GOTO_XY(2,0);
		LCD_WriteString("Press '16' to return");
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}
	while(g_KeyPadButton != 16)
	{
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}
}

void set_alarm_page_interface()
{
	LCD_Clear();
	LCD_WriteString("Enter Alarm duration: ");
}

void cancel_alarm_page()
{
	uint8 i;

	if(g_number_of_alarms > 0)
	{
		LCD_Clear();
		for(i=0 ; i<g_number_of_alarms ; ++i)
		{
			LCD_GOTO_XY(i+1,0);
			LCD_WriteString("Alarm ");
			LCD_intgerToString(i+1);
			LCD_WriteString(": ");
			LCD_intgerToString(Alarms[i]);
		}
		LCD_GOTO_XY(i+1,0);
		LCD_WriteString("Cancel alarm no:");

		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
		while(g_KeyPadButton > g_number_of_alarms )
		{
			g_KeyPadButton = KeyPad_GetValue();
			_delay_ms(500);
		}
		for(i = g_KeyPadButton; i<g_number_of_alarms ;i++)
		{
			Alarms[i-1] = Alarms[i];
		}
		g_number_of_alarms--;
		LCD_Clear();
		LCD_WriteString("The Alarm Removed");
		LCD_GOTO_XY(2,0);
		LCD_WriteString("Press'16'to continue");
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}
	else
	{
		LCD_Clear();
		LCD_WriteString("No Alarm is set");
		LCD_GOTO_XY(2,0);
		LCD_WriteString("Press'16'to continue");
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}

	while(g_KeyPadButton != 16)
	{
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}

}

void show_alarms_page()
{
	uint8 i;
	if(g_number_of_alarms > 0)
	{
		LCD_Clear();
		LCD_WriteString("Alarms List:");
		for(i=0 ; i<g_number_of_alarms ; ++i)
		{
			LCD_GOTO_XY(i+2,0);
			LCD_WriteString("Alarm ");
			LCD_intgerToString(i+1);
			LCD_WriteString(": ");
			LCD_intgerToString(Alarms[i]);
		}
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
	}
	else
	{
		LCD_Clear();
		LCD_WriteString("No Alarm Set");
		LCD_GOTO_XY(2,0);
		LCD_WriteString("Press'16'to continue");
		g_KeyPadButton = KeyPad_GetValue();
		_delay_ms(500);
		while(g_KeyPadButton != 16)
		{
			g_KeyPadButton = KeyPad_GetValue();
			_delay_ms(500);
		}
	}

}

void AlarmTimeOut(void)
{
	uint8 i;
	if(g_number_of_alarms > 0)
	{
		for(i=0 ;i<g_number_of_alarms ; i++)
		{
			if(Alarms[i] == 0)
			{
				AlarmIsFired();
			}
		}
	}
}

void OneMinHandler(void)
{
	uint8 i;
	if(g_number_of_alarms > 0)
	{
		for(i=0 ;i<g_number_of_alarms ; i++)
		{
			Alarms[i]--;
		}
	}
}

void AlarmIsFired(void)
{
	uint8 i,temp;
	for(i = 0; i<g_number_of_alarms ;i++)
	{
		if(Alarms[i] == 0)
		{
			temp = Alarms[i];
			Alarms[i] = Alarms[i+1];
			Alarms[i+1] = temp;
		}
	}
	g_number_of_alarms--;
	g_buzzer_Flag = 1;
	Start_timer0();

}

void InitLeds(void)
{
	Set_led_green();
	Set_led_blue();
	Set_led_red();
	Set_led_yellow();
}
void SysInit(void)
{
	LCD_Init();
	Buzzer_init();
	Keypad_init();
	Start_timer1();
	InitLeds();
	Timer1_setCallBack(Timer1_ISR);
	Timer0_setCallBack(Timer0_ISR);
	LDR_init();
}
