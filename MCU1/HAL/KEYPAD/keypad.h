

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

/*************************** Section: Includes *********************************/


#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

/*************************** Section: Macro Definitions ************************/

#define STANDARD_KEYPAD				FALSE

#define KEYPAD_NUM_COLS				4
#define	KEYPAD_NUM_ROWS				4

#define	KEYPAD_ROW_PORT_ID			PORTB_ID
#define	KEYPAD_FIRST_ROW_PIN_ID		PIN_0

#define	KEYPAD_COL_PORT_ID			PORTB_ID
#define	KEYPAD_FIRST_COL_PIN_ID		PIN_4

#define KEYPAD_BUTTON_PRESSED            STD_LOW
#define KEYPAD_BUTTON_RELEASED           STD_HIGH

/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/
/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType KEYPAD_init(void);

Std_ReturnType KEYPAD_getPressedKey(uint8_t *value);

#endif /* HAL_KEYPAD_KEYPAD_H_ */
