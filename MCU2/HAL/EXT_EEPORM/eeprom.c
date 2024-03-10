
/*************************** Section: Includes *********************************/

#include "../EXT_EEPORM/eeprom.h"

/*************************** Section: Static Variables Declarations ************/
/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/


Std_ReturnType HAL_EEPROM_writeByte(uint16_t address, uint8_t byte) {
    uint8_t twi_return = 0XFF;
    Std_ReturnType ret = E_OK;
    _delay_ms(10);

    /* Send Start */
    HAL_TWI_start();
    HAL_TWI_getStatus(&twi_return);
    if (twi_return != TWI_START) {
        ret = E_NOT_OK;
    }

    /* Send Address */

    if (ret == E_OK) {
        HAL_TWI_writeByte((uint8_t) (((address & 0x0700) >> 7) | (0xA0)));
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MT_SLA_W_ACK)
            ret = E_NOT_OK;
    }

    if (ret == E_OK) {
        HAL_TWI_writeByte((uint8_t) address);
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MT_DATA_ACK)
            ret = E_NOT_OK;
    }


    /* Send Byte Data */
    if (ret == E_OK) {
        HAL_TWI_writeByte(byte);
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MT_DATA_ACK)
            ret = E_NOT_OK;
    }

    /* Stop I2C */
    if (ret == E_OK) {
        HAL_TWI_stop();

    }

    return ret;
}

Std_ReturnType HAL_EEPROM_readByte(uint16_t address, uint8_t *value) {

    Std_ReturnType ret = E_OK;
    uint8_t twi_return;

    _delay_ms(10);

    /* Send Start */
    HAL_TWI_start();
    HAL_TWI_getStatus(&twi_return);
    if (twi_return != TWI_START) {
        ret = E_NOT_OK;
    }

    /* Send Address */
    if (ret == E_OK) {
        HAL_TWI_writeByte((uint8_t) (((address & 0x0700) >> 7) | (0xA0)));
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MT_SLA_W_ACK)
            ret = E_NOT_OK;
    }

    if (ret == E_OK) {
        HAL_TWI_writeByte((uint8_t) address);
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MT_DATA_ACK)
            ret = E_NOT_OK;
    }

    // Repeated Start
    if (ret == E_OK) {
        HAL_TWI_start();
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_REP_START) {
            ret = E_NOT_OK;
        }
    }

    if (ret == E_OK) {
        HAL_TWI_writeByte((uint8_t) ((0xA0) | ((address & 0x0700) >> 7) | 1));
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MT_SLA_R_ACK)
            ret = E_NOT_OK;

    }

    if (ret == E_OK) {
        HAL_TWI_readByteWithNACK(value);
        HAL_TWI_getStatus(&twi_return);
        if (twi_return != TWI_MR_DATA_NACK)
            ret = E_OK;
    }

    if (ret == E_OK) {

        HAL_TWI_stop();
    }
    return ret;
}

/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/
