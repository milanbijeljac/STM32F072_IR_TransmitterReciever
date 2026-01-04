#ifndef INC_STM32F0XX_USART_DRIVER_H_
#define INC_STM32F0XX_USART_DRIVER_H_

/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <types.h>
#include <stm32f072x8.h>

/* **************************************************
 *			    FUNCTION PROTOTYPE 					*
 *************************************************  */

uint8 UARTRing_v_WriteElement(uint8* u_data, uint8 u_size);

uint8 UARTRing_v_ReadElement(uint8 *u_data, uint8 u_size);

uint8 UARTRing_u_GetMaxReadSize(void);
/**
 *
 * \brief      - Initialization function for UART
 * \param[in]  - uint32 clock - clock speed in HZ
 * \param[in]  - uint32 baudRate - desired baud rate
 * \return     - NONE
 * \globals    - NONE
 *
 */
void UART_v_Init(uint32 clock, uint32 baudRate);

#endif /* INC_STM32F0XX_USART_DRIVER_H_ */
