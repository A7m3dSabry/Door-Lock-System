

/*************************** Section: Includes *********************************/
#include "APP/app.h"


/*************************** Section: Static Variables Declarations ************/

UART_Config_t UART_Configuration = {9600, '#', UART_1_STOP_BIT, UART_8_BITS, UART_DISABLED_PARTIY, POLLING};
TWI_Config_t TWI_Configuration = {1, 400}; /* Slave Address = 1 , Baud rate = 400 Kbps */
DCMotor_t dcMotor = {PORTA_ID, PIN_0, PIN_1, PIN_2};

/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/

int main(void) {
    /**** Init Modules ****/
    /* 1- I2C */
    HAL_TWI_init(&TWI_Configuration);
    /* 2- Buzzer */
    HAL_BUZZER_init();
    /* 3- Motor */
    HAL_DCMotor_Init(&dcMotor);
    /* 4- UART */
    HAL_UART_init(&UART_Configuration);

    sei();
    uint8_t MSG = 0;
    HAL_UART_receiveByte(&MSG);
    while ( MSG!= MC_Ready) {}

    APP_isPasswordSet(); /* To check if password is set in the EEPROM or not for first time entring the program */

    while (1) {

        /* waiting MCU1 to send the message to trigger start */
        HAL_UART_receiveByte(&MSG);
        switch (MSG) {
            
            /* In case MCU1 wants to set the password or update it */
            case MSG_UpdatePassword:
                APP_updatePassword();
                break;
            
            /* In case MCU1 wants to enter ERROR state and turn the alarm on */
            case MSG_TurnOnAlarm:
                APP_alarm(); /* call the function that is responsible of turning alarm on for 60 seconds */
                break;
            
            /* In case MCU1 wants to enter open the door */
            case MSG_Motor:
                APP_door();/* call the function that is responsible of opening the door */
                break;
            
            /* In case MCU1 wants to know the password saved in EEPROM */
            case MSG_checkPassword:
                APP_checkPassword();
                break;
            case default:
                break;

        }
    }
}


/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/

