 /******************************************************************************
 *
 * Module: MC1
 *
 * File Name: hmi_ECU.h
 *
 * Description: header file for the HMI MC
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
# define F_CPU 8000000UL
#define MCU1_READY 0x01
#define MCU2_READY 0x02
#define FIRST_TIME 0x05
#define NOT_FIRST_TIME 0x22
#define THIS_IS_PW 0x88
#define PW_SUCCESS 0x30
#define PW_FAILURE 0x31
#define PW_CHECK 0x82
#define BUZZER_ON 0x49
#define DOOR_OPEN 0x44


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void enter_Password();
void reenter_Password();
void menu();
void check_password();
void open_door();
void buzzer_activate();



#endif /* HMI_ECU_H_ */
