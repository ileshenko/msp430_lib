#include <msp430g2553.h>
#include <config_lib.h>
#include "timer_lib.h"

void timer_init(void)
{
	/* Timer A */
	/* Source SMCLK (1MHz) TASSEL_2
	 * divider 8 (125 kHz) ID_3
	 * Mode UP/Down MC_3
	 * Interrupt enable TAIE
	 */
#ifdef CONF_TIMER_A0_SRC_SMCLK
    TA0CTL = TASSEL_2 | ID_3 | MC_3 | TAIE;
    TA0CCR0 = 0xF424; /* 125 kHz / 2 */
#endif
#ifdef CONF_TIMER_A0_IE
    TA0CTL |= TAIE;
#endif
}

