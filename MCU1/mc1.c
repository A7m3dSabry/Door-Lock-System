

/*************************** Section: Includes *********************************/


#include "APP/app.h"
/*************************** Section: Global Variables Declarations ************/
UART_Config_t UART_Configuration = {9600,'#',UART_1_STOP_BIT,UART_8_BITS,UART_DISABLED_PARTIY,POLLING};


/*************************** Section: Local Variables Declarations *************/
/*************************** Section: Helper Methods Prototypes  ***************/
/*************************** Section: Methods Implementations ******************/



int main(void)
{
	/* Initialize different modules */
	KEYPAD_init();
	HAL_LCD_init();
	HAL_UART_init(&UART_Configuration);
	sei(); /* Enable Global interrupt */
	/* Telling MCU2 that MCU1 did the initialization stage */
	HAL_UART_sendByte(MC_Ready);
    /* To check if password is set in the EEPROM or not */
    uint8_t PasswordState = 0;
     HAL_UART_receiveByte(&PasswordState);

	if(PasswordState != PasswordSET)
	{
		/* If password not set we got to set password function */
		APP_setPassword();
	}

	while(1)
	{
		HAL_LCD_clearScreen();
		HAL_LCD_displayStringRowColumn(0, 0, "+ : Open Door");
		HAL_LCD_displayStringRowColumn(1, 0, "- : Change Pass");
		uint8_t menuKey; /* variable to decide  to open the door or change the password from the menu */
		do{
			 KEYPAD_getPressedKey(&menuKey);
		}while(menuKey != '-' && menuKey != '+'); /* wait until we get '+' or '-' */
		HAL_LCD_clearScreen();

		switch(menuKey)
		{
		case '+':
			APP_door(); /* Open the door function */
			break;

		case '-':
			APP_changePassword(); /* Change password function */
			break;
		}
	}
}


/*************************** Section: Interrupts Implementations ***************/
/*************************** Section: Helper Methods Implementations ***********/
