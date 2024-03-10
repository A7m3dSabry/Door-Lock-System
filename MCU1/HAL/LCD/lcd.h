#ifndef LCD_H_
#define LCD_H_

/*************************** Section: Includes *********************************/


#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"
#include "util/delay.h"
/*************************** Section: Macro Definitions ************************/

#define LCD_DATA_BITS_MODE	(8)

/* Checking if another mode used*/
#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))
#error "Number of Data bits should be 4 or 8"

#endif

#define LCD_RS_PORT_ID				PORTD_ID
#define LCD_RS_PIN_ID				PIN_0

#define LCD_E_PORT_ID				PORTD_ID
#define LCD_E_PIN_ID				PIN_2

#define LCD_DATA_PORT_ID			PORTC_ID



#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN_3
#define LCD_DB5_PIN_ID                 PIN_4
#define LCD_DB6_PIN_ID                 PIN_5
#define LCD_DB7_PIN_ID                 PIN_6

#endif

/****** LCD Commands ******/
#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80

/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/
/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType HAL_LCD_sendCommand(uint8_t command);

Std_ReturnType HAL_LCD_init(void);

Std_ReturnType HAL_LCD_displayCharacter(uint8_t data);

Std_ReturnType HAL_LCD_displayString(int8_t * string);

Std_ReturnType HAL_LCD_clearScreen();

Std_ReturnType HAL_LCD_moveCursor(uint8_t row, uint8_t column);

Std_ReturnType HAL_LCD_displayStringRowColumn(uint8_t row , uint8_t column , char * string);

Std_ReturnType HAL_LCD_intToString(int number);

#endif /* LCD_H_ */

