/******************************************************************************
 *
 * Module: MC2
 *
 * File Name: control_ECU.h
 *
 * Description: Header file for the Control MC
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_



/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
# define F_CPU 8000000UL
#define MCU1_READY 0x01
#define MCU2_READY 0x02
#define EE_ADDR 0x0300
#define FIRST_TIME 0x05
#define BUZZER_ON 0x49
#define NOT_FIRST_TIME 0x22
#define THIS_IS_PW 0x88
#define PW_CHECK 0x82
#define PW_SUCCESS 0x30
#define PW_FAILURE 0x31
#define DOOR_OPEN 0x44
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void save_and_check_password();
void check_first_time();
void save_Password();
void check_PW();
void timer_callback();
void open_door();
void buzzer_activate();
#endif /* CONTROL_ECU_H_ */
