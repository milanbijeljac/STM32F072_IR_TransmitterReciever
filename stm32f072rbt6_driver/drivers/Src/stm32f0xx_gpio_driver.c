/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */
#include <stm32f0xx_gpio_driver.h>

void GPIO_v_PeripheralClockControl(GPIO_TypeDef *pGPIOx, uint8 enabledOrDisabled)
{
	if(enabledOrDisabled == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}
		else
		{
			/* TODO: Report error: unknown GPIO port */
		}
	}
	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DI();
		}
		else
		{
			/* TODO: Report error: unknown GPIO port */
		}
	}
}

void GPIO_v_Init(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration)
{
	/* Enable peripheral clock */

	/* TODO: Call GPIO_PeripheralClockControl() here */

	/* TODO: Error handling */

	GPIOx_v_ModeConfig(pGPIOx, GPIO_PinConfiguration);

	GPIOx_v_SpeedConfig(pGPIOx, GPIO_PinConfiguration);

	GPIOx_v_PupdrConfig(pGPIOx, GPIO_PinConfiguration);

	GPIOx_v_OutputConfig(pGPIOx, GPIO_PinConfiguration);

	if(GPIO_PinConfiguration.GPIO_PinMode == ALTERNATE_FUNCTION_MODE)
	{
		GPIOx_v_AlternateFunctionConfig(pGPIOx, GPIO_PinConfiguration);
	}
	else
	{
		/* Do nothing */
	}

}

void GPIO_v_DeInit(GPIO_TypeDef *pGPIOx)
{
	if(pGPIOx == GPIOA)
	{
		/* Reset GPIOA peripheral, bit position 17 at RCC_AHBSTR register */
		RCC->AHBRSTR |= 1u << 17u;
		RCC->AHBRSTR &= ~(1u << 17u);
	}
	else if(pGPIOx == GPIOB)
	{
		/* Reset GPIOB peripheral, bit position 18 at RCC_AHBSTR register */
		RCC->AHBRSTR |= 1u << 18u;
		RCC->AHBRSTR &= ~(1u << 18u);
	}
	else if(pGPIOx == GPIOC)
	{
		/* Reset GPIOC peripheral, bit position 19 at RCC_AHBSTR register */
		RCC->AHBRSTR |= 1u << 19u;
		RCC->AHBRSTR &= ~(1u << 19u);
	}
	else if(pGPIOx == GPIOD)
	{
		/* Reset GPIOD peripheral, bit position 20 at RCC_AHBSTR register */
		RCC->AHBRSTR |= 1u << 20u;
		RCC->AHBRSTR &= ~(1u << 20u);
	}
	else if(pGPIOx == GPIOE)
	{
		/* Reset GPIOE peripheral, bit position 21 at RCC_AHBSTR register */
		RCC->AHBRSTR |= 1u << 21u;
		RCC->AHBRSTR &= ~(1u << 21u);
	}
	else if(pGPIOx == GPIOF)
	{
		/* Reset GPIOF peripheral, bit position 22 at RCC_AHBSTR register */
		RCC->AHBRSTR |= 1u << 22u;
		RCC->AHBRSTR &= ~(1u << 22u);
	}
	else
	{
		/* Do nothing */
	}

}

uint8 GPIO_u_ReadFromInputPin(GPIO_TypeDef *pGPIOx, uint8 u_pinNumber)
{
	uint8 u_retrunValue = 0u;
	u_retrunValue = (uint8)((pGPIOx->IDR >> u_pinNumber) & 0x00000001);
	return u_retrunValue;
}

uint32 GPIO_u_ReadFromInputPort(GPIO_TypeDef *pGPIOx)
{
	uint32 u_retrunValue = 0u;
	u_retrunValue = (uint32) pGPIOx->IDR;
	return u_retrunValue;
}

void GPIO_v_WriteToOutputPin(GPIO_TypeDef *pGPIOx, uint8 u_pinNumber, uint8 u_value)
{
	if(u_value == SET)
	{
		/* Write 1 to the out data register to the bit fiend corresponding to bit number */
		pGPIOx->ODR |= (1 << u_pinNumber);
	}
	else
	{
		pGPIOx->ODR &= ~(1 << u_pinNumber);
	}
}
void GPIO_v_WriteToOutputPort(GPIO_TypeDef *pGPIOx, uint32 u_value)
{
	pGPIOx->ODR = u_value;

}
void GPIO_v_TogglePin(GPIO_TypeDef *pGPIOx, uint8 u_pinNumber)
{
	pGPIOx->ODR ^= (1 << u_pinNumber);
}

