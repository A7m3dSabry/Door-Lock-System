


/*************************** Section: Includes *********************************/


#include "twi.h"


/*************************** Section: Static Variables Declarations ************/
/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/



Std_ReturnType HAL_TWI_init(const TWI_Config_t *config) {

    Std_ReturnType ret = E_OK;

    if (config == NULL) {
        ret = E_NOT_OK;
    } else {
        TWCR = (1 << TWEN);
        TWAR = config->address;
        TWSR = 0x00; /* assuming it is equal to 0 always and get TWBR based on that assumption */
        TWBR = (uint8_t) (((F_CPU / ((config->bit_rate) * 1000)) - 16) / 2);
    }

    return ret;


}

Std_ReturnType HAL_TWI_start() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);
    while (BIT_IS_CLEAR(TWCR, TWINT)) {}
    return E_OK;
}

Std_ReturnType HAL_TWI_stop() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);
    return E_OK;
}

Std_ReturnType HAL_TWI_writeByte(uint8_t byte) {
    TWDR = byte;

    TWCR = (1 << TWEN) | (1 << TWINT);
    while (BIT_IS_CLEAR(TWCR, TWINT)) {}

    return E_OK;
}

Std_ReturnType HAL_TWI_readByteWithACK(uint8_t *value) {
    Std_ReturnType ret = E_OK;

    if (value == NULL) {
        ret = E_NOT_OK;
    } else {
        TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
        while (BIT_IS_CLEAR(TWCR, TWINT)) {}
        *value = TWDR;
    }
    return ret;

}

Std_ReturnType HAL_TWI_readByteWithNACK(uint8_t *value) {
    Std_ReturnType ret = E_OK;

    if (value == NULL) {
        ret = E_NOT_OK;
    } else {

        TWCR = (1 << TWEN) | (1 << TWINT);

        while (BIT_IS_CLEAR(TWCR, TWINT)) {}
        *value = TWDR;
    }
    return ret;

}

Std_ReturnType HAL_TWI_getStatus(uint8_t *value) {
    Std_ReturnType ret = E_OK;

    if (value == NULL) {
        ret = E_NOT_OK;
    } else {

        *value = TWSR & 0xF8;
    }
    return ret;

}


/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/