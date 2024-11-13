/*
 * sys_delay.h
 *
 *  Created on: Jan 21, 2024
 *      Author: Milan
 */

#ifndef INC_SYS_TIMER_H_
#define INC_SYS_TIMER_H_

#include <stm32f072x8.h>
#include <types.h>

#define US_TO_MS 1000u
#define MS_TO_S  1000u

/**
 * @fn				- Function used to configure general purpose timer TIM3.
 *
 * @brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]		- GPIO_TypeDef *pGPIOx - base address of GPIOx port
 * @param[in]		- uint8 enabledOrDisabled - or disable port
 *
 * @return			-
 *
 * @Note			-
 *
 */
void TIM3_v_cfg(uint8 u_frequency);

/**
 * @fn				- Delay_v_us
 *
 * @brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]		- GPIO_TypeDef *pGPIOx - base address of GPIOx port
 * @param[in]		- uint8 enabledOrDisabled - or disable port
 *
 * @return			-
 *
 * @Note			-
 *
 */
void Delay_v_us (uint16 us);

/**
 * @fn				- Delay_v_ms
 *
 * @brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]		- GPIO_TypeDef *pGPIOx - base address of GPIOx port
 * @param[in]		- uint8 enabledOrDisabled - or disable port
 *
 * @return			-
 *
 * @Note			-
 *
 */
void Delay_v_ms (uint16 ms);

/**
 * @fn				- Delay_v_seconds
 *
 * @brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]		- GPIO_TypeDef *pGPIOx - base address of GPIOx port
 * @param[in]		- uint8 enabledOrDisabled - or disable port
 *
 * @return			-
 *
 * @Note			-
 *
 */
void Delay_v_seconds(uint16 seconds);

/**
 * \fn				- Delay_v_seconds
 *
 * \brief			- This function enables or disables peripheral clock for the given GPIO port
 *
 * \param[in]		- GPIO_TypeDef *pGPIOx - base address of GPIOx port
 * \param[in]		- uint8 enabledOrDisabled - or disable port
 *
 * \return			-
 *
 * \Note			-
 *
 */
void TIM2_v_IrFrequencyCfg(void);

#endif /* INC_SYS_TIMER_H_ */
