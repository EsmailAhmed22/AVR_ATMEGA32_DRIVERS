/******************************************************************************
 *
 * [FILE NAME]:		<uart.h>
 *
 * [MODULE]:		<UART>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/8/2020>
 *
 * [DESCRIPTION]:	<Header file for the UART driver>
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

typedef enum
{
	NORMAL,DOUBLE=2
}UART_Rate;

typedef enum
{
	POLLING,INTTERRUPT
}UART_Mode;

typedef enum
{
	NO_PARITY,ODD_PARITY,EVEN_PARITY
}UART_Parity;

typedef enum
{
	W5_BITS,W6_BITS=2,W7_BITS=4,W8_BITS=6
}UART_WORD_BITS;
typedef struct
{
	UART_Rate 	s_rate;
	UART_Mode 	s_tx_mode;
	UART_Mode 	s_rx_mode;
	UART_Parity s_parity;
	uint32		s_baudRate;
	uint8		s_safeChar;
	UART_WORD_BITS s_word_bits;

}UART_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* This function is responsible for initializing the UART */
void UART_init(const UART_ConfigType *a_config_Ptr);

/* This function is responsible for sending one byte */
void UART_sendByte(uint8 a_data);

/* This function is responsible for receiving one byte */
uint8 UART_receiveByte(void);

/* This function is responsible for sending String */
void UART_sendString(uint8 *a_str);

/* This function is responsible for receiving String */
void UART_receiveString(uint8 *a_str);

/*This function is responsible for saving the address that will be called after interrupts happen */
void UART_callBackAdress(void(*a_Func_Ptr)(void),uint8 TorR);

#endif
