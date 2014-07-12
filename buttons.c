#include <msp430g2553.h>
#include <config_lib.h>
#include "buttons.h"

void buttons_init(void)
{
#ifdef BTNS_P1
	P1DIR &= ~BTNS_P1;			// IN
	P1SEL &= ~BTNS_P1;			// GPIO mode
	P1REN &= ~BTNS_P1;
	P1REN |= BTNS_P1;			// Poll Up/Down Resistor enable
	P1OUT |= BTNS_P1;			// Poll Up
#endif
#ifdef BTNS_P2
	P2DIR &= ~BTNS_P2;			// IN
	P2SEL &= ~BTNS_P2;			// GPIO mode
	P2REN &= ~BTNS_P2;
	P2REN |= BTNS_P2;			// Poll Up/Down Resistor enable
	P2OUT |= BTNS_P2;			// Poll Up
#endif
}

int button_get(btn_role_t btn)
{
	volatile unsigned char *PxIN = ((btn & PORT_MASK) == PORT_1) ? &P1IN : &P2IN;

	return btn & PIN_MASK & *PxIN;
}

