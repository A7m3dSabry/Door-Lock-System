
/*************************** Section: Includes *********************************/

#include "timer1.h"

/*************************** Section: Local Variables Declarations *************/


static volatile void (*timer1CompareCallback)(void) = NULL; /* to store the address of the function */
static volatile void (*timer1OverflowCallback)(void) = NULL; /* to store the address of the function */

/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/

Std_ReturnType HAL_TIMER1_init(Timer1_Config_t *config) {
    Std_ReturnType ret = E_OK;

    if (config == NULL) {
        ret = E_NOT_OK;
    } else {
        TCCR1A = (1 << FOC1A) | (1 << FOC1B);
        TCCR1B = (config->mode << WGM12);
        TCCR1B = (TCCR1B & 0xF8) | (config->prescaler);

        TCNT1 = config->initial_value;
        if (config->mode == COMPARE) {
            OCR1A = config->compare_value;
        }
        TIMSK |= (1 << OCIE1A);
    }
    return ret;

}

Std_ReturnType HAL_TIMER1_deInit() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    OCR1A = 0;
    return E_OK;
}


Std_ReturnType HAL_TIMER1_COMP_setCallBack(void(*a_ptr)(void)) {
    timer1CompareCallback = (volatile void (*)(void)) a_ptr;
    return E_OK;
}

Std_ReturnType HAL_TIMER1_OVF_setCallBack(void(*a_ptr)(void)) {
    timer1OverflowCallback = (volatile void (*)(void)) a_ptr;
    return E_OK;
}

/*************************** Section: Interrupt Methods Implementations ********/

ISR(TIMER1_COMPA_vect){
        if (timer1CompareCallback != NULL)
        {
            (*timer1CompareCallback)();
        }
}

ISR(TIMER1_OVF_vect){
        if (timer1CompareCallback != NULL)
        {
            (*timer1OverflowCallback)();
        }
}


/*************************** Section: Helper Methods Implementations  **********/
