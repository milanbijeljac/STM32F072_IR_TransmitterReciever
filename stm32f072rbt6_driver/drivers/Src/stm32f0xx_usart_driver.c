/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <stm32f0xx_error_handler.h>
#include <stm32f0xx_usart_driver.h>
#include <stm32f072x8.h>

/* **************************************************
 *			   	       GLOBALS  					*
 *************************************************  */

static uint8 u_buffer[50];

static const uint8 u_bufferMaxSize = sizeof(u_buffer)/sizeof(u_buffer[0]);

static uint8 u_writeIndex = 0u;

static uint8 u_readIndex = 0u;

static uint8 u_fullCircle = 0u;

static uint8 u_MaxBytesToWrite = 50u;

/****************************************************/

uint8 UARTRing_u_GetMaxReadSize(void)
{
	return 50u - u_MaxBytesToWrite;
}

uint8 UARTRing_v_WriteElement(uint8* u_data, uint8 u_size)
{
	uint8 i;
	uint8 u_retVal = NOK;

	if( (u_fullCircle == 1u) && (u_writeIndex == u_readIndex) )
	{
		Error_v_Report(USART_RING_BUFFER_OVERWRITE_ATTEMPT);
	}
	else if( (u_size > u_MaxBytesToWrite) || (u_size > u_bufferMaxSize) )
	{
		Error_v_Report(USART_RING_BUFFER_WRITE_LIMIT_EXCEEDED);
	}
	else
	{
		for(i = 0; i < u_size; i++)
		{
			if(u_writeIndex == u_bufferMaxSize )
			{
				u_writeIndex = 0u;
				u_fullCircle = 1u;
			}

			u_buffer[u_writeIndex] = *u_data;
			u_data++;
			u_writeIndex++;
			u_MaxBytesToWrite--;
		}

		u_retVal = OK;
	}

	return u_retVal;
}

uint8 UARTRing_v_ReadElement(uint8 *u_data, uint8 u_size)
{
	uint8 i;
	uint8 u_readLength = 0u;
	uint8 u_retVal = NOK;

	u_readLength = UARTRing_u_GetMaxReadSize();

	if(u_size > u_readLength)
	{
		Error_v_Report(USART_RING_BUFFER_READ_SIZE_EXCEEDED);
	}
	else if(u_writeIndex == u_readIndex)
	{
		/* Do nothing as there is nothing to read */
	}
	else
	{
		for(i = 0; i < u_size; i++)
		{
			if(u_readIndex == u_bufferMaxSize)
			{
				u_readIndex = 0u;
				u_fullCircle = 0u;
			}

			*u_data = u_buffer[u_readIndex];
			u_data++;
			u_readIndex++;
			u_MaxBytesToWrite++;
		}

		u_retVal = OK;
	}
	return u_retVal;
}


void USARTx_v_Init(USART_TypeDef* p_USARTx)
{
	if(p_USARTx == USART1)
	{
		RCC->APB2ENR |= 1u << 14u;
	}
	else if(p_USARTx == USART2)
	{
		RCC->APB1ENR |= 1u << 17u;
	}
	else if(p_USARTx == USART3)
	{
		RCC->APB1ENR |= 1u << 18u;
	}
	else if(p_USARTx == USART4)
	{
		RCC->APB1ENR |= 1u << 19u;
	}
	else
	{
		Error_v_Report(USART_UNSUPPORTED_USART_ID);
	}

	/* Clear M0 and M1 bits, M00 for 8 bit mode) */
	p_USARTx->CR1 &= ~(1u << 12u);
	p_USARTx->CR1 &= ~(1u << 28u);

	/* Set baud rate to 115.2 KBps */
	p_USARTx->BRR = 0x1A1u;

	/* Set 1 stop bit */
	p_USARTx->CR2 &= ~(1u << 0);

	/* Enable USART */
	p_USARTx->CR1 |= 1u << 0u;

}
