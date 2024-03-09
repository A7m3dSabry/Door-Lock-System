
/*************************** Section: Includes *********************************/
#include "app.h"


/*************************** Section: Static Variables Declarations ************/
/*************************** Section: Local Variables Declarations *************/

uint8_t UART_String[20];
uint8_t PasswordState;
uint8_t Password[PASSWORD_SIZE];
uint8_t counter_ticks = 0;
uint8_t flag_exitMotor = 0;
uint8_t counter_motorUnlocking = 0;
uint8_t flag_exitAlarm = 0;

Timer1_Config_t TIMER1_Configuration = {0, TIMER1_OCR1A, TIMER1_FCPU_1024, COMPARE};


/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/
void APP_isPasswordSet() {
    /* Check if There is Password in EEPROM */
    HAL_EEPROM_readByte(Password_Is_Set_Address, &PasswordState);
    /* Send Password state to Handle either there was a password or not */
    HAL_UART_sendByte(PasswordState);
}

void APP_readPassword() {
    for (uint8_t i = 0; i < PASSWORD_SIZE; i++) {
        HAL_EEPROM_readByte(Password_Address + i, (Password + i));
    }
}

void APP_updatePassword() {
    for (uint8_t k = 0; k < PASSWORD_SIZE; k++) {
        HAL_UART_receiveByte(Password + k); /* wait until get new password from mcu1 */
        HAL_EEPROM_writeByte(Password_Address + k, Password[k]); /* Save new password in the eeprom */
    }
    HAL_EEPROM_writeByte(Password_Is_Set_Address, PasswordSET); /* update password state to set */
}

void APP_checkPassword() {
    uint8_t checkPassword[PASSWORD_SIZE]; /* Variable to save the password from the keypad in MCU1 */
    APP_readPassword(); /* Update the Password variable to be = to the password in the EEPROM */
    for (uint8_t k = 0; k < PASSWORD_SIZE; k++) /* Receiving the password from MCU1 */
    {
        HAL_UART_receiveByte(&checkPassword[k]);
        HAL_UART_sendByte(MC_Ready);
    }
    for (uint8_t j = 0; j < PASSWORD_SIZE; j++) /* check if they are matched or not */
    {
        if (Password[j] != checkPassword[j]) {
            HAL_UART_sendByte(MSG_UnMatched);
            return;
        }
    }
    HAL_UART_sendByte(MSG_Matched);
}

void APP_alarm() {
    counter_ticks = 0;
    flag_exitAlarm = 0;

    /* initialize the timer module with the alarm ISR */
    HAL_TIMER1_COMP_registerCallBack(TIMER1_ALARM_ISR);
    /* init timer_1 configuration */
    HAL_TIMER1_init(&TIMER1_Configuration);
    /* set buzzer to on */
    HAL_BUZZER_setState(Buzzer_State_ON);
    /* wait exitAlarm flag to turn off the buzzer(60s) */
    while (flag_exitAlarm == 0) {}
    /* set buzzer to off */
    HAL_BUZZER_setState(Buzzer_State_OFF);
}

void APP_door() {
    counter_ticks = 0;
    /* initialize timer with motor 15sec isr */
    HAL_TIMER1_COMP_registerCallBack(TIMER1_MOTOR_15SEC_ISR);
    /* Initialize Motor Configuration */
    HAL_TIMER1_init(&TIMER1_Configuration);
    /* Open The Door */
    HAL_DCMotor_Rotate(&dcMotor, DCMotor_CW, 100);
    flag_exitMotor = 0;
    while (flag_exitMotor == 0) {}
}

/*************************** Section: Interrupt Callbacks Implementations ******/

void TIMER1_MOTOR_15SEC_ISR(void) {
    counter_ticks++;
    if (counter_ticks == 15) {
        counter_ticks = 0;
        /* Check if the Motor is in the initial state and we need to wai 15 seconds */
        if (counter_motorUnlocking == 0) {
            /* Waiting MC1 to be Ready because LCD writing is time-consuming */
            uint8_t temp;
            HAL_UART_receiveByte(&temp);
            /* The door is now open */
            HAL_DCMotor_Rotate(&dcMotor, DCMotor_STOP, 100);

            counter_motorUnlocking++;

            /* now we wait 3 seconds to lock the door again */
            HAL_TIMER1_COMP_registerCallBack(TIMER1_MOTOR_3SEC_ISR);
        } else if (counter_motorUnlocking ==
                   1) /* in this case we stop the motor since the door is locked successfully now */
        {
            counter_motorUnlocking = 0;
            flag_exitMotor = 1;
            HAL_DCMotor_Rotate(&dcMotor, DCMotor_STOP, 100); /* Stop the motor */
            HAL_TIMER1_deInit(); /* stop the timer */
        }
    }
}


void TIMER1_MOTOR_3SEC_ISR(void) {
    counter_ticks++;
    /* Wait for 3 Seconds */
    if (counter_ticks == 3) {
        counter_ticks = 0;
        uint8_t dummy_value;

        /* Wait for MC1 to Finish printing on lcd (since it's time-consuming task) */
        HAL_UART_receiveByte(&dummy_value);
        /* Start Locking the door */
        HAL_DCMotor_Rotate(&dcMotor, DCMotor_CCW, 100);

        /* wait for 15 seconds then stop the motor */
        HAL_TIMER1_COMP_registerCallBack(TIMER1_MOTOR_15SEC_ISR);
    }
}


void TIMER1_ALARM_ISR() {
    counter_ticks++;
    /* wait until number of seconds = 60 */
    if (counter_ticks == 60) {
        counter_ticks = 0;
        flag_exitAlarm = STD_ON;
        /* stop the timer */
        HAL_TIMER1_deInit();
    }
}



/*************************** Section: Helper Methods Implementations  **********/