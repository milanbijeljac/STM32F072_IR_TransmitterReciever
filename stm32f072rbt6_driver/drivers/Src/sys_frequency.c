/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <sys_frequency.h>

void PLL_Enable(uint32 pllInputMultyply)
{
	/* Enable HSI oscillator */
	RCC->CR |= RCC_CR_HSION;

	/* Wait for HSI oscillator to stabilize */
	while(!(RCC->CR & RCC_CR_HSIRDY));

	/* Configure PLL */
	RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL);
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSI_Div2 | pllInputMultyply;

	/* Enable PLL */
	RCC->CR |= RCC_CR_PLLON;

	/* Wait for PLL to lock */
	while(!(RCC->CR & RCC_CR_PLLRDY));

	/* Switch system clock to PLL */
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;

	/* Wait for system clock switch */
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}

