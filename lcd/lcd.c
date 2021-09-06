/******************************************************************************
 *
 * [FILE NAME]:		<lcd.c>
 *
 * [MODULE]:		<LCD>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Source file for the LCD driver>
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "lcd.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/********************************************************************************
 *  [Function Name]:	LCD_init
 *  [Description] :		This function is responsible for initializing the LCD
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void LCD_init(void){
	/* Configure the control pins(E,RS,RW) as output pins */
	LCD_CTRL_DIR_PORT |= (1<<E) | (1<<RS) | (1<<RW);

	#if (DATA_MODE == 4)
		#if (UPPER_OR_LOWER==1)
			/* Configure the highest 4 bits of the data port as output pins */
			LCD_DATA_DIR_PORT |= 0xF0;

		#elif (UPPER_OR_LOWER==0)
			/* Configure the lowest 4 bits of the data port as output pins */
			LCD_DATA_DIR_PORT |= 0x0F;

		#endif
			/* initialize LCD in 4-bit mode */
			LCD_sendCommand(FOUR_BITS_DATA_MODE);

			/* use 2-line LCD + 4-bit Data Mode + 5*7 dot display Mode */
			LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);

	#elif (DATA_MODE == 8)
			/* Configure the data port as output port */
			LCD_DATA_DIR_PORT = 0xFF;

			/* use 2-line LCD + 8-bit Data Mode + 5*7 dot display Mode */
			LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE);

	#endif
		/* Display ON cursor OFF */
		LCD_sendCommand(CURSOR_OFF);

		/* clear LCD at the beginning */
		LCD_sendCommand(CLEAR_COMMAND);
}

