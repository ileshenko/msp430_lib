#include <msp430g2553.h>
#include <config_lib.h>
#include "timer_lib.h"


#ifdef FEATURE_RTC

unsigned long jiffies;

static void rtc_init(void)
{
	jiffies = 0;
}

void rtc_sleep(void)
{
	_BIS_SR(LPM0_bits + GIE);
}

void rtc_sleep_for(unsigned int j_ticks)
{
	while (j_ticks--)
		rtc_sleep();
}

#if defined (CONF_RTC_SRC_A_CCR0)
#pragma vector=TIMER0_A0_VECTOR
#elif defined (CONF_RTC_SRC_B_CCR0)
#pragma vector=TIMER1_A0_VECTOR
#else
#error
#endif
__interrupt void rtc_isr(void)
{
	jiffies++;
	_BIC_SR_IRQ(LPM0_bits);
}


#if 0 /* Good example for future */
#pragma vector=TIMER1_A1_VECTOR
__interrupt void main_timer(void)
{
	switch(TA1IV)
	{
	case 10: /* TAIFG, timer overflow */
		break;
	case 2: /* TACCR1 CCIFG, compare 1 */
	case 4: /* TACCR2 CCIFG, compare 2 */
	default: /* impossible! */
		for (;;);
	}

	timeout++;
	jiffies++;

	_BIC_SR_IRQ(LPM0_bits);
}
#endif
#endif

void timer_init(void)
{
/* Timer A0 */
#ifdef CONF_TIMER_A0_USE
    TA0CTL = 0;
#if defined(CONF_TIMER_A0_SRC_TACLK)
#error TODO
#elif defined(CONF_TIMER_A0_SRC_ACLK)
#error TODO
#elif defined(CONF_TIMER_A0_SRC_SMCLK)
    TA0CTL |= TASSEL_2;
#elif defined(CONF_TIMER_A0_SRC_INCLK)
#error TODO
#else
#error Undefined TA0 source
#endif

#if CONF_TIMER_A0_DIV == 1
    TA0CTL |= ID_0;
#elif CONF_TIMER_A0_DIV == 2
    TA0CTL |= ID_1;
#elif CONF_TIMER_A0_DIV == 4
    TA0CTL |= ID_2;
#elif CONF_TIMER_A0_DIV == 8
    TA0CTL |= ID_3;
#else
#error Wrong TA0 divider
#endif

#ifdef CONF_TIMER_A0_MODE_UP_TO_CCR0
    TA0CTL |= MC_1;
    TA0CCR0 = CONF_TIMER_A0_CCR0_VAL;
#elif defined CONF_TIMER_A0_MODE_UP
    TA0CTL |= MC_2;
#elif defined CONF_TIMER_A0_MODE_UP_DOWN
    TA0CTL |= MC_3;
    TA0CCR0 = CONF_TIMER_A0_CCR0_VAL;
#endif

#ifdef CONF_TIMER_A_CCR0_IE
    TA0CCTL0 = CCIE;
    //TA0CTL |= TAIE;
#endif
#endif

/* Timer A1 */
#ifdef CONF_TIMER_A1_USE
    TA1CTL = 0;
#if defined(CONF_TIMER_A1_SRC_TACLK)
#error TODO
#elif defined(CONF_TIMER_A1_SRC_ACLK)
#error TODO
#elif defined(CONF_TIMER_A1_SRC_SMCLK)
    TA1CTL |= TASSEL_2;
#elif defined(CONF_TIMER_A1_SRC_INCLK)
#error TODO
#else
#error Undefined TA1 source
#endif

#if CONF_TIMER_A1_DIV == 1
    TA1CTL |= ID_0;
#elif CONF_TIMER_A1_DIV == 2
    TA1CTL |= ID_1;
#elif CONF_TIMER_A1_DIV == 4
    TA1CTL |= ID_2;
#elif CONF_TIMER_A1_DIV == 8
    TA1CTL |= ID_3;
#else
#error Wrong TA1 divider
#endif

#ifdef CONF_TIMER_A1_MODE_UP_TO_CCR0
    TA1CTL |= MC_1;
    TA1CCR0 = CONF_TIMER_A1_CCR0_VAL;
#elif defined CONF_TIMER_A1_MODE_UP
    TA1CTL |= MC_2;
#elif defined CONF_TIMER_A1_MODE_UP_DOWN
    TA1CTL |= MC_3;
    TA1CCR0 = CONF_TIMER_A1_CCR0_VAL;
#endif

#ifdef CONF_TIMER_B_CCR0_IE
    TA1CCTL0 = CCIE;
    //TA1CTL |= TAIE;
#endif
#endif

#if 0
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
#endif

#ifdef FEATURE_RTC
    rtc_init();
#endif
}


