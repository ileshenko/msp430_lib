/*
 * irq_stubs.c
 *
 *  Created on: Mar 4, 2013
 *      Author: Igor
 */
#include <msp430g2553.h>
#include <config_lib.h>

#ifndef CONF_TIMER_A_CCR0_IE
#pragma vector=TIMER0_A0_VECTOR
__interrupt void t0_a0_Stub (void)
{
	for (;;);
}
#endif

#ifndef CONF_TIMER_B_CCR0_IE
#pragma vector=TIMER1_A0_VECTOR
__interrupt void t1_a0_Stub (void)
{
	for (;;);
}

#endif

#ifndef CONF_TIMER_A_IV_IE
#pragma vector=TIMER0_A1_VECTOR
__interrupt void t0_a1_Stub (void)
{
	for (;;);
}
#endif

#ifndef CONF_TIMER_B_IV_IE
#pragma vector=TIMER1_A1_VECTOR
__interrupt void t1_a1_Stub (void)
{
	for (;;);
}
#endif

#pragma vector=WDT_VECTOR
__interrupt void wdt_Stub (void)
{
	for (;;);
}

#ifndef CONF_PORT1_VECTOR
#pragma vector = PORT1_VECTOR
__interrupt void port1_Stub (void)
{
		for (;;);
}
#endif

#ifndef CONF_PORT2_VECTOR
#pragma vector=PORT2_VECTOR
__interrupt void port2_Stub (void)
{
	for (;;);
}
#endif

//#pragma vector=USI_VECTOR

#ifndef CONF_ADC10_IE
#pragma vector=ADC10_VECTOR
__interrupt void adc10_Stub (void)
{
	for (;;);
}
#endif

#pragma vector=NMI_VECTOR
__interrupt void nmi_Stub (void)
{
	for (;;);
}

#pragma vector=COMPARATORA_VECTOR
__interrupt void comparator_Stub (void)
{
	for (;;);
}

#ifndef UART_RX
#pragma vector = USCIAB0RX_VECTOR
__interrupt void uscib0rx_Stub (void)
{
	for (;;);
}
#endif

#ifndef UART_TX
#pragma vector = USCIAB0TX_VECTOR
__interrupt void uscib0tx_Stub (void)
{
	for (;;);
}
#endif
