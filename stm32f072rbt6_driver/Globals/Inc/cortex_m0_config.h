#ifndef INC_CORTEX_M0_CONFIG_H_
#define INC_CORTEX_M0_CONFIG_H_

#include <types.h>

/************************************************   Cortex - M0 information  ******************************************************************/

#define ISER_BASE	0xE000E100u
#define ICER_BASE	0xE000E180u
#define ISPR_BASE	0xE000E200u
#define ICPR_BASE	0xE000E280u
#define IPR_BASE	0xE000E400u

typedef struct
{
	volatile uint32 IPRx[8];				/*!< Interrupt priority configuration register */

}IPR_TypeDef;


#define ISER		((volatile uint32*)ISER_BASE)		/* Interrupt Set Enable Register 	*/
#define ICER		((volatile uint32*)ICER_BASE)		/* Interrupt Clear Enable Register 	*/
#define ISPR		((volatile uint32*)ISPR_BASE)		/* Interrupt Set Pending Register 	*/
#define ICPR		((volatile uint32*)ICPR_BASE)		/* Interrupt Clear Enable Register 	*/
#define IPR         ((IPR_TypeDef *) IPR_BASE)			/* Interrupt Priority Register 		*/


#define IPR_M0_BITS_IMPLEMENTED 		2u

#endif /* INC_CORTEX_M0_CONFIG_H_ */
