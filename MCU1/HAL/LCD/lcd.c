

/*************************** Section: Includes *********************************/

#include "lcd.h"

/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/


Std_ReturnType HAL_LCD_init(void) {
    HAL_GPIO_setPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
    HAL_GPIO_setPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

    _delay_ms(20);

#if(LCD_DATA_BITS_MODE == 8)
    HAL_GPIO_setPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);
    HAL_LCD_sendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 4)
    HAL_GPIO_setPinDirection(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, PIN_OUTPUT);
    HAL_GPIO_setPinDirection(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, PIN_OUTPUT);
    HAL_GPIO_setPinDirection(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, PIN_OUTPUT);
    HAL_GPIO_setPinDirection(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, PIN_OUTPUT);

    HAL_LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
    HAL_LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

    HAL_LCD_sendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#endif

    HAL_LCD_sendCommand(LCD_CURSOR_OFF);
    HAL_LCD_sendCommand(LCD_CLEAR_COMMAND);
}

Std_ReturnType HAL_LCD_sendCommand(uint8_t command) {
    HAL_GPIO_setPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, STD_LOW);
    _delay_ms(1);
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_HIGH);
    _delay_ms(1);

#if(LCD_DATA_BITS_MODE == 8)

    /* Send Command */
    HAL_GPIO_setPortValue(LCD_DATA_PORT_ID, command);
    _delay_ms(1);
    /* Set Enable to High */
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_LOW);
    _delay_ms(1);

#elif(LCD_DATA_BITS_MODE == 4)

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,4));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,5));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,6));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,7));

    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_LOW);
    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_HIGH);
    _delay_ms(1);

    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(command,0));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(command,1));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(command,2));
    GPIO_writePin(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(command,3));

    _delay_ms(1);
    GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_LOW);
    _delay_ms(1);

#endif
}

Std_ReturnType HAL_LCD_displayCharacter(uint8_t data) {
    /* Set RS to High */
    HAL_GPIO_setPinValue(LCD_RS_PORT_ID, LCD_RS_PIN_ID, STD_HIGH);
    _delay_ms(1);
    /* Set Enable to High */
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_HIGH);
    _delay_ms(1);

#if(LCD_DATA_BITS_MODE == 8)

    /* Send Command */
    HAL_GPIO_setPortValue(LCD_DATA_PORT_ID, data);
    _delay_ms(1);
    /* Set Enable to High */
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_LOW);
    _delay_ms(1);


#elif(LCD_DATA_BITS_MODE == 4)
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data,4));
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data,5));
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data,6));
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data,7));

    _delay_ms(1);
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_LOW);
    _delay_ms(1);
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_HIGH);
    _delay_ms(1);

    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB4_PIN_ID, GET_BIT(data,0));
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB5_PIN_ID, GET_BIT(data,1));
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB6_PIN_ID, GET_BIT(data,2));
    HAL_GPIO_setPinValue(LCD_DATA_PORT_ID, LCD_DB7_PIN_ID, GET_BIT(data,3));

    _delay_ms(1);
    HAL_GPIO_setPinValue(LCD_E_PORT_ID, LCD_E_PIN_ID, STD_LOW);
    _delay_ms(1);

#endif
}

Std_ReturnType HAL_LCD_displayString(int8_t *string) {
    while (*string++ != 0) {
        HAL_LCD_displayCharacter(*string);
    }

}

Std_ReturnType HAL_LCD_clearScreen() {
    HAL_LCD_sendCommand(LCD_CLEAR_COMMAND);
}

Std_ReturnType HAL_LCD_moveCursor(uint8_t row, uint8_t column) {
    uint8_t LCD_cursorAdress;
    switch (row) {
        case 0:
            LCD_cursorAdress = column;
            break;
        case 1:
            LCD_cursorAdress = 0x40 + column;
            break;
        case 2:
            LCD_cursorAdress = 0x10 + column;
            break;
        case 3:
            LCD_cursorAdress = 0x50 + column;
            break;
    }
    LCD_cursorAdress |= LCD_SET_CURSOR_LOCATION;
    HAL_LCD_sendCommand(LCD_cursorAdress);
}

Std_ReturnType HAL_LCD_displayStringRowColumn(uint8_t row, uint8_t column, int8_t *string) {
    HAL_LCD_moveCursor(row, column);
    HAL_LCD_displayString(string);
}

Std_ReturnType HAL_LCD_intToString(int number) {
    char buffer[16];
    itoa(number, buffer, 10);
    HAL_LCD_displayString(buffer);
}

/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/
