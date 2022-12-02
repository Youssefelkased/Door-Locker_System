/******************************************************************************
 *
 * Module: buzzer
 *
 * File Name: buzzer.h
 *
 * Description: source file for the ATmega32 buzzer driver
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
#include "gpio.h"

#define BUZZER_PORT PORTA_ID
#define BUZZER_PIN	PIN0_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialization for buzzer
 */
void Buzzer_init();
/*
 * Description :
 * turns the buzzer on
 */
void Buzzer_on(void);
/*
 * Description :
 * turns the buzzer off
 */
void Buzzer_off(void);
#endif /* BUZZER_H_ */
