
#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

/*************************** Section: Includes *********************************/

#include "avr/io.h"
#include "avr/interrupt.h"
#include "../../LIB/std_types.h"
/*************************** Section: Macro Definitions ************************/

#define CLEAR_PARITY_MASK                0xCF
#define CLEAR_STOP_BITS_MASK            0xF7
#define CLEAR_CHAR_SIZE_MASK            0xF9
#define CLEAR_RECEIVE_METHOD_MASK        0x7F

/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/


typedef enum {
    UART_DISABLED_PARTIY,
    UART_EVEN_PARITY = 2,
    UART_ODD_PARITY
} UART_Parity_t;


typedef enum {
    UART_1_STOP_BIT,
    UART_2_STOP_BITS
} UART_StopBits_t;


typedef enum {
    UART_5_BITS,
    UART_6_BITS,
    UART_7_BITS,
    UART_8_BITS
} UART_CharSize_t;


typedef enum {
    POLLING,
    INTERRUPT
} UART_ReceiveMethod_t;


typedef struct {
    uint32_t baudRate;
    uint8_t END_SRTING; /* Receive the required string until the END_STRING char */
    UART_StopBits_t stopBits;
    UART_CharSize_t charSize; /* max 8-bit not 9 */
    UART_Parity_t parity;
    UART_ReceiveMethod_t RECEVIE_METHOD;
} UART_Config_t;


/*************************** Section: Methods Prototypes ***********************/



Std_ReturnType HAL_UART_init(const UART_Config_t *config);


Std_ReturnType HAL_UART_sendByte(const uint8_t data);


Std_ReturnType HAL_UART_receiveByte(uint8_t *value);


Std_ReturnType HAL_UART_sendString(const uint8_t *str);


Std_ReturnType HAL_UART_receiveString(uint8_t *str);


Std_ReturnType HAL_UART_registerCallBack(void(*a_ptr)(void));

#endif /* MCAL_UART_UART_H_ */
