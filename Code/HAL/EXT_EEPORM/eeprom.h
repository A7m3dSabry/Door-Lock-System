
#ifndef HAL_EXT_EEPORM_EEPROM_H_
#define HAL_EXT_EEPORM_EEPROM_H_



/*************************** Section: Includes *********************************/

#include "util/delay.h"
#include "../../LIB/std_types.h"
#include "../../MCAL/TWI/twi.h"

/*************************** Section: Macro Definitions ************************/



/*************************** Section: Macro Functions **************************/
/*************************** Section: Data Types *******************************/
/*************************** Section: Methods Prototypes ***********************/


uint8_t HAL_EEPROM_writeByte(uint16_t address, uint8_t byte);

uint8_t HAL_EEPROM_readByte(uint16_t address, uint8_t *value);

#endif /* HAL_EXT_EEPORM_EEPROM_H_ */
