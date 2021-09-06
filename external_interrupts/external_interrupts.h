/******************************************************************************
 *
 * [FILE NAME]:		<External-Interrupts.h>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/4/2020>
 *
 * [DESCRIPTION]:	<Headr file for external interrupts>
 *
 *******************************************************************************/

#ifndef EXTERNAL_INTERRUPTS_H_
#define EXTERNAL_INTERRUPTS_H_


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
	BOTH,FALLING,RISING
}ExtInts_Edge;

typedef enum
{
	EXT0,EXT1,EXT2
}ExtInts_ID;

typedef struct
{
	ExtInts_ID		s_extInts_id ;
	ExtInts_Edge 	s_extInts_edge;
}ExternalInterrupts_ConfigType;


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*This function is responsible for activating INT0 OR INT1 OR INT2*/
void ExternalInterrupts_init(const ExternalInterrupts_ConfigType *a_config_Ptr);
void ExternalIntterrupts_deinit(uint8 a_extInts_id);
void ExternalIntterrupts_setCallBack(uint8 a_extInts_id,void(*a_ptr)(void));




#endif
