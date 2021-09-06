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
 * [DESCRIPTION]:	<Source file for the TIMER driver>
 *
 *******************************************************************************/
/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "timer.h"

/*******************************************************************************
 *                     	  Global Variables                                     *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_timer0_callBack_Ptr)(void) = NULL_PTR;
static volatile void (*g_timer1_callBack_Ptr)(void) = NULL_PTR;
static volatile void (*g_timer1B_callBack_Ptr)(void) = NULL_PTR;
static volatile void (*g_timer2_callBack_Ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
/* All ISR work with callBack function technique */

/* TIMER0 overflow mode ISR */
ISR(TIMER0_OVF_vect) {
	if (g_timer0_callBack_Ptr != NULL_PTR) {
		(*g_timer0_callBack_Ptr)();
	}
}

/* TIMER1 overflow mode ISR */
ISR(TIMER1_OVF_vect) {
	if (g_timer1_callBack_Ptr != NULL_PTR) {
		(*g_timer1_callBack_Ptr)();
	}
}

/* TIMER2 overflow mode ISR */
ISR(TIMER2_OVF_vect) {
	if (g_timer2_callBack_Ptr != NULL_PTR) {
		(*g_timer2_callBack_Ptr)();
	}
}

/* TIMER0 compare mode ISR */
ISR(TIMER0_COMP_vect) {
	if (g_timer0_callBack_Ptr != NULL_PTR) {
		(*g_timer0_callBack_Ptr)();
	}
}

/* TIMER1 compare A mode ISR */
ISR(TIMER1_COMPA_vect) {
	if (g_timer1_callBack_Ptr != NULL_PTR) {
		(*g_timer1_callBack_Ptr)();
	}
}

/* TIMER1 compare B mode ISR */
ISR(TIMER1_COMPB_vect) {
	if (g_timer1B_callBack_Ptr != NULL_PTR) {
		(*g_timer1B_callBack_Ptr)();
	}
}

