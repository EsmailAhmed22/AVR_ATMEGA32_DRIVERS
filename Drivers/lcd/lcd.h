/******************************************************************************
 *
 * [FILE NAME]:		<lcd.h>
 *
 * [MODULE]:		<LCD>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Header file for the LCD driver>
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
/* for the use of itoa() function */
#include "stdlib.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/*LCD width 16 or 20 */
#define LCD_WIDTH 16

/* Data Mode of the LCD 4 or 8 */
#define DATA_MODE 8

/* In  4-bit Mode
 * Put 1 for UPPER_PORT_PINS in the data port
 * Put 0 for LOWER_PORT_PINS in the data port */
#define UPPER_OR_LOWER 0

/* LCD HW Pins */
#define RS PC0
#define RW PC1
#define E  PC2
#define LCD_CTRL_OUT_PORT PORTC
#define LCD_CTRL_DIR_PORT DDRC
#define LCD_DATA_OUT_PORT PORTA
#define LCD_DATA_DIR_PORT DDRA

/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* This function is responsible for initializing the LCD */
void LCD_init(void);

/* This function is responsible for sending command to the LCD */
void LCD_sendCommand(uint8 a_command);

/* This function is responsible for displaying character on the LCD */
void LCD_displayCharacter(uint8 a_character);

/* This function is responsible for displaying string on the LCD */
void LCD_displayString(const uint8 *a_string_Ptr);

/* This function is responsible for moving cursor to specific coordinate on the LCD */
void LCD_goToRowColumn(uint8 a_row,uint8 a_column);

/* This function is responsible for displaying string on the LCD at specific column and row */
void LCD_displayStringRowColumn(uint8 a_row,uint8 a_column,const uint8 *a_string_Ptr);

/* This function is responsible for clearing the screen of the LCD */
void LCD_clearScreen(void);

/* This function is responsible for converting integer to string */
void LCD_integerToString(uint32 a_data);

#endif
