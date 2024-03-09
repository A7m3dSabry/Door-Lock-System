
#ifndef HAL_BUZZER_BUZZER_H_
#define HAL_BUZZER_BUZZER_H_



/*************************** Section: Includes *********************************/


#include "../../LIB/std_types.h"
#include "../../MCAL/GPIO/gpio.h"

/*************************** Section: Macro Definitions ************************/

#define BUZZER_PORT_ID                    PORTB_ID
#define BUZZER_PIN_ID                    PIN_0

/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/

typedef enum {
    Buzzer_State_OFF=STD_LOW,
    Buzzer_State_ON=STD_HIGH,
} Buzzer_State_t;
/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType HAL_BUZZER_init(void);

Std_ReturnType HAL_BUZZER_setState(Buzzer_State_t state);

#endif /* HAL_BUZZER_BUZZER_H_ */
