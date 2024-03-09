
#ifndef PWM0_PWM0_H_
#define PWM0_PWM0_H_


/*************************** Section: Includes *********************************/

#include "avr/io.h"
#include "../../LIB/std_types.h"
#include "../GPIO/gpio.h"

/*************************** Section: Macro Definitions ************************/
/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/
/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType PWM_Timer0_Start(uint8_t duty_cycle);


#endif /* PWM0_PWM0_H_ */
