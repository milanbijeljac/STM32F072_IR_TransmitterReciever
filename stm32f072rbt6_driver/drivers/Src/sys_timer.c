/*
 * sys_delay.c
 *
 *  Created on: Jan 21, 2024
 *      Author: Milan
 */

/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <sys_timer.h>

/****************************************************/

void TIM3_v_cfg(uint8 u_frequency)
{
	RCC->APB1ENR |= 1u << 1u; /* TIM3 */

	RCC->CFGR |= 3u << 0u;

	/* APB bus clock speed is currently set at value provided as argument
	 * frequency (-1 since PSC register is configured that way)             */

	TIM3->PSC = u_frequency - 1u;
	TIM3->ARR = 0xFFFFu;
	TIM3->CR1 |= 1u << 0u;
	while(!(TIM3->SR & (1u << 0u)));
}

void Delay_v_us (uint16 us)
{
	TIM3->CNT = 0u;
	while (TIM3->CNT < us);

}
void Delay_v_ms (uint16 ms)
{
	for (uint16 i = 0; i < ms; i++)
	{
		Delay_v_us(US_TO_MS);
	}
}

void Delay_v_seconds(uint16 seconds)
{
	for (uint16 i = 0; i < seconds; i++)
	{
		Delay_v_ms(MS_TO_S);
	}
}

void TIM2_v_IrFrequencyCfg(void)
{
	RCC->APB1ENR |= 1u << 0u;

    /* Configure TIM2 for 38kHz */
	TIM2->PSC = 16u - 1u;
	TIM2->ARR = 26u - 1u;
	TIM2->CCR1 = 13u;

    /* Set PWM mode 1 on TIM2 Channel 1 (active when counter < CCR1) */
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1; /* PWM mode 1, TIM_CCMR1_OC1M_Pos = 4 */
	TIM2->CCER |= TIM_CCER_CC1E;  /* Enable capture/compare on CH1 */
}
