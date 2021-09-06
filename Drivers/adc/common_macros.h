/******************************************************************************
 *
 * [FILE NAME]:		<Common - Macros.h>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Commonly used Macros>
 *
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Set specific bit in any register */
#define SET_BIT(REG,BIT_NUMBER)      (REG|=(1<<BIT_NUMBER))

/* Clear specific bit in any register */
#define CLEAR_BIT(REG,BIT_NUMBER)    (REG&=(~(1<<BIT_NUMBER)))

/* Toggle specific bit in any register */
#define TOGGLE_BIT(REG,BIT_NUMBER)   (REG^=(1<<BIT_NUMBER))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,NUMBER_OF_SHIFTS)    (REG=(REG>>NUMBER_OF_SHIFTS)|(REG<<(REG_SIZE-NUMBER_OF_SHIFTS)))

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,NUMBER_OF_SHIFTS)  	 (REG=(REG<<NUMBER_OF_SHIFTS)|(REG>>(REG_SIZE-NUMBER_OF_SHIFTS)))

/* Check if specific bit in any register is set and return 1 if true */
#define BIT_IS_SET(REG,BIT_NUMBER)	 ((REG>>BIT_NUMBER) & 1)

/* Check if specific bit in any register is clear and return 1 if true */
#define BIT_IS_CLEAR(REG,BIT_NUMBER) (!((REG>>BIT_NUMBER) & 1))

#endif
