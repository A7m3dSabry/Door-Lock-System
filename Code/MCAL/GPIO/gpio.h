
#ifndef GPIO_H_
#define GPIO_H_

/*************************** Section: Includes *********************************/

#include "../../LIB/std_types.h"
#include "avr/io.h"
/*************************** Section: Macro Definitions ************************/

#define MAX_NUM_OF_PORTS      (4)
#define NUM_OF_PINS_PER_PORT  (8)


typedef enum {
    PORTA_ID,
    PORTB_ID,
    PORTC_ID,
    PORTD_ID

} GPIO_PortID_t;

#define PIN_0                (0)
#define PIN_1                (1)
#define PIN_2                (2)
#define PIN_3                (3)
#define PIN_4                (4)
#define PIN_5                (5)
#define PIN_6                (6)
#define PIN_7                (7)

/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/


typedef enum {
    PIN_INPUT = 0,
    PIN_OUTPUT = 1
} GPIO_PinDirectionType;

typedef enum {
    PORT_INPUT,
    PORT_OUTPUT
} GPIO_PortDirectionType;

/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType HAL_GPIO_setPinDirection(GPIO_PortID_t portID, uint8_t pin, GPIO_PinDirectionType dir);


Std_ReturnType HAL_GPIO_setPinValue(GPIO_PortID_t port_id, uint8_t pin, uint8_t value);


Std_ReturnType HAL_GPIO_readPinValue(GPIO_PortID_t port_id, uint8_t pin, uint8_t *value);


Std_ReturnType HAL_GPIO_setPortDirection(GPIO_PortID_t portId, GPIO_PortDirectionType direction);

Std_ReturnType HAL_GPIO_setPortValue(GPIO_PortID_t portId, uint8_t value);

Std_ReturnType HAL_GPIO_readPortValue(GPIO_PortID_t port_id, uint8_t *value);

#endif /* GPIO_H_ */
