
#include <msp430g2553.h>
#include <config.h>
#include "clock.h"


void clock_init(void)
{
	/* Set DCO to 1 MHz */
	DCOCTL = CALDCO_1MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_1MHZ;				//calibrate basic clock

	/* MCLK - 1MHz (MCLK = DCO/1)*/
	/* SMCLK - 1MHz (SMCLK = DCO/1)*/
	BCSCTL2 = SELM_0 | DIVM_0 | /*SELS |*/ DIVS_0; // .
}
