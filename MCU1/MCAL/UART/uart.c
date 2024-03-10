

/*************************** Section: Includes *********************************/
#include "uart.h"


/*************************** Section: Static Variables Declarations ************/
static uint8_t endStringChar;

static volatile void (*uart_callback)(void) = NULL;

/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/


Std_ReturnType HAL_UART_init(const UART_Config_t *config) {

    Std_ReturnType ret = E_OK;

    if (config == NULL) {
        ret = E_NOT_OK;
    } else {
        uint16_t temp_baudrate;
        UCSRA = (1 << U2X);
        UCSRB = (1 << RXEN) | (1 << TXEN);
        UCSRB = (UCSRB & CLEAR_RECEIVE_METHOD_MASK) | ((config->RECEVIE_METHOD << 7));

        SET_BIT(UCSRC, URSEL);
        UCSRC = (UCSRC & CLEAR_CHAR_SIZE_MASK) | ((config->charSize) << 1);
        UCSRC = (UCSRC & CLEAR_STOP_BITS_MASK) | ((config->stopBits) << 3);
        UCSRC = (UCSRC & CLEAR_PARITY_MASK) | ((config->parity) << 4);

        CLEAR_BIT(UBRRH, URSEL);
        temp_baudrate = (uint16)(((F_CPU / (config->baudRate * 8UL))) - 1);
        UBRRH = temp_baudrate >> 8;
        UBRRL = temp_baudrate;

        endStringChar = config->END_SRTING;

    }
    return ret;


}

Std_ReturnType HAL_UART_sendByte(const uint8_t data) {
    while (BIT_IS_CLEAR(UCSRA, UDRE)) {}
    UDR = data;
    return E_OK;
}

Std_ReturnType HAL_UART_receiveByte(uint8_t *value) {
    Std_ReturnType ret = E_OK;

    if (value == NULL) {
        ret = E_NOT_OK;
    } else {
        while (BIT_IS_CLEAR(UCSRA, RXC)) {}
        *value = UDR;
    }
    return ret;


}

Std_ReturnType HAL_UART_sendString(const uint8_t *str) {

    Std_ReturnType ret = E_OK;

    if (str == NULL) {
        ret = E_NOT_OK;
    } else {

        for (uint8_t i = 0; str[i] != '\0'; i++) {
            HAL_UART_sendByte(str[i]);
        }
    }
    return ret;
}

Std_ReturnType HAL_UART_receiveString(uint8_t *str) {
    Std_ReturnType ret = E_OK;

    if (str == NULL) {
        ret = E_NOT_OK;
    } else {

        /* Loop and receive until endStringChar is received*/
        do {
            HAL_UART_receiveByte(str);
        } while (*str++ != endStringChar);
    }
    return ret;
}

Std_ReturnType HAL_UART_registerCallBack(void(*a_ptr)(void)) {
    uart_callback = (volatile void (*)(void)) a_ptr;
    return E_OK;
}


/*************************** Section: Interrupt Methods Implementations ********/

ISR(USART_RXC_vect){
        if (uart_callback != NULL)
        {
            (*uart_callback)();
        }
}

/*************************** Section: Helper Methods Implementations  **********/

