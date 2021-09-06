/******************************************************************************
 *
 * [FILE NAME]:		<uart.c>
 *
 * [MODULE]:		<UART>
 *
 * [AUTHOR]:		<Esmail Ahmed>
 *
 * [DATE CREATED]:	<11/8/2020>
 *
 * [DESCRIPTION]:	<Source file for the UART driver>
 * 					<Asynchronous , 1 stop bit and 8 data bits transfer >
 *
 *******************************************************************************/

/*******************************************************************************
 *                     			  INCLUDES                                     *
 *******************************************************************************/

#include "uart.h"


/*******************************************************************************
 *                     			  GLOBAL VARIABLES                             *
 *******************************************************************************/

/* Global pointer to store address of initialization structure */
static const UART_ConfigType *g_config_Ptr=0;

/* Global variable used for call back technique */

static void(*g_uartTX_Ptr)(void);

static void(*g_uartRX_Ptr)(void);

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/* ISR activated after data is transmitted */
ISR(USART_UDRE_vect){
	/* Call the function in the Scheduler using Call Back concept */
	(*g_uartTX_Ptr)();
}

/* ISR activated after data is received */
ISR(USART_RXC_vect){
	/* Call the function in the Scheduler using Call Back concept */
	(*g_uartRX_Ptr)();
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/********************************************************************************
 *  [Function Name]:	UART_init
 *  [Description] :		This function is responsible for initializing the UART
 *  [Args] :
 *  [in]				const UART_ConfigType *a_config_Ptr:
 *  							pointer contains address of structure
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void UART_init(const UART_ConfigType *a_config_Ptr){
	/* Storing pointer in global one */
	g_config_Ptr=a_config_Ptr;

	/* U2X = 1 for double transmission speed */
	UCSRA |= a_config_Ptr->s_rate;

	if(a_config_Ptr->s_tx_mode)
		/* Enable interrupt mode with transmitting data */
		SET_BIT(UCSRB,UDRIE);

	if(a_config_Ptr->s_rx_mode)
		/* Enable interrupt mode with receiving data */
		SET_BIT(UCSRB,RXCIE);

	/* To write in UCSRC make URSEL=1 */
	SET_BIT(UCSRC,URSEL);

	/* Choose Parity */
	switch(a_config_Ptr->s_parity){

	case NO_PARITY:
		/*Disable Parity  */
		UCSRC &= ~(1<<UPM0) & ~(1<<UPM1);
		break;

	case EVEN_PARITY:
		/* Enable even parity */
		CLEAR_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);
		break;

	case ODD_PARITY:
		/* Enable odd parity */
		UCSRC |= (1<<UPM0) | (1<<UPM1);
		break;
}

	/* send 8 bit data */
	UCSRC|=(a_config_Ptr->s_word_bits);


	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	CLEAR_BIT(UBRRH,URSEL); /*To write in UBRRH */
	UBRRH = (((F_CPU / ((a_config_Ptr->s_baudRate)* 8UL))) - 1)>>8;
	UBRRL = (((F_CPU / ((a_config_Ptr->s_baudRate)* 8UL))) - 1);

	/* Enable Receiving and Transmitting */
	UCSRB= (1<<RXEN) | (1<<TXEN);
}
/********************************************************************************
 *  [Function Name]:	UART_sendByte
 *  [Description] :		This function is responsible for sending one byte
 *  [Args] :
 *  [in]				uint8 a_data:
 *  						contain data that will be sent
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void UART_sendByte(uint8 a_data){

	/* Wait until current transmission is done */
	while(BIT_IS_CLEAR(UCSRA,UDRE));
	/* Transmit data */
	UDR=a_data;
}

/********************************************************************************
 *  [Function Name]:	UART_receiveByte
 *  [Description] :		This function is responsible for receiving one byte
 *  [Args] :
 *  [in]				None
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			The received data.
 *********************************************************************************/
uint8 UART_receiveByte(void){
	/* Wait until current receiving is finished */
	while(BIT_IS_CLEAR(UCSRA,RXC));

	if(g_config_Ptr->s_parity!=0)

		/*Check for parity error */
		if(BIT_IS_SET(UCSRA,PE))

			/* return safe character chosen */
			return (g_config_Ptr->s_safeChar);

	/* Check for frame error */
	if(BIT_IS_SET(UCSRA,FE))

		/* return safe character chosen */
		return (g_config_Ptr->s_safeChar);

	/* Read received data */
	return UDR;
}

/********************************************************************************
 *  [Function Name]:	UART_sendString
 *  [Description] :		This function is responsible for sending String
 *  [Args] :
 *  [in]				uint8 *a_str_Ptr:
 *  						contain address of data that will be sent
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None
 *********************************************************************************/
void UART_sendString(uint8 *a_str_Ptr){
	while(*a_str_Ptr!='\0'){
		UART_sendByte(*a_str_Ptr);
		a_str_Ptr++;
	}
}

/********************************************************************************
 *  [Function Name]:	UART_receiveString
 *  [Description] :		This function is responsible for receiving String
 *  [Args] :
 *  [in]				uint8 *a_str_Ptr:
 *  						pointer to address that data will be stored at
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			None.
 *********************************************************************************/
void UART_receiveString(uint8 *a_str_Ptr){
	uint8 numberofchars;
	numberofchars=UART_receiveByte();
	for(;numberofchars>0;numberofchars--){
		*a_str_Ptr=UART_receiveByte();
		a_str_Ptr++;
	}
	*a_str_Ptr='\0';
}

/**********************************************************************************************
 *  [Function Name]:	UART_callBackAdress
 *  [Description] :		This function is responsible for saving the address that
 *  					will be called after interrupts happen
 *  [Args] :
 *  [in]				void(*a_Func_Ptr)(void):
 *  						Pointer to function used to store function's address ISR will call
 *  					uint8 a_TorR:
 *  						used to say the coming address for which ISR
 *  [out]				None
 *  [in/out]			None
 *  [Returns]			The received data.
 ***********************************************************************************************/
void UART_callBackAdress(void(*a_Func_Ptr)(void),uint8 a_TorR){
	if(a_TorR==1){
		g_uartTX_Ptr=a_Func_Ptr;
	}
	if(a_TorR==0){
		g_uartRX_Ptr=a_Func_Ptr;
	}
}