void GPIO_v_IRQInteruptConfig(uint8 IRQNumber, uint8 u_enableOrDisable)
{
	if(u_enableOrDisable == ENABLE)
	{
		/* Program ISER register */
		*ISER |= 1u << IRQNumber;
	}
	else
	{
		*ICER |= 1u << IRQNumber;
	}
}

void GPIO_v_IRQPrioConfig(uint8 u_IRQNumber, uint8 u_IRQPriority)
{
	/* IPR register configuration */
	float_t iprRegisterNumber;
	uint8   u_prioritySection;
	uint8   u_shift;

	/* Find out which of 8 IPR registers we need to used. Every register can hold 4 IRQ priorities (8 bits for each IRQ and it's priority) */
	iprRegisterNumber = u_IRQNumber / 4u;
	iprRegisterNumber = (uint8)floor((double)iprRegisterNumber);

	/* Start position of writing for priority. */
	u_prioritySection = u_IRQNumber % 4;

	/* Multiply start of section with 8bit width and add number of bits that are read out in IPR register */
	u_shift = (u_prioritySection * 8u) + (8u - IPR_M0_BITS_IMPLEMENTED);

	IPR->IPRx[(uint8)iprRegisterNumber] |= (u_IRQPriority << (u_shift));
}

void GPIO_v_IRQHandling(uint8 u_pinNumber)
{
	/* Clear EXTI pending register corresponding to the pin number */
	if(EXTI->PR & (1u << u_pinNumber))
	{
		/* Clear PR register for given pin */
		EXTI->PR |= (1 << u_pinNumber);
	}
}

void GPIOx_v_ModeConfig(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration)
{
	uint8   u_port;
	uint8   u_extiBitShift;
	float_t extiToPinMap;

	/* Perform clear bit operation */
	pGPIOx->MODER &= ~(CLEAR_2_BITS << (GPIO_PinConfiguration.GPIO_PinNumber * 2));

	if(GPIO_PinConfiguration.GPIO_PinMode <= ANALOG_MODE)
	{
		/* Non interrupt mode */
	    pGPIOx->MODER |= GPIO_PinConfiguration.GPIO_PinMode << (GPIO_PinConfiguration.GPIO_PinNumber * 2);
	}
	else if(GPIO_PinConfiguration.GPIO_PinMode > ANALOG_MODE)
	{
		/* Interrupt mode */
		if(GPIO_PinConfiguration.GPIO_PinMode == FALING_TRIGGER)
		{
			/* Clear rising trigger */
			EXTI->RTSR &= ~(1u << GPIO_PinConfiguration.GPIO_PinNumber);

			EXTI->FTSR |= (1u << GPIO_PinConfiguration.GPIO_PinNumber);
		}
		else if(GPIO_PinConfiguration.GPIO_PinMode == RISING_TRIGGER)
		{
			/* Clear falling trigger */
			EXTI->FTSR &= ~(1u << GPIO_PinConfiguration.GPIO_PinNumber);

			EXTI->RTSR |= (1u << GPIO_PinConfiguration.GPIO_PinNumber);
		}
		else if(GPIO_PinConfiguration.GPIO_PinMode == RISING_FALLING_TRIGGER)
		{
			EXTI->FTSR |= (1u << GPIO_PinConfiguration.GPIO_PinNumber);

			EXTI->RTSR |= (1u << GPIO_PinConfiguration.GPIO_PinNumber);
		}
		else
		{

		}

		/* Configure GPIO port selection in SYSCFG_EXTICR
		 * For different ports, different values need to be stored in register*/
		u_port = GPOIx_u_PortCheck(pGPIOx);

		/* Check in which of 4 EXTI registers PIN belong */
		extiToPinMap = GPIO_PinConfiguration.GPIO_PinNumber / 4u;

		/* Determine start position of PIN in register */
		u_extiBitShift = GPIO_PinConfiguration.GPIO_PinNumber % 4u;
		SYSCFG_PLCK_EN();

		extiToPinMap = (uint8)floor((double)extiToPinMap);

		SYSCFG->EXTICR[(uint8)extiToPinMap] = u_port << (u_extiBitShift * 4u);

		/* Enable the EXTI interrupt delivery using Interrupt Mask Register */
		EXTI->IMR |= (1 << GPIO_PinConfiguration.GPIO_PinNumber);
	}
	else
	{
		/* TODO: Error handling */
	}
}


