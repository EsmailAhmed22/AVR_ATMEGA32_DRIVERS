/******************************************************************************
 *
 * [FILE NAME]:		<Keypad.h>
 *
 * [MODULE]:		<KEYPAD>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Source file for the Keypad driver>
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "keypad.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#if (NUMBER_COLUMNS == 3)

/* Function to adjust the number to its equivalent in the keypad for 4x3 keypad */
static uint8 KEYPAD_4x3_adjustButtonNumber(uint8 a_button_number);
#elif (NUMBER_COLUMNS == 4)

/* Function to adjust the number to its equivalent in the keypad for 4x4 keypad */
static uint8 KEYPAD_4x4_adjustButtonNumber(uint8 a_button_number);
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/********************************************************************************
 *  [Function Name]:	Keypad_getPressed
 *  [Description] :		This function is responsible for getting the pressed key
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			This function return the pressed key
 *  NOTE				Delay 150ms because of debounce
 *********************************************************************************/

uint8 KEYPAD_getPressed(void) {
	/* counter for columns and counter for rows */
	uint8 column, row;
	while(1){
	/* Loop for columns */
	for (column = 0; column < NUMBER_COLUMNS; column++) {

		/* Make one of all columns as output and the rest are inputs including the rows */
		KEYPAD_DIR_PORT = (0b00010000 << column);

		/* Output 0 in the column that had been made output
		 * Enable all rows internal pull_up
		 */
		KEYPAD_OUT_PORT = ~(0b00010000 << column);

		/*Loop for rows */
		for (row = 0; row < NUMBER_ROWS; row++) {

			/* Check each row if it reads 0 means it is pressed */
			if (BIT_IS_CLEAR(KEYPAD_IN_PORT, row)) {
				_delay_ms(50);
				if(BIT_IS_CLEAR(KEYPAD_IN_PORT, row)){
					_delay_ms(130);
				/* Send the pushed button to adjustment function */
					#if (NUMBER_COLUMNS == 3)
						return KEYPAD_4x3_adjustButtonNumber((row*NUMBER_COLUMNS)+column+1);
					#elif (NUMBER_COLUMNS == 4)

						return KEYPAD_4x4_adjustButtonNumber((row * NUMBER_COLUMNS) + column + 1);
					#endif
					}
				}
			}
		}
	}
	return 0;
}

#if (NUMBER_COLUMNS == 3)

/********************************************************************************
 *  [Function Name]:	Keypad_4x3_adjustButtonNumber
 *  [Description] :		This function is responsible for adjusting the button number to its
 *  					equivalent in the keypad for 4x3 keypad.
 *  [Args] :
 *  [in]				uint8 a_button_number:
 *  						button number of the pressed key
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			This function return the adjusted number
 *********************************************************************************/

static uint8 KEYPAD_4x3_adjustButtonNumber(uint8 a_button_number){
	switch(a_button_number)
		{
			case 10: return '*'; /* ASCII Code of * */
					 break;
			case 11: return 0;
					 break;
			case 12: return '#'; /* ASCII Code of # */
					 break;
			default: return a_button_number;
		}
}

#elif (NUMBER_COLUMNS == 4)

/********************************************************************************
 *  [Function Name]:	Keypad_4x4_adjustButtonNumber
 *  [Description] :		This function is responsible for adjusting the button number to its
 *  					equivalent in the keypad for 4x4 keypad.
 *  [Args] :
 *  [in]				uint8 a_button_number:
 *  				 		button number of the pressed key
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			This function return the adjusted number
 *********************************************************************************/

static uint8 KEYPAD_4x4_adjustButtonNumber(uint8 a_button_number){
	switch(a_button_number)
		{
			case 1: return 7;
					break;
			case 2: return 8;
					break;
			case 3: return 9;
					break;
			case 4: return '%'; /* ASCII Code of % */
					break;
			case 5: return 4;
					break;
			case 6: return 5;
					break;
			case 7: return 6;
					break;
			case 8: return '*'; /* ASCII Code of '*' */
					break;
			case 9: return 1;
					break;
			case 10: return 2;
					break;
			case 11: return 3;
					break;
			case 12: return '-'; /* ASCII Code of '-' */
					break;
			case 13: return 13;  /* ASCII of Enter */
					break;
			case 14: return 0;
					break;
			case 15: return '='; /* ASCII Code of '=' */
					break;
			case 16: return '+'; /* ASCII Code of '+' */
					break;
			default: return a_button_number;
		}
}

#endif
