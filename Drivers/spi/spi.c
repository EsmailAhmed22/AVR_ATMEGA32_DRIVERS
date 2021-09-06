/******************************************************************************
 *
 * [FILE NAME]:		<spi.c>
 *
 * [MODULE]:		<SPI>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/11/2020>
 *
 * [DESCRIPTION]:	<Source file for the SPI driver>
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "spi.h"

/*******************************************************************************
 *                     			  GLOBAL VARIABLES                             *
 *******************************************************************************/

/* Global variable used for call back technique */

#if(SPI_INTENABLE==1)
static void(*g_SPI_interrupt_Func_Ptr)(void);
#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*************************************************************************************
 *  [Function Name]:	SPI_initMaster
 *  [Description] :		This function is responsible for initializing the SPI's Master
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/

void SPI_initMaster(void){
	/******** Configure SPI Master Pins *********
	 * SS(PB4)   --> Output
	 * MOSI(PB5) --> Output
	 * MISO(PB6) --> Input
	 * SCK(PB7) --> Output
	 ********************************************/
	DDRB |= (1<<PB4);
	DDRB |= (1<<PB5);
	DDRB &= ~(1<<PB6);
	DDRB |= (1<<PB7);

	/* SPE 	set 1 to enable SPI
	 * MSTR set 1 to make it Master */
	SPCR=(1<<SPE) | (1<<MSTR);

#if(SPI_INTENABLE==1)
	/* SPI work with Interrupt */
	SIT_BIT(SPCR,SPIE);
#endif

#if(SPI_DORD==1)
	/* Send LSB first */
	SIT_BIT(SPCR,DORD);
#endif

#if(SPI_CLKPOL==1)
	/* CLOCK POLARITY with falling edge */
	SIT_BIT(SPCR,CPOL);
#endif

#if(SPI_DOUPLESPEED==1)
	/* Make SPI2X=1 to get double speed */
	SIT_BIT(SPSR,SPI2X);
	/* Set SPI clk rate */
	SPCR=(SPCR & 0xFC) | (SPI_CLKRATE & 0x03);
#endif

	/* Set SPI clk rate */
	SPCR=(SPCR & 0xFC) | (SPI_CLKRATE & 0x03);
}

/*************************************************************************************
 *  [Function Name]:	SPI_initSlave
 *  [Description] :		This function is responsible for initializing the SPI's Slave
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/

void SPI_initSlave(void){
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)   --> Input
	 * MOSI(PB5) --> Input
	 * MISO(PB6) --> Output
	 * SCK(PB7) --> Input
	 ********************************************/
	DDRB &= (~(1<<PB4));
	DDRB &= (~(1<<PB5));
	DDRB |= (1<<PB6);
	DDRB &= (~(1<<PB7));

	/* SPE 	set 1 to enable SPI
	 * MSTR set 0 to make it Slave */
	SPCR=(1<<SPE);

#if(SPI_INTENABLE==1)
	/* SPI work with Interrupt */
	SIT_BIT(SPCR,SPIE);
#endif

#if(SPI_DORD==1)
	/* Send LSB first */
	SIT_BIT(SPCR,DORD);
#endif

#if(SPI_CLKPOL==1)
	/* CLOCK POLARITY with falling edge */
	SIT_BIT(SPCR,CPOL);
#endif

#if(SPI_DOUPLESPEED==1)
	/* Make SPI2X=1 to get double speed */
	SIT_BIT(SPSR,SPI2X);
	/* Set SPI clk rate */
	SPCR=(SPCR & 0xFC) | (SPI_CLKRATE & 0x03);
#endif

	/* Set SPI clk rate */
	SPCR=(SPCR & 0xFC) | (SPI_CLKRATE & 0x03);
}

/********************************************************************************
 *  [Function Name]:	SPI_sendByte
 *  [Description] :		This function is responsible for sending one byte
 *  [Args] :
 *  [in]				uint8 a_data:
 *  						contain data that will be sent
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/

void SPI_sendByte(uint8 a_data){
	/* Transmit data */
	SPDR=a_data;
	/* Wait until current transmission is done */
	while(BIT_IS_CLEAR(SPSR,SPIF));
}

#if(SPI_INTENABLE==0)
/********************************************************************************
 *  [Function Name]:	SPI_receiveByte
 *  [Description] :		This function is responsible for receiving one byte
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			The received data.
 *********************************************************************************/
uint8 SPI_receiveByte(void){
	/* Wait until current receiving is finished */
	while(BIT_IS_CLEAR(SPSR,SPIF));
	/* Read received data */
	return SPDR;
}
#endif

/********************************************************************************
 *  [Function Name]:	SPI_sendString
 *  [Description] :		This function is responsible for sending String
 *  [Args] :
 *  [in]				uint8 *a_str_Ptr:
 *  						contain address of data that will be sent
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/

void SPI_sendString(uint8 *a_str_Ptr){
	while(*a_str_Ptr!='\0'){
		SPI_sendByte(*a_str_Ptr);
		a_str_Ptr++;
	}
}

#if(SPI_INTENABLE==0)
/********************************************************************************
 *  [Function Name]:	SPI_receiveString
 *  [Description] :		This function is responsible for receiving String
 *  [Args] :
 *  [in]				uint8 *a_str_Ptr:
 *  						pointer to address that data will be stored at
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None.
 *********************************************************************************/

void SPI_receiveString(uint8 *a_str_Ptr){
	uint8 numberofchars;
	numberofchars=SPI_receiveByte();
	for(;numberofchars>0;numberofchars--){
		*a_str_Ptr=SPI_receiveByte();
		a_str_Ptr++;
	}
	*a_str_Ptr='\0';
}
#endif

#if(SPI_INTENABLE==1)
/**********************************************************************************************
 *  [Function Name]:	SPI_callBackAdress
 *  [Description] :		This function is responsible for saving the address that
 *  					will be called after interrupts happen
 *  [Args] :
 *  [in]				void(*a_Func_Ptr)(void):
 *  						Pointer to function used to store function's address ISR will call
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			The received data.
 ***********************************************************************************************/
void SPI_callBackAdress(void(*a_Func_Ptr)(void)){
		g_SPI_interrupt_Func_Ptr=a_Func_Ptr;
}
#endif

#if(SPI_INTENABLE==1)
/* ISR activated after data is transmitted */
ISR(SPI_STC_vect){
	/* Call the function in the Scheduler using Call Back concept */
	(*g_SPI_interrupt_Func_Ptr)();
}
#endif

