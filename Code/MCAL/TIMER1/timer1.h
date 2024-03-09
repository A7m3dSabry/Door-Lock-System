
#ifndef MCAL_TIMER1_TIMER1_H_
#define MCAL_TIMER1_TIMER1_H_

/*************************** Section: Includes *********************************/


#include "avr/io.h"
#include "avr/interrupt.h"
#include "../../LIB/std_types.h"
/*************************** Section: Macro Definitions ************************/
/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/

typedef enum {
    NORMAL,
    COMPARE
} Timer1_Mode_t;


typedef enum {
    TIMER1_OFF,
    TIMER1_FCPU_1,
    TIMER1_FCPU_8,
    TIMER1_FCPU_64,
    TIMER1_FCPU_256,
    TIMER1_FCPU_1024
} Timer1_Prescaler_t;


typedef struct {
    uint16_t initial_value;
    uint16_t compare_value;
    Timer1_Prescaler_t prescaler;
    Timer1_Mode_t mode;
} Timer1_Config_t;

/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType HAL_TIMER1_init(Timer1_Config_t *config);


Std_ReturnType HAL_TIMER1_deInit();


Std_ReturnType HAL_TIMER1_COMP_registerCallBack(void(*a_ptr)(void));


Std_ReturnType HAL_TIMER1_OVF_registerCallBack(void(*a_ptr)(void));

#endif /* MCAL_TIMER1_TIMER1_H_ */
