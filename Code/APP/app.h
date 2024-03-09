

#ifndef APP_APP_H_
#define APP_APP_H_

/*************************** Section: Includes *********************************/

#include "../MCAL/UART/uart.h"
#include "../MCAL/TWI/twi.h"
#include "../MCAL/TIMER1/timer1.h"
#include "../HAL/BUZZER/buzzer.h"
#include "../HAL/EXT_EEPORM/eeprom.h"
#include "../HAL/MOTOR/motor.h"
#include "avr/interrupt.h"

/*************************** Section: Macro Definitions ************************/

#define TIMER1_OCR1A				(8000) 	/* Timer Config To make interrupt every 1 sec*/
#define PASSWORD_SIZE				(5) 	/* password array size */
#define Password_Address			(0x350) /* Password Location in the EEPROM */
#define	Password_Is_Set_Address		(0x320)	/* Password flag Location in the EEPROM */
#define PasswordSET					(0xC2) 	/* To indicate whether the password is set or not */

#define MC_Ready					(0xFC) /* Message to indicate if the MCU is ready or not */
#define MSG_UpdatePassword			(0x99) /* Message From MCU1 to MCU2 to inform it that it will send new password and replace the one you have with it */
#define MSG_TurnOnAlarm				(0x88) /* Message From MCU1 to MCU2 to inform it the user entered the password wrong for 3 times, turn on the alarm */
#define MSG_checkPassword			(0x77) /* Message From MCU1 to MCU2 to inform it that it will send password from keypad to get checked */
#define MSG_Motor					(0x20) /* Message From MCU1 to MCU2 to inform it the user entered the password right, open the door */
#define MSG_Matched					(0xF0) /* Message From MCU2 to MCU1 to inform it if the passwords match or not */
#define MSG_UnMatched				(0x0F) /* Message From MCU2 to MCU1 to inform it if the passwords match or not */


/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/

extern DCMotor_t dcMotor;
/*************************** Section: Methods Prototypes ***********************/

void APP_isPasswordSet();
void APP_updatePassword();
void APP_checkPassword();
void APP_readPassword();
void APP_alarm();
void APP_door();

void TIMER1_MOTOR_3SEC_ISR();
void TIMER1_MOTOR_15SEC_ISR();
void TIMER1_ALARM_ISR();

#endif /* APP_APP_H_ */
