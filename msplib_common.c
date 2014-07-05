#include "msplib_common.h"
#include <msp430g2553.h>
#include <config_lib.h>

void default_state(void)
{
	/* by default all GPIO should be in IN (High Impedance) direction */
	P1DIR = 0x00;
	P2DIR = 0x00;
	P1REN = 0x00;
	P2REN = 0x00;
}

void clock_init(void)
{
#if DCO_CLK==1
	/* Set DCO to 1 MHz */
	DCOCTL = CALDCO_1MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_1MHZ;				//calibrate basic clock
#elif DCO_CLK==8
	DCOCTL = CALDCO_8MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_8MHZ;				//calibrate basic clock
#elif DCO_CLK==12
	DCOCTL = CALDCO_12MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_12MHZ;				//calibrate basic clock
#elif DCO_CLK==16
	DCOCTL = CALDCO_16MHZ;				//calibrate DCO
	BCSCTL1 = CALBC1_16MHZ;				//calibrate basic clock
#endif

#if MCLK_DIV==1
#define DIVM DIVM_0
#elif MCLK_DIV==2
#define DIVM DIVM_1
#elif MCLK_DIV==4
#define DIVM DIVM_2
#elif MCLK_DIV==8
#define DIVM DIVM_3
#else
#error Incorrect MCLK divider
#endif

#if SMCLK_DIV==1
#define DIVS DIVS_0
#elif SMCLK_DIV==2
#define DIVS DIVS_1
#elif SMCLK_DIV==4
#define DIVS DIVS_2
#elif SMCLK_DIV==8
#define DIVS DIVS_3
#else
#error Incorrect SMCLK divider
#endif

	/* Source for MCLK and SMCLK - DCO */
	BCSCTL2 = SELM_0 | DIVM | /*SELS |*/ DIVS;
}
