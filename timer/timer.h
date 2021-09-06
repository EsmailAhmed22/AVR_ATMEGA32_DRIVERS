/******************************************************************************
 *
 * [FILE NAME]:		<timer.h>
 *
 * [MODULE]:		<TIMER>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<14/12/2020>
 *
 * [DESCRIPTION]:	<Header file for the TIMER driver>
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

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
	NONE1,F_CPU_1=1,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXT_FALL,EXT_RISE
}Timer_Clock;

typedef enum
{
	NONE2,F2_CPU_1=1,F2_CPU_8,F2_CPU_32,F2_CPU_64,F2_CPU_128,F2_CPU_256,F2_CPU_1024
}Timer2_Clock;

typedef enum
{
	TIMER0,TIMER1,TIMER2
}Timer_ID;

typedef enum
{
	OVF,CMP,PWM
}Timer_Mode;

typedef enum
{
	NONE_OCO,NON_INVERTING_OCO=0x20,INVERTING_OCO=0x30
}Timer_OCO_Mode;
typedef struct
{
	Timer_ID		s_timer_id ;
	Timer_Mode 		s_timer_mode;
	Timer_Clock 	s_timer_clk;
	Timer2_Clock	s_timer2_clk;
	Timer_OCO_Mode	s_timer_oco_mode;
	uint16 			s_timer_initial_value;
	uint16			s_timer_compare_value;
	uint16			s_timer1B_compare_value;
}Timer_ConfigType;

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Configure TIMER HW bins */
#define Timer_DIR_PORTB DDRB
#define Timer_DIR_PORTD DDRD
#define OC0	PB3
#define OC2	PD7
#define OCB	PD4


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void TIMER_init(const Timer_ConfigType * a_config_Ptr);
/*This function is responsible for setting the Call Back function address */
void TIMER_setCallBack(uint8 a_timerID,void(*a_ptr)(void));
void TIMER_deinit(uint8 a_timerID);

#endif /* TIMER_H_ */
