#ifndef NEC_TRANSMISSION_H_
#define NEC_TRANSMISSION_H_

/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <stm32f072x8.h>
#include <types.h>

/* **************************************************
 *			    FUNCTION PROTOTYPE 					*
 *************************************************  */

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \param[out] - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
void NEC_v_SendMessage(uint32 *codeBuffer, uint8 u_size);

#endif /* NEC_TRANSMISSION_H_ */
