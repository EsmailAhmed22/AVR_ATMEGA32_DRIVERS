/******************************************************************************
 *
 * [FILE NAME]:		<adc.h>
 *
 * [MODULE]:		<ADC>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Header file for the ADC driver>
 *
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

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
	F_CPU_CLOCK_0_2,F_CPU_CLOCK_1_2,F_CPU_4,F_CPU_8,F_CPU_16,F_CPU_32,F_CPU_CLOCK_64,F_CPU_CLOCK_128
}Adc_Clock;

typedef enum
{
	AREF_VOLTAGE,AVCC_VOLTAGE,A2_VOLTAG=3
}Adc_VoltageRef;

typedef enum
{
	DISABLE,ENABLE
}Adc_Activations;

typedef struct
{
	Adc_Clock s_clock;
	Adc_Activations s_adlar;
	Adc_Activations s_interrupt;
	Adc_VoltageRef s_volt;
}Adc_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Configure ADC HW bins */
#define ADC_DIR_PORT DDRA


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*This function is responsible for initializing ADC */
void ADC_init(void);
/* This function is responsible for reading analog from specific bin WORK WITH POLLING */
uint16 ADC_readChannelPolling(uint8 a_channelNumber);

/*This function is responsible for reading analog from specific bin WORK WITH INTERRUPT */
void ADC_readChannelInterrupt(uint8 a_channelNumber);

/*This function is responsible for setting the Call Back function address */
void Adc_setCallBack(void(*a_ptr)(void));
#endif
