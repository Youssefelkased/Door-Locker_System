/******************************************************************************
 *
 * Module: MC2
 *
 * File Name: control_ECU.c
 *
 * Description: source file for the Control MC
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#include "timer.h"
#include "uart.h"
#include "control_ECU.h"
#include "external_eeprom.h"
#include "motor.h"
#include "pwm.h"
#include "twi.h"
#include "avr/io.h"
#include "buzzer.h"
#include "avr/delay.h"
#include "gpio.h"

uint8 checkBit=0,pw1[20]="00000",pw2[20]="00000",temp[10]="00000";
uint16 timerCount;

int main()
{
	SREG|=(1<<7);
	UART_ConfigType Config1={EIGHT_BIT_MODE,DISABLED,ONE_BIT_MODE,9600};
	UART_init(&Config1);
	TWI_ConfigType Config_TWI={0x01,0x02};
	TWI_init(&Config_TWI);
	Buzzer_init();
	DcMotor_Init();
	check_first_time();
	while(1)
	{
		UART_sendByte(MCU2_READY);
		checkBit=UART_recieveByte();
		switch(checkBit)
		{
		case THIS_IS_PW:
			save_Password();
			save_and_check_password();
			break;
		case PW_CHECK:
			check_PW();
			break;
		case DOOR_OPEN:
			open_door();
			break;
		case BUZZER_ON:
			buzzer_activate();
			break;
		default:
			break;

		}
	}
	return 1;
}
void check_first_time()
{
	uint8 value,i,check_cond=0;
	for (i = 0; i < 5; ++i) {
		EEPROM_readByte(EE_ADDR+i, &value);
		if(value==0xFF)
		{
			check_cond++;
		}
	}
	if(check_cond==5)
	{
		while(UART_recieveByte() != MCU1_READY);
		UART_sendByte(FIRST_TIME);
	}
	else
	{
		while(UART_recieveByte() != MCU1_READY);
		UART_sendByte(NOT_FIRST_TIME);
	}

}
void save_Password()
{
	UART_sendByte(MCU2_READY);
	UART_receiveString(pw1);
}
void save_and_check_password()
{
	uint8 i,count=0;
	UART_sendByte(MCU2_READY);
	UART_receiveString(pw2);
	for (i = 0; i < 5; ++i) {
		if(pw1[i]==pw2[i]) count++;
	}
	if (count==5)
	{
		for (i = 0; i < 5; ++i) {
			_delay_ms(10);
			EEPROM_writeByte(EE_ADDR+i, pw2[i]);
			_delay_ms(10);
		}
		while(UART_recieveByte() != MCU1_READY);
		UART_sendByte(PW_SUCCESS);
	}
	else
	{
		while(UART_recieveByte() != MCU1_READY);
		UART_sendByte(PW_FAILURE);
	}
}

void check_PW()
{
	uint8 i,x=0;
	UART_sendByte(MCU2_READY);
	UART_receiveString(pw1);
	_delay_ms(10);
	for (i = 0; i < 5; ++i) {
		EEPROM_readByte(EE_ADDR+i, &x);
		temp[i]=x;
		_delay_ms(10);
	}
	for (i = 0; i < 5; ++i) {
		if(pw1[i]!=temp[i])
		{
			while(UART_recieveByte()!=MCU1_READY);
			UART_sendByte(PW_FAILURE);
			return;
		}
	}
	while(UART_recieveByte()!=MCU1_READY);
	UART_sendByte(PW_SUCCESS);
}
void timer_callback(){
	timerCount++;
}

void open_door()
{
	EEPROM_writeByte(0x0350, 0x11);
	timerCount = 0;
	Timer1_ConfigType timer_config = { 0,31250, F_CPU_256,COMPARE};
	Timer1_init(&timer_config);
	Timer1_setCallBack(timer_callback);
	DcMotor_Rotate(CW);
	while (timerCount < 15) {
	}
	DcMotor_Rotate(STOP);
	Timer1_deInit();
	timerCount = 0;
	Timer1_init(&timer_config);
	while (timerCount < 3) {}
	DcMotor_Rotate(ACW);
	Timer1_deInit();
	timerCount = 0;
	Timer1_init(&timer_config);
	while (timerCount < 15) {}
	Timer1_deInit();
	timerCount = 0;
	DcMotor_Rotate(STOP);
}
void buzzer_activate()
{
	Timer1_ConfigType timer_config = { 0, 31250, F_CPU_256, COMPARE};
	Timer1_init(&timer_config);
	Timer1_setCallBack(timer_callback);
	Buzzer_on();
	while(timerCount !=60){}
	Timer1_deInit();
	timerCount=0;
	Buzzer_off();

}
