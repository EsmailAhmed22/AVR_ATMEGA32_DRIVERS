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
 * [DESCRIPTION]:	<Header file for the Keypad driver>
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* Keypad configuration for number of columns */
#define NUMBER_COLUMNS 4

/* Keypad configuration for number of rows */
#define NUMBER_ROWS    4

/* Keypad PORT  Output configuration (First 4 OF PORT)*/
#define KEYPAD_OUT_PORT PORTB

/* Keypad PORT  Input configuration (LAST 4 OF PORT*/
#define KEYPAD_IN_PORT  PINB

/* Keypad PORT  Direction configuration */
#define KEYPAD_DIR_PORT DDRB

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* This function is responsible for getting the pressed key */
uint8 KEYPAD_getPressed(void);


#endif
