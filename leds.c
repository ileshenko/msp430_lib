#include <msp430g2553.h>
#include <config_lib.h>
#include "leds.h"
//#include "main.h"

#if LEDP == 1
#define PxDIR  P1DIR
#define PxOUT P1OUT
#define PxSEL P1SEL
#define PxREN P1REN
#elif LEDP == 2
#define PxDIR  P2DIR
#define PxOUT P2OUT
#define PxSEL P2SEL
#define PxREN P2REN
#else
#error define LED port
#endif

void leds_init(void)
{
	PxDIR |= LEDS;			// OUT
	PxSEL &= ~LEDS;			// GPIO mode
	PxREN &= ~LEDS;

	PxOUT &= ~LEDS;			// Switch Off
}

void led_toggle(void)
{
	PxOUT ^= LEDB;
}

#ifdef OUT1B
void out1_turn(int on)
{
	if (on)
		PxOUT |= OUT1B;
	else
		PxOUT &= ~OUT1B;
}
#endif

#ifdef OUT2B
void out2_turn(int on)
{
	if (on)
		PxOUT |= OUT2B;
	else
		PxOUT &= ~OUT2B;
}
#endif

void leds_hello(void)
{
	int i;
	volatile int j;

	for (i = 5; i; i--)
	{
		led_toggle();
		j = 0x3fff;
		while(--j);
	}
}
