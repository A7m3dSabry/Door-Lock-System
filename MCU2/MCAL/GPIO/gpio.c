

/**************	Section: Includes *********************************/


#include "gpio.h"

/**************	Section: Local Variables Declarations *************/
/**************	Section: Helper Methods Prototypes  ***************/
/**************	Section: Methods Implementations ******************/

Std_ReturnType HAL_GPIO_setPinDirection(GPIO_PortID_t portID, uint8_t pin, GPIO_PinDirectionType dir) {
    Std_ReturnType ret = E_OK;

    if ((pin >= NUM_OF_PINS_PER_PORT) || (portID >= MAX_NUM_OF_PORTS)) {
        ret = E_NOT_OK;
    } else {
        uint32_t *port = NULL;
        switch (portID) {

            case PORTA_ID:
                port = &DDRA;
                break;
            case PORTB_ID:
                port = &DDRB;
                break;
            case PORTC_ID:
                port = &DDRC;

                break;
            case PORTD_ID:
                port = &DDRD;

                break;
        }
        if (dir == PIN_OUTPUT) {
            SET_BIT(*port, pin);
        } else {
            CLEAR_BIT(*port, pin);
        }
    }

    return ret;
}


Std_ReturnType HAL_GPIO_setPinValue(GPIO_PortID_t port_id, uint8_t pin, uint8_t value) {
    Std_ReturnType ret = E_OK;
    if ((pin >= NUM_OF_PINS_PER_PORT) || (port_id >= MAX_NUM_OF_PORTS)) {
        ret = E_NOT_OK;
    } else {
        uint32_t *port = NULL;
        switch (port_id) {
            case PORTA_ID:
                port = &PORTA;
                break;
            case PORTB_ID:
                port = &PORTB;
                break;
            case PORTC_ID:
                port = &PORTC;
                break;
            case PORTD_ID:
                port = &PORTD;
                break;
        }
        FORCE_BIT(*port, 1 << pin, value);
    }
    return ret;
}


Std_ReturnType HAL_GPIO_readPinValue(GPIO_PortID_t port_id, uint8_t pin, uint8_t *value) {

    Std_ReturnType ret = E_OK;
    if ((pin >= NUM_OF_PINS_PER_PORT) || (port_id >= MAX_NUM_OF_PORTS)) {
        ret = E_NOT_OK;
    } else {

        uint8_t GPIO_outPin = STD_LOW;
        uint32_t *reg = NULL;
        switch (port_id) {
            case PORTA_ID:
                reg = &PINA;
                break;
            case PORTB_ID:
                reg = &PINB;
                break;
            case PORTC_ID:
                reg = &PINC;
                break;
            case PORTD_ID:
                reg = &PIND;
                break;
        }
        *value = READ_BIT(*reg, 1 << pin);
    }
    return ret;
}


Std_ReturnType HAL_GPIO_setPortDirection(GPIO_PortID_t portId, GPIO_PortDirectionType direction) {

    Std_ReturnType ret = E_OK;
    if (portId >= MAX_NUM_OF_PORTS) {
        ret = E_NOT_OK;
    } else {

        switch (portId) {
            case PORTA_ID:
                DDRA = direction;
                break;
            case PORTB_ID:
                DDRB = direction;
                break;
            case PORTC_ID:
                DDRC = direction;
                break;
            case PORTD_ID:
                DDRD = direction;
                break;
        }
    }
    return ret;
}

Std_ReturnType HAL_GPIO_setPortValue(GPIO_PortID_t portId, uint8_t value) {
    Std_ReturnType ret = E_OK;

    if ((portId >= MAX_NUM_OF_PORTS)) {
        ret = E_NOT_OK;
    } else {
        switch (portId) {
            case PORTA_ID:
                PORTA = value;
                break;
            case PORTB_ID:
                PORTB = value;
                break;
            case PORTC_ID:
                PORTC = value;
                break;
            case PORTD_ID:
                PORTD = value;
                break;
        }
    }
    return ret;
}


Std_ReturnType HAL_GPIO_readPortValue(GPIO_PortID_t port_id, uint8_t *value) {


    Std_ReturnType ret = E_OK;
    if ((port_id >= MAX_NUM_OF_PORTS)) {
        ret = E_NOT_OK;
    } else {
        switch (port_id) {
            case PORTA_ID:
                *value = PINA;
                break;
            case PORTB_ID:
                *value = PINB;
                break;
            case PORTC_ID:
                *value = PINC;
                break;
            case PORTD_ID:
                *value = PIND;
                break;
        }
    }
    return ret;
}

/**************	Section: Helper Methods Implementations  **********/
