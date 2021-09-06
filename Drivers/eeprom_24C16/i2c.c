/******************************************************************************
 *
 * [FILE NAME]:		<i2c.c>
 *
 * [MODULE]:		<I2C>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<14/11/2020>
 *
 * [DESCRIPTION]:	<Source file for the I2C driver>
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "i2c.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*************************************************************************************
 *  [Function Name]:	TWI_init
 *  [Description] :		This function is responsible for initializing I2C
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
void I2C_init(const I2C_ConfigType *a_config_Ptr){
	/* Enable I2C */
	TWCR=(1<<TWEN);

	/* Setting Baud rate */
	switch(a_config_Ptr->i2c_speed){
	/*
	 * Setting Bit Rate register TWBR
	 * Setting Prescaler bitsi TWBR
	 */
	case LOW_MODE_10KB:
		TWBR=98;
		TWSR=1;
		break;
	case STANDARD_MODE_100KB:
		TWBR=8;
		TWSR=1;
		break;
	case FAST_MODE_400KB:
		TWBR=2;
		TWSR=0;
		break;
	}

	/*
	 * My address as slave
	 * Activating the response to general call *
	 */
	TWAR=((a_config_Ptr->i2c_myAddress)<<1) | 0x01;

}

/*************************************************************************************
 *  [Function Name]:	I2C_start
 *  [Description] :		This function is responsible for sending start bit
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
void I2C_start(void){
	/*
	 * Clear flag TWINT.
	 * Enable TWEN again.
	 * Sending start bit.
	 */
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);

	/* Wait until start bit is sent */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*************************************************************************************
 *  [Function Name]:	I2C_stop
 *  [Description] :		This function is responsible for sending stop bit
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
void I2C_stop(void){
	/*
	 * Clear flag TWINT.
	 * Enable TWEN again.
	 * Sending stop bit.
	 */
	TWCR=(1<<TWSTO)|(1<<TWEN)|(1<<TWINT);
}

/******************************************************************************************
 *  [Function Name]:	I2C_write
 *  [Description] :		This function is responsible for write address or data to the buss.
 *  [Args] :
 *  [in]				uint8 data:
 *  						Data to put in buss either address or data.
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *******************************************************************************************/
void I2C_write(uint8 data){

	/* Write data on the buss */
	TWDR=data;

	/*
	 * Clear flag TWINT.
	 * Enable TWEN again.
	 */
	TWCR=(1<<TWEN)|(1<<TWINT);

	/* Wait until data is sent */
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

/*************************************************************************************
 *  [Function Name]:	I2C_readWithACK
 *  [Description] :		This function is responsible for reading data and send Ack
 *  					to take more data.
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			Data read from the buss.
 **************************************************************************************/
uint8 I2C_readWithACK(void){
	/*
	 * Clear flag TWINT.
	 * Enable TWEN again.
	 * Enable Acknowledgment bit
	 */
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);

	/* Wait until data is received */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Return received data*/
	return TWDR;
}

/*************************************************************************************
 *  [Function Name]:	I2C_readWithNACK
 *  [Description] :		This function is responsible for reading last byte.
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
uint8 I2C_readWithNACK(void){
	/*
	 * Clear flag TWINT.
	 * Enable TWEN again.
	 */
	TWCR=(1<<TWEN)|(1<<TWINT);

	/* Wait until data is received */
	while(BIT_IS_CLEAR(TWCR,TWINT));

	/* Return received data*/
	return TWDR;
}

/*************************************************************************************
 *  [Function Name]:	I2C_getStatus
 *  [Description] :		This function is responsible for checking that current action
 *  					has happened
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
uint8 I2C_getStatus(void){
	/* Return the code of finished current action */
	return (TWSR&0xF8);
}