/* TIMER2 compare mode ISR */
ISR(TIMER2_COMP_vect) {
	if (g_timer2_callBack_Ptr != NULL_PTR) {
		(*g_timer2_callBack_Ptr)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/********************************************************************************
 *  [Function Name]:	Timer_init
 *  [Description] :		This function is responsible for initializing Timer
 *  					-Support TIMER0,TIMER1 and TIMER2
 *  					-Support Normal Mode,Compare Mode and PWM mode
 *  [Args] :
 *  [in]				const Timer_ConfigType * a_config_Ptr:
 *  						pointer to structure
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void TIMER_init(const Timer_ConfigType *a_config_Ptr) {
	/* Choose between timers */
	switch (a_config_Ptr->s_timer_id) {

	case TIMER0:
		/* Clear all registers at first */
		TCCR0 = 0;
		TCNT0 = 0;
		OCR0 = 0;
		TIMSK &= 0XFC;

		/*Choose between modes */
		switch (a_config_Ptr->s_timer_mode) {

		case OVF:
			/* Choosing OVF mode */
			SET_BIT(TCCR0,FOC0);
			CLEAR_BIT(TCCR0, WGM00);
			CLEAR_BIT(TCCR0, WGM01);

			/* Choosing Clk*/
			TCCR0 |= (a_config_Ptr->s_timer_clk);

			/* Set initial value of the timer*/
			TCNT0 = a_config_Ptr->s_timer_initial_value;

			/* Enable OVF interrupt */
			SET_BIT(TIMSK, TOIE0);

			break;

		case CMP:
			/* Choosing CMP mode */
			SET_BIT(TCCR0,FOC0);
			CLEAR_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);

			/* Choosing Clk*/
			TCCR0 |= (a_config_Ptr->s_timer_clk);

			/* Set initial value of the timer */
			TCNT0 = a_config_Ptr->s_timer_initial_value;

			/* Set Compare value */
			OCR0 = a_config_Ptr->s_timer_compare_value;

			/* Enable CMP interrupt */
			SET_BIT(TIMSK, OCIE0);

			break;

		case PWM:
			/* Choosing PWM mode */
			CLEAR_BIT(TCCR0,FOC0);
			SET_BIT(TCCR0, WGM00);
			SET_BIT(TCCR0, WGM01);

			/*Make OC0 output pin */
			SET_BIT(Timer_DIR_PORTB,OC0);

			/* Choosing Clk*/
			TCCR0 |= (a_config_Ptr->s_timer_clk);

			/* Set initial value of the timer */
			TCNT0 = a_config_Ptr->s_timer_initial_value;

			/* Set OCO mode */
			TCCR0 |= (a_config_Ptr->s_timer_oco_mode);

			/* Set Compare value */
			OCR0 = a_config_Ptr->s_timer_compare_value;

			break;
		}
		break;

	case TIMER1:
		/* Clear all registers at first */
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
		OCR1A = 0;
		OCR1B = 0;
		TIMSK &= 0XC3;

		/*Choose between modes */
		switch (a_config_Ptr->s_timer_mode) {

		case OVF:
			/* Choosing OVF mode */
			TCCR1A =  (1<<FOC1A)|(1<<FOC1B);
			TCCR1A &= ~(1 << WGM10) & ~(1 << WGM11);
			TCCR1B &= ~(1 << WGM12) & ~(1 << WGM13);

			/* Choosing Clk*/
			TCCR1B |= (a_config_Ptr->s_timer_clk);

			/* Set initial value of the timer*/
			TCNT1 = a_config_Ptr->s_timer_initial_value;

			/* Enable OVF interrupt */
			SET_BIT(TIMSK, TOIE1);

			break;

		case CMP:
			/* Choosing CMP mode with OCR1A */
			TCCR1A =  (1<<FOC1A)|(1<<FOC1B);
			TCCR1A &= ~(1 << WGM10) & ~(1 << WGM11);
			SET_BIT(TCCR1B, WGM12);
			CLEAR_BIT(TCCR1B, WGM13);

			/* Choosing Clk*/
			TCCR1B =(TCCR1B&0xF8)|((a_config_Ptr->s_timer_clk)&0x07);

			/* Set initial value of the timer */
			TCNT1 = a_config_Ptr->s_timer_initial_value;

			/* Set Compare value */
			OCR1A = a_config_Ptr->s_timer_compare_value;
			if (a_config_Ptr->s_timer1B_compare_value) {
				OCR1B = a_config_Ptr->s_timer1B_compare_value;
				SET_BIT(TIMSK, OCIE1B);
			}

			/* Enable CMP interrupt */
			SET_BIT(TIMSK, OCIE1A);

			break;

		case PWM:
			/* Choosing CMP mode with OCR1A */
			TCCR1A =  ~(1<<FOC1A) & ~(1<<FOC1B);
			TCCR1A |= (1 << WGM10) | (1 << WGM11);
			TCCR1B |= (1 << WGM12) | (1 << WGM13);

			/*Make OCB output pin */
			SET_BIT(Timer_DIR_PORTD,OCB);

			/* Choosing Clk*/
			TCCR1B |= (a_config_Ptr->s_timer_clk);

			/* Set initial value of the timer */
			TCNT1 = a_config_Ptr->s_timer_initial_value;

			/* Set OCO mode with OCO1B */
			TCCR1A |= (a_config_Ptr->s_timer_oco_mode);

			/* Set TOP value */
			OCR1A = a_config_Ptr->s_timer_compare_value;

			/* Set Compare value */
			OCR1B = a_config_Ptr->s_timer1B_compare_value;

			break;
		}
		break;

	case TIMER2:
		/* Clear all registers at first */
		ASSR = 0;
		TCCR2 = 0;
		TCNT2 = 0;
		OCR2 = 0;
		TIMSK &= 0X3F;

		/*Choose between modes */
		switch (a_config_Ptr->s_timer_mode) {

		case OVF:
			/* Choosing OVF mode */
			SET_BIT(TCCR2,FOC2);
			CLEAR_BIT(TCCR2, WGM20);
			CLEAR_BIT(TCCR2, WGM21);

			/* Choosing Clk*/
			TCCR2 |= (a_config_Ptr->s_timer2_clk);

			/* Set initial value of the timer*/
			TCNT2 = a_config_Ptr->s_timer_initial_value;

			/* Enable OVF interrupt */
			SET_BIT(TIMSK, TOIE2);

			break;

		case CMP:
			/* Choosing CMP mode */
			SET_BIT(TCCR2,FOC2);
			CLEAR_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/* Choosing Clk*/
			TCCR2 |= (a_config_Ptr->s_timer2_clk);

			/* Set initial value of the timer */
			TCNT2 = a_config_Ptr->s_timer_initial_value;

			/* Set Compare value */
			OCR2 = a_config_Ptr->s_timer_compare_value;

			/* Enable CMP interrupt */
			SET_BIT(TIMSK, TOIE2);

			break;

		case PWM:
			/* Choosing PWM mode */
			CLEAR_BIT(TCCR2,FOC2);
			SET_BIT(TCCR2, WGM20);
			SET_BIT(TCCR2, WGM21);

			/*Make OC2 output pin */
			SET_BIT(Timer_DIR_PORTD,OC2);

			/* Choosing Clk*/
			TCCR2 |= (a_config_Ptr->s_timer2_clk);

			/* Set initial value of the timer */
			TCNT2 = a_config_Ptr->s_timer_initial_value;

			/* Set OCO mode */
			TCCR2 |= (a_config_Ptr->s_timer_oco_mode);

			/* Set Compare value */
			OCR2 = a_config_Ptr->s_timer_compare_value;

			break;
		}
		break;
	}
}

/********************************************************************************
 *  [Function Name]:	Timer_setCallBack
 *  [Description] :		This function is responsible for taking call back addresses
 *  [Args] :
 *  [in]				uint8 a_timerID:
 *  						Contains Timer Id which for address is sent
 *  					void(*a_callBack_Ptr)(void):
 *  						Contains address of the callback function
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void TIMER_setCallBack(uint8 a_timerID, void (*a_callBack_Ptr)(void)) {
	/* Choose between timers */
	switch (a_timerID) {

	case TIMER0:
		g_timer0_callBack_Ptr = a_callBack_Ptr;
		break;

	case TIMER1:
		g_timer1_callBack_Ptr = a_callBack_Ptr;
		break;

	case TIMER2:
		g_timer2_callBack_Ptr = a_callBack_Ptr;
		break;

	default:
		g_timer1B_callBack_Ptr = a_callBack_Ptr;
	}
}
/************************************************************************************
 *  [Function Name]:	TIMER_deinit
 *  [Description] :		This function is responsible for de-initialization of TIMERS
 *  [Args] :
 *  [in]				uint8 a_timerID:
 *  						Contains Timer Id which will be stopped
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *************************************************************************************/
void TIMER_deinit(uint8 a_timerID){
	/* Choose between timers */
	switch (a_timerID) {

	case TIMER0:
		TCCR0 = 0;	TCNT0 = 0;	OCR0 = 0;	TIMSK &= 0XFC;
		break;

	case TIMER1:
		TCCR1A = 0;	TCCR1B = 0;	TCNT1 = 0;	OCR1A = 0;	OCR1B = 0;	TIMSK &= 0XC3;
		break;

	case TIMER2:
		ASSR = 0;	TCCR2 = 0;	TCNT2 = 0;	OCR2 = 0;	TIMSK &= 0X3F;
		break;
}
}
