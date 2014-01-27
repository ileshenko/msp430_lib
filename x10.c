
#include <config_lib.h>
#include "x10.h"
//#include <string.h>

#include <msp430g2553.h>

#if X10_PORT == 1

#define PxDIR  P1DIR
#define PxREN P1REN
#define PxIE P1IE
#define PxIES P1IES
#define PxIFG P1IFG
#define PxOUT P1OUT
#define PxIN P1IN
#define PxSEL P1SEL
#define PxSEL2 P1SEL2

#elif X10_OUT_P == 2

#define PxDIR  P2DIR
#define PxREN P2REN
#define PxIE P2IE
#define PxIES P2IES
#define PxIFG P2IFG
#define PxOUT P2OUT
#define PxIN P2IN
#define PxSEL P2SEL
#define PxSEL2 P2SEL2
#else
#error define X10 port
#endif

#ifdef X10TX

static unsigned char curr, buff[8];
static unsigned char tx_stage;

static void x10_timer_init(void)
{
	/* Timer B */
	/* Source SMCLK (1MHz) TASSEL_2
	 * divider 8 (125 kHz) ID_3
	 * Mode STOP MC_0 now, but Up to CCR0 (MC_1) later
	 * //Interrupt IV enable TAIE
	 */
    TA1CTL = TASSEL_2 | ID_3 | MC_0 /*| TAIE*/;
    TA1CCR0 = 125*3; /* 3ms delay */
    TA1CCTL0 = CCIE;

}

void x10tx_init(void)
{
	/* Switch to GPIO mode */
	PxSEL &= ~(X10_OUT_B | X10_ZC_B);
	PxSEL2 &= ~(X10_OUT_B | X10_ZC_B);

	PxDIR &= ~X10_ZC_B; /* Set ZC detector as Input */
	PxDIR |= X10_OUT_B; /* Set output as output :) */
	PxOUT |= X10_OUT_B; /* By default - high state */

//	PxREN |= BTNS;									// Poll Up/Down Resistor enable
//	PxOUT |= BTNS;									// Poll Up

	PxIE |= X10_ZC_B; /* Interrupt Enabled */
	PxIES |= X10_ZC_B; /* Hi/Lo edge */
	PxIFG &= ~X10_ZC_B; /* IFG cleared */

	x10_timer_init();
	
	tx_stage = 0;
}

void x10tx_putn(unsigned char *ch, int len)
{
	curr = len - 1 ;
	
	while (len--)
		buff[len] = *ch++;

	tx_stage = 10;
}

static inline void x10_zc(void)
{
	if (!--tx_stage)
	{
		if (curr--)
			tx_stage = 10;
	}
	else if (tx_stage < 9 && !(buff[curr] & 1<<(tx_stage-1)))
		return;

	PxOUT &= ~X10_OUT_B;
    TA1CTL |= MC_1; /* Start timer */
}

#pragma vector = PORT1_VECTOR
__interrupt void port1_isr (void)
{
	if (PxIFG & X10_ZC_B)
	{
		PxIFG &= ~X10_ZC_B;
		if (tx_stage)
			x10_zc();
	}
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer_b_a0_isr(void)
{
	PxOUT |= X10_OUT_B; /* Set output to inactive state */

    TA1CTL &= ~MC_3; /* Stop timer */
    TA1R = 0; /* clear timer counter */
}
#endif

#ifdef X10RX
static void (*rx_cb)(unsigned char ch);
static unsigned char rx_stage, rx_buff;
static unsigned int last_ms_cnt;
extern unsigned int ms_cnt;

void x10rx_init(void (*cb)(unsigned char ch))
{
	rx_cb = cb;

	/* Switch to GPIO mode */
	PxSEL &= ~X10_IN_B;
	PxSEL2 &= ~X10_IN_B;

	PxDIR &= ~X10_IN_B; /* Set pin as Input */
	PxREN |= X10_IN_B; /* Pull Up/Down Resistor enable */
	PxOUT |= X10_IN_B; /* Pull UP */

	PxIE |= X10_IN_B; /* Interrupt Enabled */
	PxIES |= X10_IN_B; /* Hi/Lo edge */
	PxIFG &= ~X10_IN_B; /* IFG cleared */

	rx_stage = 0;
	last_ms_cnt = 0;
}

static inline void x10_rx_isr(void)
{
	unsigned int delta = ms_cnt - last_ms_cnt;

	last_ms_cnt = ms_cnt;

	if (delta > 100)
		rx_stage = 0;

	if (!rx_stage++)
		return;

	delta += 5; /* tolerance +- 5 ms */

	for (; delta > 20; delta -= 10)
	{
		rx_stage++;
		rx_buff <<= 1;
	}

	if (rx_stage > 10)
	{
		rx_stage = 0;
	}
	else if (rx_stage == 10)
	{
		rx_cb(rx_buff);
		rx_stage = 0;
	}
	else
	{
		rx_buff <<= 1;
		rx_buff |= 0x1;
	}
}

#pragma vector = PORT1_VECTOR
__interrupt void port1_isr (void)
{
	if (PxIFG & X10_IN_B)
	{
		PxIFG &= ~X10_IN_B;
		x10_rx_isr();
	}
}

#endif
