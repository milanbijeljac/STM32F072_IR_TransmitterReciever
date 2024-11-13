/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <sys_adc.h>

/* **************************************************
 *			    FUNCTION PROTOTYPE 					*
 *************************************************  */

static uint8 ADC_u_Calibration(ADC_TypeDef* p_ADCx);

/****************************************************/

static uint8 ADC_u_Calibration(ADC_TypeDef* p_ADCx)
{
	uint8 u_retVal  = NOK;
	uint8 u_counter = 0u;
	uint8 u_timeout = 0u;

	/* Check if ADC and DMA are enabled */
	if( (!(p_ADCx->CR & (1u << 0u))) && (!(p_ADCx->CFGR1 & (1u << 0u))) )
	{
		/* Request calibration START */
		p_ADCx->CR |= 1u << 31u;

		/* Wait for calibration to end */
		while( !(p_ADCx->CR & (1u << 31u)) || (u_timeout == 1u) )
		{
			Delay_v_ms(100u);

			/* 200ms timeout */ /* TODO: Rework timeout logic to check time difference between entry time in loop */
			if(u_counter >= 2u)
			{
				u_timeout = 1u;
				u_retVal  = NOK;
			}
			else
			{
				u_retVal = OK;
			}

			u_counter++;
		}
	}

	return u_retVal;
}

uint8 ADCx_u_Init(ADC_TypeDef* p_ADCx, uint8 channel)
{
	uint8 u_retVal;

	RCC->APB2ENR |= 1u << 9u;

	u_retVal = ADC_u_Calibration(p_ADCx);

	Delay_v_ms(100u);

	p_ADCx->CFGR1  &= ~(1u << 13u);      /* Single conversion mode */
	p_ADCx->CFGR1  &= ~(3u << 3u);       /* 12 bit mode */
	p_ADCx->CHSELR |=   1u << channel;   /* Channel select */
	p_ADCx->CR     |=   1u << 0u;        /* Enable ADC */

	while ( !(p_ADCx->ISR & (1u << 0u)));

	return  u_retVal;
}

uint16 ADCx_u_Read(ADC_TypeDef* p_ADCx)
{
	p_ADCx->CR |= 1u << 2u; 				/* Start ADC conversion */
	while( !(p_ADCx->ISR & (1u << 2u)) ); 	/* Wait for EOC */
	return (uint16) p_ADCx->DR;
}


