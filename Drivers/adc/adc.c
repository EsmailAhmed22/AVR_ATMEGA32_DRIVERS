/******************************************************************************
 *
 * [FILE NAME]:		<adc.c>
 *
 * [MODULE]:		<ADC>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/3/2020>
 *
 * [DESCRIPTION]:	<Source file for the ADC driver>
 *					<This driver supports the free running mode only.Trigger OFF>
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "adc.h"

/*******************************************************************************
 *                     	  Global Variables                                     *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(ADC_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/********************************************************************************
 *  [Function Name]:	ADC_init
 *  [Description] :		This function is responsible for initializing ADC
 *  					-With AREF
 *  					-With AVCC
 *  					-With Internal 2.56v
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void ADC_init(const Adc_ConfigType * Config_Ptr){

/* Making PORTA Input PORT */
	ADC_DIR_PORT =0;

/*
 * Choosing Reference Voltage
 * Choose ADLAR bit
 */
	ADMUX=((Config_Ptr->s_volt)<<6 )|((Config_Ptr->s_adlar)<<5);

/*
 * Prescaler bits
 * Interrupt or polling mode
 */
	ADCSRA=(ADCSRA & 0xF8) | (Config_Ptr->s_clock & 0x07) |((Config_Ptr->s_interrupt)<<3);

/* Enable ADC */
	SET_BIT(ADCSRA,ADEN);
}
/******************************************************************************************
 *  [Function Name]:	ADC_readChannelPolling
 *  [Description] :		This function is responsible for reading analog from specific bin
 *  					WORK WITH POLLING.
 *  [Args] :
 *  [in]				uint8 a_channelNumber:
 *  						bin number that my ADC will read.
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			ADC REGESTER.The digital value after converting.
 *******************************************************************************************/
uint16 ADC_readChannelPolling(uint8 a_channelNumber){
	/* Write bin to read from */
	ADMUX=(ADMUX & 0xE0)|(a_channelNumber & 0x07);

	/* Start conversion */
	SET_BIT(ADCSRA,ADSC);
	/* Waiting until the ADC flag rise */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear flag */
	SET_BIT(ADCSRA,ADIF);
	return ADC;
}

/******************************************************************************************
 *  [Function Name]:	ADC_readChannelInterrupt
 *  [Description] :		This function is responsible for reading analog from specific bin
 *  					WORK WITH INTERRUPT.
 *  [Args] :
 *  [in]				uint8 a_channelNumber:
 *  						bin number that my ADC will read
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None.
 *******************************************************************************************/
void ADC_readChannelInterrupt(uint8 a_channelNumber){
	/* Write bin to read from */
	ADMUX=(ADMUX & 0xE0)|(a_channelNumber & 0x07);
	/* Enable ADC interrupt */
	SET_BIT(ADCSRA,ADIE);
	/* Start conversion */
	SET_BIT(ADCSRA,ADSC);

}

/******************************************************************************************
 *  [Function Name]:	Adc_setCallBack
 *  [Description] :		This function is responsible for setting the Call Back function address
 *  [Args] :
 *  [in]				void(*a_ptr)(void):
 *  						pointer to function contain the address of the Call Back function
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None.
 *******************************************************************************************/
void Adc_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

