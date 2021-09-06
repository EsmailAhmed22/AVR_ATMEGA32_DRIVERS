/******************************************************************************
 *
 * [FILE NAME]:		<eeprom.c>
 *
 * [MODULE]:		<EEPROM>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<15/12/2020>
 *
 * [DESCRIPTION]:	<Source file for the I2C driver>
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "i2c.h"
#include "eeprom.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*************************************************************************************
 *  [Function Name]:	EEPROM_init
 *  [Description] :		This function is responsible for initializing EEPROM
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 **************************************************************************************/
void EEPROM_init(void)
{
	/*Initialize the I2C module*/
	I2C_ConfigType eeprom={STANDARD_MODE_100KB,10};
	I2C_init(&eeprom);
}

/*************************************************************************************
 *  [Function Name]:	EEPROM_writeByte
 *  [Description] :		This function is responsible for writing byte in EEPROM.
 *  [Args] :
 *  [in]				uint16 a_address:
 *  						Address of memory slot i will write in.
 *  					uint8 a_data:
 *  						Data that will be written.
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			Success that transfer is done
 *  					Error if there is something happened wrong
 **************************************************************************************/
uint8 EEPROM_writeByte(uint16 a_address, uint8 a_data)
{
	/* Send the Start Bit */
	I2C_start();
    /* Check that it is sent */
    if (I2C_getStatus() != TW_START)
        return ERROR;

    /* Send the device address(0xA0) + last 3 bits of memory location + R/W=0 (write)*/
    I2C_write((uint8)(0xA0 | ((a_address & 0x0700)>>7)));
    /* Check that it is sent */
    if (I2C_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;

    /* Send the rest of the required memory location address */
    I2C_write((uint8)(a_address));
    /* Check that it is sent */
    if (I2C_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* write byte to eeprom */
    I2C_write(a_data);
    /* Check that it is sent */
    if (I2C_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();

    return SUCCESS;
}

/*************************************************************************************
 *  [Function Name]:	EEPROM_readByte
 *  [Description] :		This function is responsible for reading byte from EEPROM.
 *  [Args] :
 *  [in]				uint16 a_address:
 *  						Address of memory slot i will read from.
 *  					uint8 *a_data_Ptr:
 *  						Pointer to data that will be read.
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			Success that read is done
 *  					Error if there is something happened wrong
 **************************************************************************************/
uint8 EEPROM_readByte(uint16 a_address, uint8 *a_data_Ptr)
{
	/* Send the Start Bit */
	I2C_start();
	/* Check that it is sent */
	if (I2C_getStatus() != TW_START)
        return ERROR;

	/* Send the device address(0xA0) + last 3 bits of memory location + R/W=0 (write) */
    I2C_write((uint8)((0xA0) | ((a_address & 0x0700)>>7)));
    /* Check that it is sent */
    if (I2C_getStatus() != TW_MT_SLA_W_ACK)
        return ERROR;

    /* Send the rest of the required memory location address */
    I2C_write((uint8)(a_address));
    /* Check that it is sent */
    if (I2C_getStatus() != TW_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    I2C_start();
    /* Check that it is sent */
    if (I2C_getStatus() != TW_REP_START)
        return ERROR;

    /* Send the device address(0xA0) + last 3 bits of memory location + R/W=1 (Read) */
    I2C_write((uint8)((0xA0) | ((a_address & 0x0700)>>7) | 1));
    /* Check that it is sent */
    if (I2C_getStatus() != TW_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *a_data_Ptr = I2C_readWithNACK();
    /* Check that it is done */
    if (I2C_getStatus() != TW_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    I2C_stop();
    return SUCCESS;
}
