/******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: motor.h
 *
 * Description: header file for the ATmega32 motor driver
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#ifndef MOTOR_H_
#define MOTOR_H_


#include "std_types.h"


/*******************************************************************************
 *                      Structures & enums                                     *
 *******************************************************************************/
typedef enum
{
	CW,STOP,ACW
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Initialization for DC motor
 */
void DcMotor_Init(void);

/*
 * Description :
 * starts rotation at specific speed
 */
void DcMotor_Rotate(DcMotor_State state);


#endif /* MOTOR_H_ */