void GPIOx_v_SpeedConfig(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration)
{
	/* Perform clear bit operation */
	pGPIOx->OSPEEDR &= ~(CLEAR_2_BITS << (GPIO_PinConfiguration.GPIO_PinNumber * 2));

	pGPIOx->OSPEEDR |= GPIO_PinConfiguration.GPIO_PinSpeed << (GPIO_PinConfiguration.GPIO_PinNumber * 2);

	/* TODO: Error handling of exception */
}

void GPIOx_v_PupdrConfig(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration)
{
	/* Perform clear bit operation */
	pGPIOx->PUPDR &= ~(CLEAR_2_BITS << (GPIO_PinConfiguration.GPIO_PinNumber * 2));
	pGPIOx->PUPDR |= GPIO_PinConfiguration.GPIO_PinPuPdControl << (GPIO_PinConfiguration.GPIO_PinNumber * 2);

	/* TODO: Error handling of exception */
}

void GPIOx_v_OutputConfig(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration)
{
	/* Perform clear bit operation */
	pGPIOx->OTYPER &= ~(CLEAR_1_BIT << (GPIO_PinConfiguration.GPIO_PinNumber * 2));
	pGPIOx->OTYPER |= GPIO_PinConfiguration.GPIO_PinOPType << GPIO_PinConfiguration.GPIO_PinNumber;

	/* TODO: Error handling of exception */
}

void GPIOx_v_AlternateFunctionConfig(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration)
{
	if(GPIO_PinConfiguration.GPIO_PinNumber <= PIN_SEPARATION)
	{
		/* Perform clear bit operation */
		pGPIOx->AFR[0] &= ~(CLEAR_4_BITS << (GPIO_PinConfiguration.GPIO_PinNumber * 2));
		pGPIOx->AFR[0] |= GPIO_PinConfiguration.GPIO_PinAltFunMode << (GPIO_PinConfiguration.GPIO_PinNumber * 4);

		/* TODO: Error handling of exception */
	}
	else if(GPIO_PinConfiguration.GPIO_PinNumber > PIN_SEPARATION)
	{
		/* Perform clear bit operation */
		pGPIOx->AFR[1] &= ~(CLEAR_4_BITS << (GPIO_PinConfiguration.GPIO_PinNumber * 2));
		pGPIOx->AFR[1] |= GPIO_PinConfiguration.GPIO_PinAltFunMode << ((GPIO_PinConfiguration.GPIO_PinNumber - 8u) * 4);

		/* TODO: Error handling of exception */
	}
	else
	{
		/* TODO: Error handling of exception */
	}
}

void GPIOx_v_BitSetResetConfig(GPIO_TypeDef *pGPIOx, GPIO_PinConfig_t GPIO_PinConfiguration, uint8 u_pinSetOrReset)
{
	if(u_pinSetOrReset == SET)
	{
		//pGPIOx->BSRR &= ~(1u << (GPIO_PinConfiguration.GPIO_PinNumber + 16u));
		pGPIOx->BSRR |= 1u << GPIO_PinConfiguration.GPIO_PinNumber;
	}
	else
	{
		//pGPIOx->BSRR &= ~(1u << GPIO_PinConfiguration.GPIO_PinNumber);
		pGPIOx->BSRR |= 1u << (GPIO_PinConfiguration.GPIO_PinNumber + 16u);
	}
}

void GPIOx_BitToggleBsrr(GPIO_TypeDef *pGPIOx, uint8 pinNumber, uint8 u_pinSetOrReset)
{
	if(u_pinSetOrReset == SET)
	{
		pGPIOx->BSRR |= 1u << pinNumber;
	}
	else
	{
		pGPIOx->BSRR |= 1u << (pinNumber + 16u);
	}
}

uint8 GPOIx_u_PortCheck(GPIO_TypeDef *pGPIOx)
{
	/* TODO: Error Handling */

	uint8 u_retVal = 0u;
	if(pGPIOx == GPIOA)
	{
		u_retVal = 0;
	}
	else if(pGPIOx == GPIOB)
	{
		u_retVal = 1u;
	}
	else if(pGPIOx == GPIOC)
	{
		u_retVal = 2u;
	}
	else if(pGPIOx == GPIOD)
	{
		u_retVal = 3u;
	}
	else if(pGPIOx == GPIOE)
	{
		u_retVal = 4u;
	}
	else
	{
		u_retVal = 5u;
	}

	return u_retVal;
}
