

/*************************** Section: Includes *********************************/

#include "pwm0.h"

/*************************** Section: Static Variables Declarations ************/
/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/
/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/

Std_ReturnType PWM_Timer0_Start(uint8_t duty_cycle)
{

	TCNT0 = 0;
	OCR0 = (uint8_t)((uint16_t)(duty_cycle*255)/100) ;
	HAL_GPIO_setPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
    return E_OK;
}
