# Door-Locker_System
MT diploma Door Locker Security System to unlock a door using a password, C based project, using ATmega32 microcontroller, the project is designed and implemented based on the layered architecture model.
The project uses 2 ATmega32 microcontrollers:

HMI_ECU (Human Machine Interface) is just responsible for interaction with the user, it takes inputs through the keypad and display messages on the LCD.

CONTROL_ECU is responsible for all the processing and decisions in the system like password checking, opening the door and activating the system alarm in case of wrong password.
