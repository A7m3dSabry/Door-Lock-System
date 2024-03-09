
#ifndef MOTOR_H_
#define MOTOR_H_

/*************************** Section: Includes *********************************/

#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/PWM0/pwm0.h"

/*************************** Section: Macro Definitions ************************/
/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/

typedef enum {
    DCMotor_STOP,
    DCMotor_CW,
    DCMotor_CCW
} DCMotor_state_t;

typedef struct {
    GPIO_PortID_t portId;
    uint8_t pin_in1;
    uint8_t pin_in2;
    uint8_t pin_E;
} DCMotor_t;
/*************************** Section: Methods Prototypes ***********************/


Std_ReturnType HAL_DCMotor_Init(DCMotor_t *config);

Std_ReturnType HAL_DCMotor_Rotate(DCMotor_t *config,DCMotor_state_t state, uint8_t speed);

#endif /* MOTOR_H_ */
