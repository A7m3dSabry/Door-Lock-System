
#ifndef MCAL_TWI_TWI_H_
#define MCAL_TWI_TWI_H_

/*************************** Section: Includes *********************************/
#include "avr/io.h"
#include "../../LIB/std_types.h"
/*************************** Section: Macro Definitions ************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/

typedef struct{
 uint8_t address;
 uint16_t bit_rate; /* in Kbps */
}TWI_Config_t;

/*************************** Section: Methods Prototypes ***********************/

Std_ReturnType HAL_TWI_init(const TWI_Config_t * config);

Std_ReturnType HAL_TWI_start();


Std_ReturnType HAL_TWI_stop();


Std_ReturnType HAL_TWI_writeByte(uint8_t byte);


Std_ReturnType HAL_TWI_readByteWithACK(uint8_t *value);

Std_ReturnType HAL_TWI_readByteWithNACK(uint8_t *value);


Std_ReturnType HAL_TWI_getStatus(uint8_t *value);

#endif /* MCAL_TWI_TWI_H_ */
