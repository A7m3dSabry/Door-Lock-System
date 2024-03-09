


/*************************** Section: Includes *********************************/

#include "timer1.h"

/*************************** Section: Static Variables Declarations ************/

/* address of compare callback interrupt */
static volatile void (*compareCallback)(void) = NULL;

/* address of overflow callback interrupt */
static volatile void (*overflowCallback)(void) = NULL;

/*************************** Section: Local Variables Declarations *************/
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

Std_ReturnType HAL_TIMER1_COMP_registerCallBack(void(*a_ptr)(void)) {
    compareCallback = (volatile void (*)(void)) a_ptr;
    return E_OK;
}

Std_ReturnType HAL_TIMER1_OVF_registerCallBack(void(*a_ptr)(void)) {
    overflowCallback = (volatile void (*)(void)) a_ptr;
    return E_OK;
}

/*************************** Section: Interrupt Methods Implementations ********/

ISR(TIMER1_COMPA_vect){
        if (compareCallback != NULL)
        {
            (*compareCallback)();
        }
}

ISR(TIMER1_OVF_vect){
        if (overflowCallback != NULL)
        {
            (*overflowCallback)();
        }
}

/*************************** Section: Helper Methods Implementations  **********/