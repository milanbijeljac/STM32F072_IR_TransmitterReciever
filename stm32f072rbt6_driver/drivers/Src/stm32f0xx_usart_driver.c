/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <stm32f0xx_error_handler.h>
#include <stm32f0xx_usart_driver.h>
#include <stm32f072x8.h>
#include <core_cm0.h>
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

void UART_v_Init(uint32 clock, uint32 baudRate)
{
    /* Clock initialization */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

    /* Set baud rate */
    USART2->BRR = clock / baudRate;

	/* Clear M0 and M1 bits, M00 for 8 bit mode) */
    USART2->CR1 &= ~(USART_CR1_M);
    USART2->CR1 &= ~(1u << 28u);

    /* 			 Enable TX 			Enable RX	  Enable RX IR		 Enable USART  */
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;

    NVIC_EnableIRQ(USART2_IRQn);
}


void UART_v_Write_Message(uint8* data, uint8 size)
{
	uint8 i;

    for (i = 0; i < size; i++)
    {
        while (!(USART2->ISR & USART_ISR_TXE));
        USART2->TDR = data[i];
    }
}

