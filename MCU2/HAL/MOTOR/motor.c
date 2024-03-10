


/*************************** Section: Includes *********************************/

#include "motor.h"
/*************************** Section: Static Variables Declarations ************/
/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/


Std_ReturnType HAL_DCMotor_Init(DCMotor_t *config) {

    Std_ReturnType ret = E_OK;

    if (config == NULL) {
        ret = E_NOT_OK;
    } else {

        /* setting the direction of the motor pins */
        HAL_GPIO_setPinDirection(config->portId, config->pin_in1, PIN_OUTPUT); /* Input1 */
        HAL_GPIO_setPinDirection(config->portId, config->pin_in2, PIN_OUTPUT); /* Inupt2 */

        /* Stop the motor */
        HAL_GPIO_setPinValue(config->portId, config->pin_in1, STD_LOW);
        HAL_GPIO_setPinValue(config->portId, config->pin_in2, STD_LOW);
    }
    return ret;

}

Std_ReturnType HAL_DCMotor_Rotate(DCMotor_t *config, DCMotor_state_t state, uint8_t speed) {
    /* clearing the motor so we can change it state */
    HAL_GPIO_setPinValue(config->portId, config->pin_in1, STD_LOW);
    HAL_GPIO_setPinValue(config->portId, config->pin_in2, STD_LOW);

    HAL_GPIO_setPinValue(config->portId, config->pin_in1, READ_BIT(state, 0));
    HAL_GPIO_setPinValue(config->portId, config->pin_in2, READ_BIT(state, 1));

    PWM_Timer0_Start(speed);
    return E_OK;
}

/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/