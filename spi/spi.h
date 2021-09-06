/******************************************************************************
 *
 * [FILE NAME]:		<spi.h>
 *
 * [MODULE]:		<SPI>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/11/2020>
 *
 * [DESCRIPTION]:	<Header file for the SPI driver>
 *
 *******************************************************************************/
#ifndef SPI_H_
#define SPI_H_

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* INTERRUPT ENABLE */
#define SPI_INTENABLE 0

/* Send MSB first write 0
 * Send LSB first write 1
 */
#define SPI_DORD 0

/* Clock Polarity with Rising write 0 with falling write 1 */
#define SPI_CLKPOL 0

/* factor to divide F_CPU with WRITE
 * 0 ----> F_CPU/4
 * 1 ----> F_CPU/16
 * 2 ----> F_CPU/64
 * 3 ----> F_CPU/128
 */
#define SPI_CLKRATE  0x00

/* To enable double speed write 1 */
#define SPI_DOUPLESPEED 0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* This function is responsible for initializing the SPI's Master */
void SPI_initMaster(void);

/* This function is responsible for initializing the SPI's Slave */
void SPI_initSlave(void);

/* This function is responsible for sending one byte */
void SPI_sendByte(const uint8 data);

/* This function is responsible for receiving one byte */
uint8 SPI_recieveByte(void);

/* This function is responsible for sending String */
void SPI_sendString(const uint8 *Str);

/* This function is responsible for receiving String */
void SPI_receiveString(char *Str);

/*This function is responsible for saving the address that will be called after interrupts happen*/
void SPI_callBackAdress(void(*a_Func_Ptr)(void));

#endif /* SPI_H_ */
