 /******************************************************************************
 *
 * Module: Timer1
 *
 * File Name: timer.c
 *
 * Description: source file for timer1 module
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/


#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "timer.h"
#include "avr/interrupt.h"
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
uint8 g_tick=0;
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
		{
			(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = Config_Ptr->initial_value; //timer initial value
	if(Config_Ptr->mode==COMPARE)
	{
		TCCR1B =(1<<WGM12);
		OCR1A  = Config_Ptr->compare_value;
		TIMSK |= (1<<OCIE1A);
	}
	else if(Config_Ptr->mode==NORMAL)
	{
		TCCR1A=0;
		TCCR1B=0;
		TIMSK |= (1<<TOIE1);
	}
	TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	TCCR1B |= Config_Ptr->prescaler;
}
void Timer1_deInit(void)
{
TCNT1=0;
TCCR1B=0;
TCCR1A=0;
TIMSK=0;
OCR1A=0;
}
void Timer1_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
