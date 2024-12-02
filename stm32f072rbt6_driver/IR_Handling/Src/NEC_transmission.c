/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <NEC_transmission.h>
#include <sys_timer.h>
#include <config.h>

/* **************************************************
 *					DEFINES 					    *
 *************************************************  */

#define NEC_PULSE_SHORT    		     560u   		/* 560us for a '0' bit pulse   	*/
#define NEC_PULSE_LONG     			 1690u  		/* 1.7ms for a '1' bit pulse   	*/
#define NEC_FINAL_BURST	   			 560u
#define NEC_PREFINAL_BURST_ZHJT03    7400u
#define NEC_BIT_LENGHT     			 32u

#if (ZHJT03_REMOTE == STD_ON && STANDARD_REMOTE == STD_OFF)
	#define NEC_LEADING_BURST  6100u
#else
	#define NEC_LEADING_BURST  9000u
#endif

#if (ZHJT03_REMOTE == STD_ON && STANDARD_REMOTE == STD_OFF)
	#define NEC_LEADING_SPACE  7300u
#else
	#define NEC_LEADING_SPACE  4500u
#endif


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
static void NEC_PulseOn(void);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \param[out] - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
static void NEC_PulseOff(void);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \param[out] - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
static void NEC_v_SendWholePulse(uint32 duration);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \param[out] - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
static void NEC_v_SendBit(uint8 u_bit);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \param[out] - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
static void NEC_v_SendLeadingPulseBurst(void);

/**
 *
 * \brief      - TODO
 * \param[in]  - TODO
 * \param[out] - TODO
 * \return     - TODO
 * \globals    - TODO
 *
 */
static void NEC_v_SendFinalPulseBurst(void);

/****************************************************/

static void NEC_PulseOn(void)
{
	/* Enable the timer to output signal */
    TIM2->CR1 |= TIM_CR1_CEN;
}

static void NEC_PulseOff(void)
{
	/* Disable timer, no pulse */
    TIM2->CR1 &= ~TIM_CR1_CEN;
}

static void NEC_v_SendWholePulse(uint32 duration)
{
    NEC_PulseOn();
    Delay_v_us(499u);
    NEC_PulseOff();
    Delay_v_us(duration);
}

static void NEC_v_SendBit(uint8 u_bit)
{
    if (u_bit)
    {
    	NEC_v_SendWholePulse(NEC_PULSE_LONG);  /* Send a '1' bit pulse (1.7ms) */
    }
    else
    {
        NEC_v_SendWholePulse(NEC_PULSE_SHORT); /* Send a '0' bit pulse (560µs) */
    }
}

static void NEC_v_SendLeadingPulseBurst(void)
{
	NEC_PulseOn();
    Delay_v_us(NEC_LEADING_BURST);
    NEC_PulseOff();
    Delay_v_us(NEC_LEADING_SPACE);
}

static void NEC_v_SendFinalPulseBurst(void)
{
	NEC_PulseOn();
	Delay_v_us(NEC_FINAL_BURST);
    NEC_PulseOff();
#if (ZHJT03_REMOTE == STD_ON && STANDARD_REMOTE == STD_OFF)
    Delay_v_us(NEC_PREFINAL_BURST_ZHJT03);
    NEC_PulseOn();
    Delay_v_us(NEC_FINAL_BURST);
    NEC_PulseOff();
#endif
}

void NEC_v_SendMessage(uint32 *codeBuffer, uint8 u_size)
{
	uint8 i;
	uint8 j;
	uint8 bit;

	NEC_v_SendLeadingPulseBurst();

	for (i = 0; i < u_size; i++)
	{
		for(j = 0; j < NEC_BIT_LENGHT; j++)
		{
			bit = ( (codeBuffer[i] >> (31u - j)) & 1u );
			NEC_v_SendBit(bit);
		}
	}
	NEC_v_SendFinalPulseBurst();

}
