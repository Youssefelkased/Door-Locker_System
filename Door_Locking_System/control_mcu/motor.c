/******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: motor.c
 *
 * Description: source file for the ATmega32 motor driver
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#include "pwm.h"
#include "gpio.h"
#include "common_macros.h"
#include "motor.h"
//#include "adc.h"
#include <avr/io.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void)	/* Initialization for DC motor */
{

	/* configure pin PC6 and PC7 as output pins */
	GPIO_setupPinDirection(PORTB_ID, PIN6_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN7_ID, PIN_OUTPUT);

	/* Motor is stop at the beginning */
	DcMotor_Rotate(STOP);
}

void DcMotor_Rotate(DcMotor_State state)	/* starts rotation at specific speed */
{
	uint8 dutyCycle=255;/*Always operate with maximum speed*/

	/*if(speed == 100){
		dutyCycle=255;
	}else{
		dutyCycle=(speed*256)/100;
	}*/

	/* check if the first push button at PA0 is pressed/not */
	if(state==CW)
	{
		// Rotate the motor --> clock wise
		PWM_Timer0_Start(dutyCycle);
		GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
	}
	if(state==ACW)
		{
			// Rotate the motor --> clock wise
			PWM_Timer0_Start(dutyCycle);
			GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
			GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_HIGH);
		}
	/* check if the third push button at PA2 is pressed/not */
	else if(state==STOP)
	{
		// Stop the motor
		PWM_Timer0_Start(0);
		GPIO_writePin(PORTB_ID, PIN6_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN7_ID, LOGIC_LOW);
	}

}