/***********************************************************************************
 *  [Function Name]:	LCD_sendCommand
 *  [Description] :		This function is responsible for sending command to the LCD
 *  [Args] :
 *  [in]				uint8 a_command:
 *  						Contains specific order value to make LCD do
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 ***********************************************************************************/
void LCD_sendCommand(uint8 a_command){
	/* Command Mode Rs=0 */
	CLEAR_BIT(LCD_CTRL_OUT_PORT,RS);

	/* Write mode to LCD RW=0 */
	CLEAR_BIT(LCD_CTRL_OUT_PORT,RW);

	/* delay for processing Tas = 50ns */
	_delay_ms(1);

	/* Enable LCD to receive  */
	SET_BIT(LCD_CTRL_OUT_PORT,E);

	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

	#if(DATA_MODE == 4)
		#if (UPPER_OR_LOWER==1)
			/* Transfer the higher nibble to the LCD in the upper_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0x0F)|(a_command & 0xF0);
		#elif (UPPER_OR_LOWER==0)
			/* Transfer the higher nibble to the LCD in the lower_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0xF0)|((a_command>>4) & 0x0F);
		#endif

		/* delay for processing Tdsw = 100ns */
		_delay_ms(1);

		/* Disable LCD from receiving */
		CLEAR_BIT(LCD_CTRL_OUT_PORT,E);

		/* delay for processing Th = 13ns */
		_delay_ms(1);

		/* Enable LCD to receive */
		SET_BIT(LCD_CTRL_OUT_PORT,E);

		/* delay for processing Tpw - Tdws = 190ns */
		_delay_ms(1);

		#if (UPPER_OR_LOWER==1)
			/* Transfer the lower nibble to the LCD in the upper_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0x0F)|((a_command<<4) & 0xF0);

		#elif (UPPER_OR_LOWER==0)
			/* Transfer the lower nibble to the LCD in the lower_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0xF0)|( a_command & 0x0F);

		#endif

	#elif (DATA_MODE == 8)
		/* Transfer the whole PORT to the LCD */
		LCD_DATA_OUT_PORT = a_command;

	#endif
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD from receiving */
	CLEAR_BIT(LCD_CTRL_OUT_PORT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

/*****************************************************************************************
 *  [Function Name]:	LCD_displayCharacter
 *  [Description] :		This function is responsible for displaying character on the LCD
 *  [Args] :
 *  [in]				uint8 a_character :
 *  						The character that will be displayed
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *****************************************************************************************/

void LCD_displayCharacter(uint8 a_character){
	/* Command Mode Rs=0 */
	SET_BIT(LCD_CTRL_OUT_PORT,RS);

	/* Write mode to LCD RW=0 */
	CLEAR_BIT(LCD_CTRL_OUT_PORT,RW);

	/* delay for processing Tas = 50ns */
	_delay_ms(1);

	/* Enable LCD to receive  */
	SET_BIT(LCD_CTRL_OUT_PORT,E);

	/* delay for processing Tpw - Tdws = 190ns */
	_delay_ms(1);

	#if(DATA_MODE == 4)
		#if (UPPER_OR_LOWER==1)
			/* Transfer the higher nibble to the LCD in the upper_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0x0F)|(a_character & 0xF0);
		#elif (UPPER_OR_LOWER==0)
			/* Transfer the higher nibble to the LCD in the lower_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0xF0)|((a_character>>4) & 0x0F);
		#endif

		/* delay for processing Tdsw = 100ns */
		_delay_ms(1);

		/* Disable LCD from receiving */
		CLEAR_BIT(LCD_CTRL_OUT_PORT,E);

		/* delay for processing Th = 13ns */
		_delay_ms(1);

		/* Enable LCD to receive */
		SET_BIT(LCD_CTRL_OUT_PORT,E);

		/* delay for processing Tpw - Tdws = 190ns */
		_delay_ms(1);

		#if (UPPER_OR_LOWER==1)
			/* Transfer the lower nibble to the LCD in the upper_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0x0F)|((a_character<<4) & 0xF0);

		#elif (UPPER_OR_LOWER==0)
			/* Transfer the lower nibble to the LCD in the lower_port_mode */
			LCD_DATA_OUT_PORT=(LCD_DATA_OUT_PORT & 0xF0)|( a_character & 0x0F);

		#endif

	#elif (DATA_MODE == 8)
		/* Transfer the whole PORT to the LCD */
		LCD_DATA_OUT_PORT = a_character;

	#endif
	/* delay for processing Tdsw = 100ns */
	_delay_ms(1);

	/* Disable LCD from receiving */
	CLEAR_BIT(LCD_CTRL_OUT_PORT,E);

	/* delay for processing Th = 13ns */
	_delay_ms(1);
}

/**************************************************************************************
 *  [Function Name]:	LCD_displayString
 *  [Description] :		This function is responsible for displaying string on the LCD
 *  [Args] :
 *  [in]				const uint8 *string_Ptr:
 *  						pointer to the string that will be displayed
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
void LCD_displayString(const uint8 *a_string_Ptr){
	/* Loop to send each char to display function */
	while((*a_string_Ptr) != '\0'){
		LCD_displayCharacter(*a_string_Ptr);
		/* increase pointer to next character */
		a_string_Ptr++;
	}
}

/********************************************************************************
 *  [Function Name]:	LCD_goToRowColumn
 *  [Description] :		This function is responsible for moving cursor to
 *  					specific coordinate on the LCD
 *  [Args] :
 *  [in]				uint8 a_row:
 *  						row position to go to
 *  					uint8 a_column:
 *  						column position to go to
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void LCD_goToRowColumn(uint8 a_row,uint8 a_column){
	uint8 Address;

	/* first of all calculate the required address */
	switch(a_row)
	{
		case 0:
				Address=a_column;
				break;
		case 1:
				Address=a_column+0x40;
				break;
		case 2:
				Address=a_column+0x10;
				break;
		case 3:
				Address=a_column+0x50;
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

/********************************************************************************
 *  [Function Name]:	LCD_displayStringRowColumn
 *  [Description] :		This function is responsible for displaying string
 *  					starting at specific column and row on the LCD.
 *  [Args] :
 *  [in]				uint8 a_row:
 *  						row position to go to
 *  					uint8 a_column:
 *  						column position to go to
 *  					const uint8 *a_string_Ptr:
 *  						pointer to the string will be displayed
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_column,const uint8 *a_string_Ptr){
	/* Mover cursor to position */
	LCD_goToRowColumn(a_row,a_column);

	/* Start displaying */
	LCD_displayString(a_string_Ptr);
}

/***************************************************************************************
 *  [Function Name]:	LCD_clearScreen
 *  [Description] :		This function is responsible for clearing the screen of the LCD
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 ****************************************************************************************/

void LCD_clearScreen(void){
	/* send clear command to LCD */
	LCD_sendCommand(CLEAR_COMMAND);
}

/*************************************************************************************
 *  [Function Name]:	LCD_integerToString
 *  [Description] :		This function is responsible for converting integer to string
 *  [Args] :
 *  [in]				a_data:
 *  						integer data want to convert to string and display
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *************************************************************************************/

void LCD_integerToString(uint32 a_data){
	/* array of 16 chars as LCD take 16 in one line */
	uint8 string[LCD_WIDTH];

	/* function to convert integer data to string with base 10 */
	itoa(a_data,string,10);

	/* Display data */
	LCD_displayString(string);
}
