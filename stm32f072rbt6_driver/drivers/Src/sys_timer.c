/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <sys_timer.h>

/* **************************************************
 *					DEFINES 					    *
 *************************************************  */

#define US_TO_MS 1000u
#define MS_TO_S  1000u

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
	/* Timer configuration for IR signal (38 kHz) */

    RCC->APB1ENR |= 1 << 0u;

    TIM2->PSC  = 1 - 1;               /* PSC is 1, full clock speed needed  */
    TIM2->ARR  = 419u; 			     /* ARR for 38kHz = (fconfigured/fdesired) - 1 */
    TIM2->CCR1 = 210u;               /* Set duty cycle to 50%, ARR / 2 */

    TIM2->CCMR1 &= ~(7u << 4u);
    TIM2->CCMR1 |= (6u << 4u); 		 /* Set PWM mode 1 */
    TIM2->CCMR1 |= 1u << 3u;         /* Enable output compare preload */

    TIM2->CCER |= 1u << 0u;          /* Enable capture/compare on channel 1 */
    TIM2->CR1  |= 1u << 7u;          /* Enable auto-reload preload */
    TIM2->CR1  |= 1u << 0u;          /* Enable timer */
}
