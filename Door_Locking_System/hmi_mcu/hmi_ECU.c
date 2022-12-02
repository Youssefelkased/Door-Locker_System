 /******************************************************************************
 *
 * Module: MC1
 *
 * File Name: hmi_ECU.c
 *
 * Description: source file for the HMI MC
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#include "keypad.h"
#include "lcd.h"
#include "timer.h"
#include "uart.h"
#include "hmi_ECU.h"
#include "avr/io.h"
#include "avr/delay.h"

uint8 checkBit=0,first_time=0,correct_pass=PW_SUCCESS,menu_option;
uint8 arr[20]="00000#";
uint16 timerCount;

/*******************************************************************************
 *                      Main function                                          *
 *******************************************************************************/
int main()
{
	uint8 i;
	SREG|=(1<<7);
	UART_ConfigType Config1={EIGHT_BIT_MODE,DISABLED,ONE_BIT_MODE,9600};
	UART_init(&Config1);
	LCD_init();
	UART_sendByte(MCU1_READY);
	first_time=UART_recieveByte();
	while(1)
	{
		if(first_time==FIRST_TIME)
		{
			enter_Password();
			reenter_Password();
		}
		while(1)
		{
			if(correct_pass==PW_SUCCESS)
			{
				menu();
				if(menu_option=='+')
				{
					while(1)
					{
						check_password();
						if(correct_pass==PW_SUCCESS)
						{
							open_door();
							break;
						}
						else if(correct_pass==PW_FAILURE)
						{
							for (i = 0;i < 2; ++i) {
								LCD_clearScreen();
								LCD_displayStringRowColumn(0, 0, "Wrong password...try again");
								_delay_ms(1000);
								check_password();
								if(correct_pass==PW_SUCCESS)
								{
									open_door();
									break;
								}
								if (i==1)
								{
									LCD_clearScreen();
									LCD_displayStringRowColumn(0, 0, "unauthorized action");
									buzzer_activate();
									_delay_ms(500);
									correct_pass=PW_SUCCESS;
									break;
								}
							}
						}
					}
				}
				else if(menu_option=='-')
				{
					check_password();
					if(correct_pass==PW_SUCCESS)
					{
						first_time=FIRST_TIME;
						break;
					}
					else if(correct_pass==PW_FAILURE)
					{
						for (i = 0;i < 2; ++i) {
							LCD_clearScreen();
							LCD_displayStringRowColumn(0, 0, "Wrong password...try again");
							_delay_ms(1000);
							check_password();
							if(correct_pass==PW_SUCCESS)
							{
								first_time=FIRST_TIME;
								break;
							}
							if (i==1)
							{
								LCD_clearScreen();
								LCD_displayStringRowColumn(0, 0, "unauthorized action");
								buzzer_activate();
								_delay_ms(500);
								correct_pass=PW_SUCCESS;
								break;
							}
						}
						break;
					}

				}

			}
			else
			{
				LCD_displayString("wrong not matched");
				_delay_ms(1000);
				break;
			}

		}

	}
	return 1;
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void menu()
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+ Open door");
	LCD_displayStringRowColumn(1, 0, "- Change password");
	menu_option=KEYPAD_getPressedKey();
}
void check_password()
{
	uint8 i;
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendByte(PW_CHECK);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "plz enter pass:");
	LCD_moveCursor(1, 0);
	_delay_ms(500);
	for (i = 0; i < 5; ++i) {
		arr[i] = KEYPAD_getPressedKey();

		LCD_displayCharacter('*');
//	   if((arr[i] <= 9) && (arr[i] >= 0))
//		{
//			LCD_intgerToString(arr[i]);   /* display the pressed keypad switch */
//		}
//		else
//		{
//			LCD_displayCharacter(arr[i]); /* display the pressed keypad switch */
//		}
//

		_delay_ms(500); /* Press time */
	}
	while(KEYPAD_getPressedKey()!=13);
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendString(arr);
	UART_sendByte(MCU1_READY);
	correct_pass=UART_recieveByte();

}
void enter_Password()
{
	uint8 i;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "plz enter pass:");
	LCD_moveCursor(1, 0);
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendByte(THIS_IS_PW);
	_delay_ms(500);
	for (i = 0; i < 5; ++i) {
		arr[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
//	   if((arr[i] <= 9) && (arr[i] >= 0))
//		{
//			LCD_intgerToString(arr[i]);   /* display the pressed keypad switch */
//		}
//		else
//		{
//			LCD_displayCharacter(arr[i]); /* display the pressed keypad switch */
//		}
//

		_delay_ms(500); /* Press time */
	}
	while(KEYPAD_getPressedKey()!=13);
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendString(arr);
}
void reenter_Password()
{
	uint8 i,arr[6];
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "plz re-enter pass:");
	LCD_moveCursor(1, 0);
	_delay_ms(500);
	for (i = 0; i < 5; ++i) {
		arr[i] = KEYPAD_getPressedKey();
		LCD_displayCharacter('*');
//	   if((arr[i] <= 9) && (arr[i] >= 0))
//		{
//			LCD_intgerToString(arr[i]);   /* display the pressed keypad switch */
//		}
//		else
//		{
//			LCD_displayCharacter(arr[i]); /* display the pressed keypad switch */
//		}
//

		_delay_ms(500); /* Press time */
	}
	arr[5]='#';
	while(KEYPAD_getPressedKey()!=13);
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendString(arr);
	UART_sendByte(MCU1_READY);
	correct_pass=UART_recieveByte();
}
void timer_callback(){
	timerCount++;
}

void open_door()
{
	timerCount=0;
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendByte(DOOR_OPEN);
	LCD_clearScreen();
	Timer1_ConfigType timer_config = { 0,31250, F_CPU_256, COMPARE};
	Timer1_init(&timer_config);
	Timer1_setCallBack(timer_callback);
	LCD_displayStringRowColumn(0, 0, "Door is opening..");
	while (timerCount < 15) {
	}
	Timer1_deInit();
	timerCount=0;
	Timer1_init(&timer_config);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is opened.");
	while (timerCount < 3) {
	}
	Timer1_deInit();
	timerCount=0;
	Timer1_init(&timer_config);
	LCD_displayStringRowColumn(0, 0, "Door is closing..");
	while (timerCount <15) {
	}

}
void buzzer_activate()
{
	while(UART_recieveByte()!=MCU2_READY);
	UART_sendByte(BUZZER_ON);
	Timer1_ConfigType timer_config = { 0,31250, F_CPU_256,  COMPARE};
	Timer1_init(&timer_config);
	Timer1_setCallBack(timer_callback);
	while (timerCount < 60) {
	}
	Timer1_deInit();
}
