/******************************************************************************
 *
 * [FILE NAME]:		<i2c.h>
 *
 * [MODULE]:		<I2C>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<14/11/2020>
 *
 * [DESCRIPTION]:	<Header file for the I2C driver>
 *
 *******************************************************************************/
#ifndef I2C_H_
#define I2C_H_

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
	LOW_MODE_10KB,STANDARD_MODE_100KB,FAST_MODE_400KB
}I2C_Speed;



typedef struct
{
	I2C_Speed i2c_speed;
	char	  i2c_myAddress;

}I2C_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START         0x08 /* start has been sent */
#define TW_REP_START     0x10 /* repeated start */
#define TW_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + Ack received from slave */
#define TW_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + Ack received from slave */
#define TW_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave.*/
#define TW_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave */
#define TW_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave*/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void I2C_init(const I2C_ConfigType *a_config_Ptr);
void I2C_start(void);
void I2C_stop(void);
void I2C_write(uint8 data);
uint8 I2C_readWithACK(void); //read with send Ack
uint8 I2C_readWithNACK(void); //read without send Ack
uint8 I2C_getStatus(void);
#endif /* I2C_H_ */
