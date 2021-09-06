/******************************************************************************
 *
 * [FILE NAME]:		<Microcontroller - Configurations.h>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<File to include all Micro libraries and clock define>
 *
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

/* Setting clock of Micro to 1MHZ */
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

/* For Macros ROR and ROL */
#define REG_SIZE 8

/* include Micro PORT library */
#include <avr/io.h>

/* include Micro Interrupt library */
#include <avr/interrupt.h>

/* include delay functions library */
#include <util/delay.h>

#endif
