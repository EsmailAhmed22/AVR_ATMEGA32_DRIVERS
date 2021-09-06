/******************************************************************************
 *
 * [FILE NAME]:		<eeprom.h>
 *
 * [MODULE]:		<EEPROM>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<15/12/2020>
 *
 * [DESCRIPTION]:	<Header file for the I2C driver>
 *
 *******************************************************************************/
#ifndef EEPROM_H_
#define EEPROM_H_

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void EEPROM_init(void);
uint8 EEPROM_writeByte(uint16 a_addr,uint8 a_data);
uint8 EEPROM_readByte(uint16 a_addr,uint8 *a_data_Ptr);


#endif /* EEPROM_H_ */
