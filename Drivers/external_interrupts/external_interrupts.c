/******************************************************************************
 *
 * [FILE NAME]:		<External-Interrupts.h>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/4/2020>
 *
 * [DESCRIPTION]:	<Source file for external interrupts>
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "external_interrupts.h"

/*******************************************************************************
 *                     			  GLOBAL VARIABLES                             *
 *******************************************************************************/

/* Global variable used for call back technique */

static volatile void(*g_ext0_callBack_Ptr)(void)= NULL_PTR;

static volatile void(*g_ext1_callBack_Ptr)(void)= NULL_PTR;

static volatile void(*g_ext2_callBack_Ptr)(void)= NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/* All ISR work with callBack function technique */
/* ISR of EXT0 */
ISR(INT0_vect){
	if (g_ext0_callBack_Ptr != NULL_PTR) {
		(*g_ext0_callBack_Ptr)();
	}
}

/* ISR of EXT1 */
ISR(INT1_vect){
	if (g_ext1_callBack_Ptr != NULL_PTR) {
		(*g_ext1_callBack_Ptr)();
	}
}

/* ISR of EXT2 */
ISR(INT2_vect){
	if (g_ext2_callBack_Ptr != NULL_PTR) {
		(*g_ext2_callBack_Ptr)();
	}
}

/**********************************************************************************************
 *                     				 Functions Definitions                            		  *
 **********************************************************************************************/

/******************************************************************************************
 *  [Function Name]:	ExternalIntterrupts_init
 *  [Description] :		This function is responsible for initializing ExternalIntterrupts
 *  					-Support EXT0,EXT1 and EXT2
 *  					-Support interrupting with falling,rising and both(for EXT0 and Ext1)
 *  [Args] :
 *  [in]				const ExternalInterrupts_ConfigType *a_config_Ptr:
 *  						pointer to structure
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 ********************************************************************************************/
void ExternalInterrupts_init(const ExternalInterrupts_ConfigType *a_config_Ptr) {
	/* Choose between External Interrupts */
	switch (a_config_Ptr->s_extInts_id) {

	case EXT0:
		/* Clear all registers at first */
		MCUCR&=0xFC;
		/*Choose between modes */
		switch (a_config_Ptr->s_extInts_edge) {

		case BOTH:
			/*For interrupt at any edge */
			SET_BIT(MCUCR,ISC00);
			CLEAR_BIT(MCUCR,ISC01);
			break;

		case FALLING:
			/*For interrupt at falling edge */
			SET_BIT(MCUCR,ISC01);
			CLEAR_BIT(MCUCR,ISC00);
			break;

		case RISING:
			/*For interrupt at rising edge */
			MCUCR|=(1<<ISC00) | (1<<ISC01);
			break;
		}
		/* Enable EXT0 */
		SET_BIT(GICR,INT0);
		break;

	case EXT1:
		/* Clear all registers at first */
		MCUCR&=0xF3;

		/*Choose between modes */
		switch (a_config_Ptr->s_extInts_edge) {

		case BOTH:
			/*For interrupt at any edge */
			SET_BIT(MCUCR,ISC10);
			CLEAR_BIT(MCUCR,ISC11);
			break;

		case FALLING:
			/*For interrupt at falling edge */
			SET_BIT(MCUCR,ISC11);
			CLEAR_BIT(MCUCR,ISC10);
			break;

		case RISING:
			/*For interrupt at rising edge */
			MCUCR|=(1<<ISC00) | (1<<ISC01);
			break;
		}
		/* Enable EXT1 */
		SET_BIT(GICR,INT1);
		break;

		case EXT2:
			/* Clear all registers at first */
			MCUCSR&=0xBF;

			/*Choose between modes */
			switch (a_config_Ptr->s_extInts_edge) {

			case FALLING:
				/*For interrupt at falling edge */
				CLEAR_BIT(MCUCSR,ISC2);
				break;

			case RISING:
				/*For interrupt at rising edge */
				SET_BIT(MCUCSR,ISC2);
				break;
			case BOTH:
				break;
			}
			/* Enable EXT2 */
			SET_BIT(GICR,INT2);
			break;
	}
}
/********************************************************************************
 *  [Function Name]:	ExternalIntterrupts_setCallBack
 *  [Description] :		This function is responsible for taking call back addresses
 *  [Args] :
 *  [in]				uint8 a_extInts_id:
 *  						Contains EXT_INT ID which for address is sent
 *  					void(*a_callBack_Ptr)(void):
 *  						Contains address of the callback function
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void ExternalIntterrupts_setCallBack(uint8 a_extInts_id , void (*a_callBack_Ptr)(void)) {
	/* Choose between timers */
	switch (a_extInts_id) {

	case EXT0:
		g_ext0_callBack_Ptr = a_callBack_Ptr;
		break;

	case EXT1:
		g_ext1_callBack_Ptr = a_callBack_Ptr;
		break;

	case EXT2:
		g_ext2_callBack_Ptr = a_callBack_Ptr;
		break;
	}
}
/************************************************************************************
 *  [Function Name]:	ExternalIntterrupts_deinit
 *  [Description] :		This function is responsible for de-initialization of ExtInts
 *  [Args] :
 *  [in]				uint8 a_extInts_id):
 *  						Contains EXT_INT ID which will be stopped
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *************************************************************************************/
void ExternalIntterrupts_deinit(uint8 a_extInts_id){
	/* Choose between timers */
	switch (a_extInts_id) {

	case EXT0:
		/* Disable EXT0 */
		CLEAR_BIT(GICR,INT0);
		break;

	case EXT1:
		/* Disable EXT1 */
		CLEAR_BIT(GICR,INT1);
		break;

	case EXT2:
		/* Disable EXT2 */
		CLEAR_BIT(GICR,INT2);
		break;
}
}
