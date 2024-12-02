/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <stm32f072x8.h>
#include <stm32f0xx_gpio_driver.h>
#include <types.h>
#include <config.h>

/* **************************************************
 *					DEFINES 					    *
 *************************************************  */

#define INT32_BIT_SIZE 			32u
#define NEC_TOTAL_BITS			32u
#define NEC_SEPARATOR			1200u
#define REPETITION_LOW_LIMIT   	11000u
#define REPETITION_HIGH_LIMIT  	12000u

#define ZHJT03_SEPARATOR		1600u
#define ZHJT03_BYTE_CODE_LENGHT	3u

/* **************************************************
 *			    GLOBAL VARIABLES 					*
 *************************************************  */
#if DEBUGG_MODE == STD_ON
	static uint16 u_timeDiffMatrix[3][32];
#endif

volatile uint8 u_counterInterruptTrigger = 0u;

static uint32 u_code[3]  = {0,0,0};

/****************************************************/

void EXTI4_15_IRQHandler(void)
{
	u_counterInterruptTrigger++;
	EXTI->IMR &= ~(1 << 12u); /* Disable interrupt */

	GPIO_v_IRQHandling(12u);

	uint8  i;
	uint8  j;
	uint32 u_timeDiff 	     = 0u;
	uint32 u_timeRisingEdge  = 0u;
	uint32 u_timeFallingEdge = 0u;

	u_timeRisingEdge = TIM3->CNT;

	while(!GPIO_u_ReadFromInputPin(GPIOB, 12u));

	while(GPIO_u_ReadFromInputPin(GPIOB, 12u));

	u_timeFallingEdge = TIM3->CNT;

	u_timeDiff = u_timeFallingEdge - u_timeRisingEdge;

	#if	(STANDARD_REMOTE == STD_ON && ZHJT03_REMOTE == STD_OFF)
	if( (u_timeDiff > REPETITION_LOW_LIMIT) && (u_timeDiff < REPETITION_HIGH_LIMIT) )
	{
		/* Repetition, leave last code value. */
	}
	else
	{
		u_timeRisingEdge = 0u;
		u_timeFallingEdge = 0u;
		u_timeDiff = 0u;
		u_code[0] = 0u;

		for (i = 0; i < NEC_TOTAL_BITS; i++)
		{
			while(!GPIO_u_ReadFromInputPin(GPIOB, 12u)); /* Wait for pin to go HIGH */

			u_timeRisingEdge = TIM3->CNT;

			while(GPIO_u_ReadFromInputPin(GPIOB, 12u)); /* Wait for pin to go back to LOW */

			u_timeFallingEdge = TIM3->CNT;

			u_timeDiff = u_timeFallingEdge - u_timeRisingEdge;

			#if DEBUGG_MODE == STD_ON
				j = 0u;
				u_timeDiffMatrix[j][i] = u_timeDiff;
			#endif

			if (u_timeDiff > NEC_SEPARATOR)
			{
				u_code[0] |= (1u << (31u-i));
			}
			else
			{
				u_code[0] &= ~(1u << (31u-i));
			}
		}
	}
	#endif

	#if (ZHJT03_REMOTE == STD_ON && STANDARD_REMOTE == STD_OFF)
	if( (u_timeDiff > REPETITION_LOW_LIMIT) && (u_timeDiff < REPETITION_HIGH_LIMIT) )
	{
		/* Repetition, leave last code value. */
	}
	else
	{
		u_timeRisingEdge = 0u;
		u_timeFallingEdge = 0u;
		u_timeDiff = 0u;

		for(i = 0; i < ZHJT03_BYTE_CODE_LENGHT; i++)
		{
			for (j = 0; j < INT32_BIT_SIZE; j++)
			{
				/* loop 2 times */
				while(!GPIO_u_ReadFromInputPin(GPIOB, 12u)); /* Wait for pin to go HIGH */

				u_timeRisingEdge = TIM3->CNT;

				while(GPIO_u_ReadFromInputPin(GPIOB, 12u)); /* Wait for pin to go back to LOW */

				u_timeFallingEdge = TIM3->CNT;

				u_timeDiff = u_timeFallingEdge - u_timeRisingEdge;

				#if DEBUGG_MODE == STD_ON
				u_timeDiffMatrix[i][j] = u_timeDiff;
				#endif

				if (u_timeDiff > ZHJT03_SEPARATOR)
				{
					u_code[i] |= (1u << (31u-j));
				}
				else
				{
					u_code[i] &= ~(1u << (31u-j));
				}
			}
		}
	}

	/* Wait for end impulse to avoid triggering interrupt again. */
	while(GPIO_u_ReadFromInputPin(GPIOB, 12u));

	while(!GPIO_u_ReadFromInputPin(GPIOB, 12u));

	while(GPIO_u_ReadFromInputPin(GPIOB, 12u));

	while(!GPIO_u_ReadFromInputPin(GPIOB, 12u));
	#endif

	EXTI->IMR |= (1 << 12u); /* Enable interrupt */
}
