
#include <config_lib.h>
#include "uart.h"
#include <string.h>

#include <msp430g2553.h>

//char report[128];
char *to_print;
unsigned int uart_idx, uart_len;

#ifdef UART_RX
static void (*rx_cb)(unsigned char);
#endif

#ifdef UART_TX
static void (*tx_ready_cb)(void);
#endif

void uart_init(void)
{
#ifdef UART_RX
	rx_cb = NULL;
#endif

#ifdef UART_TX
	tx_ready_cb = NULL;
#endif

	UCA0CTL1 |= UCSWRST; //toggle SW Reset on

	/* P1.1 - RXD
	 * P1.2 - TXD
	 */
	/* Each port may be overridden later if we need one direction only */
	P1SEL |= BIT1 | BIT2; //select RXD and TXD for UART
	P1SEL2 |= BIT1 | BIT2; //select RXD and TXD for UART

	/* UCSYNC = 0 (ASYNC),
	 * UCMODE = 0 (UART),
	 * UCSPB = 0 (one stop),
	 * UC7BIT = 0 (8 bit),
	 * UCMSB = 0 (LSB first),
	 * UCPEN = 0 (No Parity) */
	UCA0CTL0 = 0;

	/* input - SMCLK (1MHz) */
	UCA0CTL1 |= UCSSEL_3; /* SMCLK (0x3)*/

#if UART_BAUDRATE == 300
	/* Baud Rate Control */
	UCA0BR0 = 208;
	UCA0BR1 = 0;
	/* Modulation Control */
	UCA0MCTL = UCBRF_5 | UCBRS_0 | UCOS16;
#elif UART_BAUDRATE == 9600
	/* Baud Rate Control */
	UCA0BR0 = 6;
	UCA0BR1 = 0;
	/* Modulation Control */
	UCA0MCTL = UCBRF_8 | UCBRS_0 | UCOS16;
#elif UART_BAUDRATE == 115200
	/* Baud Rate Control */
	UCA0BR0 = 8;
	UCA0BR1 = 0;
	/* Modulation Control */
	UCA0MCTL = UCBRF_0 | UCBRS_6;
#else
#error Unknown UART Boudrate
#endif

	UCA0CTL1 &= ~UCSWRST; //toggle SW Reset off
}

#ifdef UART_RX
void uart_rx_cb(void (*cb)(unsigned char))
{
     rx_cb = cb;
     IE2 |= UCA0RXIE;
}
#endif

#ifdef UART_TX
void uart_tx_ready_cb(void (*cb)(void))
{
     tx_ready_cb = cb;
}
#endif


char *cat_ul(char *buf, unsigned long val)
{
	unsigned long cutoffVal = val/10;
	
	if (cutoffVal)
		buf = cat_ul(buf, cutoffVal);
	
	*buf = '0' + val%10;

	*(buf+1) = 0;
	return buf+1;
}

char *cat_str(char *buf, char *str)
{
	while (*str)
		*buf++ = *str++;
	*buf = 0;
	return buf;
}

void uart_data(char *data, int len)
{
	to_print = data;
	uart_idx = 0;
	uart_len = len;
	IE2 |= UCA0TXIE;
}

void uart_text(char *line)
{
	int len = strlen(line);
	uart_data(line, len);
}

void uart_report(char *line)
{
	to_print = line;
#if 0
	char *buf = report;
	unsigned int cnt1_A;

	_DINT();
	cnt1_A = cnt1_a;
	cnt1_a = 0;
	_EINT();
	
	buf = cat_ul(buf, jiffies);
	buf = cat_str(buf, "\t");
	buf = cat_ul(buf, cnt1_A);
	buf = cat_str(buf, "\t");
	buf = cat_ul(buf, cnt1_b);
# if 0
	buf = cat_ul(buf, curr_state);
	buf = cat_str(buf, "\t");
	buf = cat_ul(buf, temp_up);
	buf = cat_str(buf, "\t");
	buf = cat_ul(buf, temp_bottom);
	buf = cat_str(buf, "\t");
	buf = cat_ul(buf, temp_ctl);
#endif

	buf = cat_str(buf, "\r\n");
	*buf = 0; 
#endif
	uart_idx = 0;
	IE2 |= UCA0TXIE;
}

#if 0
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR (void)
{
  UCA0TXBUF = to_print[i++];				// TX next character

  if (!to_print[i])							// TX over?
    IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
}
#endif

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	UCA0TXBUF = to_print[uart_idx++];				// TX next character

	if (uart_idx != uart_len)
		return;

	IE2 &= ~UCA0TXIE;                       // Disable USCI_A0 TX interrupt
	if (tx_ready_cb)
		tx_ready_cb();
}

#ifdef UART_RX
#pragma vector = USCIAB0RX_VECTOR
__interrupt void uscib0rx_isr(void)
{
	unsigned char byte = UCA0RXBUF;
	if (rx_cb)
		rx_cb(byte);
}
#endif

