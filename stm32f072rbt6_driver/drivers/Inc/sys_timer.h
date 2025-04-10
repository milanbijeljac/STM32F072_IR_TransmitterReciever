#ifndef INC_SYS_TIMER_H_
#define INC_SYS_TIMER_H_

/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <stm32f072x8.h>
#include <types.h>

/****************************************************/

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
void TIM3_v_cfg(uint8 u_frequency);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
void Delay_v_us (uint16 us);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
void Delay_v_ms (uint16 ms);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
void Delay_v_seconds(uint16 seconds);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
void TIM2_v_IrFrequencyCfg(void);

#endif /* INC_SYS_TIMER_H_ */
