

/*************************** Section: Includes *********************************/
#include "keypad.h"


/*************************** Section: Local Variables Declarations *************/

#if (STANDARD_KEYPAD == FALSE)

#if (KEYPAD_NUM_COLS == 3)

static uint8_t KEYPAD_4x3_adjustKeyNumber(uint8_t button_number);

#elif (KEYPAD_NUM_COLS == 4)

static uint8_t KEYPAD_4x4_adjustKeyNumber(uint8_t button_number);

#endif

#endif /* ---> STANDARD_KEYPAD */

/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/

Std_ReturnType KEYPAD_init() {
    HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID, PIN_INPUT);
    HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 1, PIN_INPUT);
    HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 2, PIN_INPUT);
    HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + 3, PIN_INPUT);

    HAL_GPIO_setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, PIN_INPUT);
    HAL_GPIO_setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 1, PIN_INPUT);
    HAL_GPIO_setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 2, PIN_INPUT);
    HAL_GPIO_setPinDirection(PORTC_ID, PIN_0, PIN_INPUT);
#if(KEYPAD_NUM_COLS == 4)
    HAL_GPIO_setPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 3, PIN_INPUT);
#endif

    HAL_GPIO_setPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID, STD_HIGH);
    HAL_GPIO_setPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 1, STD_HIGH);
    HAL_GPIO_setPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 2, STD_HIGH);
    HAL_GPIO_setPinValue(PORTC_ID, PIN_0, STD_HIGH);
#if(KEYPAD_NUM_COLS == 4)
    HAL_GPIO_setPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + 3, STD_HIGH);
#endif
    return E_OK;
}

Std_ReturnType KEYPAD_getPressedKey(uint8_t *key) {
    Std_ReturnType ret = E_OK;

    if (key == NULL) {
        ret = E_NOT_OK;
    } else {


        uint8_t col, row;
        uint8_t value;
        while (1) {
            for (row = 0; row < KEYPAD_NUM_ROWS; row++) {
                HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_OUTPUT);
                HAL_GPIO_setPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, KEYPAD_BUTTON_PRESSED);

                for (col = 0; col < KEYPAD_NUM_COLS; col++) {

                    HAL_GPIO_readPinValue(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, &value);
                    if (value == KEYPAD_BUTTON_PRESSED) {
#if (STANDARD_KEYPAD == FALSE)
#if (KEYPAD_NUM_COLS == 3)
                        HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
                        *key = KEYPAD_4x3_adjustKeyNumber( (row*KEYPAD_NUM_COLS)+col+1 );
#elif (KEYPAD_NUM_COLS == 4)
                        HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);
                        *key = KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
#endif
#elif (STANDARD_KEYPAD == TRUE)
                        HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT);
                        *key = ((row*KEYPAD_NUM_COLS)+col+1);
#endif /* ---> STANDARD_KEYPAD */
                        break;
                    }
                    HAL_GPIO_setPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row, PIN_INPUT);


                }
                if (value == KEYPAD_BUTTON_PRESSED) {
                    break;
                }
            }
        }

    }
    return ret;
}

#if (STANDARD_KEYPAD == FALSE)

#if (KEYPAD_NUM_COLS == 3)

static uint8_t KEYPAD_4x3_adjustKeyNumber(uint8_t button_number)
{
    uint8_t keypad_button = 0;
    switch(button_number)
    {
    case 10:
        keypad_button = '*';
        break;
    case 11:
        keypad_button = 0;
        break;
    case 12:
        keypad_button = '#';
        break;
    default:
        keypad_button = button_number;
        break;
    }
    return keypad_button;
}

#elif (KEYPAD_NUM_COLS == 4)


static uint8_t KEYPAD_4x4_adjustKeyNumber(uint8_t button_number) {
    uint8_t keypad_button = 0;
    switch (button_number) {
        case 1:
            keypad_button = 7;
            break;
        case 2:
            keypad_button = 8;
            break;
        case 3:
            keypad_button = 9;
            break;
        case 4:
            keypad_button = '%';
            break;
        case 5:
            keypad_button = 4;
            break;
        case 6:
            keypad_button = 5;
            break;
        case 7:
            keypad_button = 6;
            break;
        case 8:
            keypad_button = '*';
            break;
        case 9:
            keypad_button = 1;
            break;
        case 10:
            keypad_button = 2;
            break;
        case 11:
            keypad_button = 3;
            break;
        case 12:
            keypad_button = '-';
            break;
        case 13:
            keypad_button = 13;
            break;
        case 14:
            keypad_button = 0;
            break;
        case 15:
            keypad_button = '=';
            break;
        case 16:
            keypad_button = '+';
            break;
        default:
            keypad_button = button_number;
            break;
    }
    return keypad_button;
}

#endif

#endif    /* STANDARD_KEYPAD */


/*************************** Section: Interrupt Methods Implementations ********/
/*************************** Section: Helper Methods Implementations  **********/
