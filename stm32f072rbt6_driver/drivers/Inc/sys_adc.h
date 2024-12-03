#ifndef INC_SYS_ADC_H_
#define INC_SYS_ADC_H_

/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <stm32f072x8.h>
#include <types.h>
#include <sys_timer.h>

/****************************************************/

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
uint8 ADCx_u_Init(ADC_TypeDef* p_ADCx, uint8 channel);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
uint16 ADCx_u_Read(ADC_TypeDef* p_ADCx);

#endif /* INC_SYS_ADC_H_ */
