/* **************************************************
 *			    	INCLUDES					    *
 *************************************************  */

#include <NEC_transmission.h>
#include <sys_timer.h>

/* **************************************************
 *					DEFINES 					    *
 *************************************************  */

#define NEC_PULSE_SHORT    560u   /* 560us for a '0' bit pulse   */
#define NEC_PULSE_LONG     1690u  /* 1.7ms for a '1' bit pulse   */
#define NEC_LEADING_BURST  9000u  /* 9ms for the leading burst   */
#define NEC_LEADING_SPACE  4500u  /* 4.5ms for the leading space */
#define NEC_FINAL_BURST    560u   /* 560us for the final burst   */
#define NEC_BIT_LENGHT     32u


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

void NEC_v_SendWholePulse(uint32 duration)
{
    NEC_PulseOn();
    Delay_v_us(duration);
    NEC_PulseOff();
    Delay_v_us(560u);
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

void NEC_v_SendLeadingPulseBurst(void)
{
	NEC_PulseOn();
    Delay_v_us(NEC_LEADING_BURST);
    NEC_PulseOff();
    Delay_v_us(NEC_LEADING_SPACE);
}

void NEC_v_SendFinalPulseBurst(void)
{
	NEC_PulseOn();
    Delay_v_us(NEC_FINAL_BURST);
    NEC_PulseOff();
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
