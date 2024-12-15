#ifndef STM32F0_ERROR_HANDLER_H_
#define STM32F0_ERROR_HANDLER_H_

/* **************************************************
 *			   	       GLOBALS  					*
 *************************************************  */

typedef enum
{
	USART_RING_BUFFER_OVERWRITE_ATTEMPT     	,
	USART_RING_BUFFER_WRITE_LIMIT_EXCEEDED 		,
	USART_RING_BUFFER_READ_SIZE_EXCEEDED 		,
	USART_UNSUPPORTED_USART_ID					,
	GPIOX_UNSUPPORTED_GPIO_PORT_ENABLE			,
	GPIOX_UNSUPPORTED_GPIO_PORT_DISABLE    		,
	GPIOX_UNSUPPORTED_MODE						,
	GPIOX_UNSUPPORTED_SPEED_CONFGURATION    	,
	GPIOX_UNSUPPORTED_PUPDR_CONFIGURATION   	,
	GPIOX_UNSUPPORTED_PIN					  	,
	GPIOX_UNSUPPORTED_ALTERNATE_FUNCTIONALLITY 	,
}e_ErrorCode;

/* **************************************************
 *			    FUNCTION PROTOTYPE 					*
 *************************************************  */

void Error_v_Report(e_ErrorCode e_code);

#endif /* STM32F0_ERROR_HANDLER_H_ */
