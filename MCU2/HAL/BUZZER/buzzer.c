

/*************************** Section: Includes *********************************/
#include "buzzer.h"


/*************************** Section: Static Variables Declarations ************/
/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/

Std_ReturnType HAL_BUZZER_init(void) {
    HAL_GPIO_setPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
    return E_OK;
}

Std_ReturnType HAL_BUZZER_setState(Buzzer_State_t state) {
    HAL_GPIO_setPinValue(BUZZER_PORT_ID, BUZZER_PIN_ID, state);
}



/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/