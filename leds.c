#include <msp430g2553.h>
#include <config_lib.h>
#include "leds.h"

void leds_init(void)
{
#if LEDS_P1
	P1DIR |= LEDS_P1;			// OUT
	P1SEL &= ~LEDS_P1;			// GPIO mode
	P1REN &= ~LEDS_P1;

	P1OUT &= ~LEDS_P1;			// Switch Off
#endif
#if LEDS_P2
	P2DIR |= LEDS_P2;			// OUT
	P2SEL &= ~LEDS_P2;			// GPIO mode
	P2REN &= ~LEDS_P2;

	P2OUT &= ~LEDS_P2;			// Switch Off
#endif
}

void led_toggle(led_role_t led)
{
	volatile unsigned char *PxOUT = ((led & PORT_MASK) == PORT_1) ? &P1OUT : &P2OUT;

	*PxOUT ^= led & ~PORT_MASK;
}

void led_set(led_role_t led, int val)
{
	volatile unsigned char *PxOUT = ((led & PORT_MASK) == PORT_1) ? &P1OUT : &P2OUT;

	if (val)
		*PxOUT |= led & ~PORT_MASK;
	else
		*PxOUT &= ~(led & ~PORT_MASK);

}

void leds_hello(led_role_t led)
{
	int i, k;
	volatile int j;

	for (i = 5; i; i--)
	{
		led_toggle(led);
		k = DCO_CLK;
		while (k--)
		{
			j = 0x3fff;
			while(--j);
		}
	}
}
