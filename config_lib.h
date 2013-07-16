/* library configuration file */
#ifndef _CONFIG_LIB_H_
#define _CONFIH_LIB_H_

/* Timer section */

//#define USE_ALARM
#define IMPL_TIMER0_A0
#define CONF_TIMER_A0_SRC_SMCLK
#define CONF_TIMER_A0_IE /* Inerrupt Enabled */

/* UART section */
//#define UART_BAUDRATE 9600
#define UART_BAUDRATE 115200
#define UART_TX
#define UART_RX

//#define REPORT_SZ

/* LEDS section */
#define LEDP 1

#define LEDB BIT0
//#define OUT1B BIT2
//#define OUT2B BIT3
#define LEDS (LEDB /*| OUT1B | OUT2B*/)

#if 0
/* Buttons section */
#define BTNP 2

#define CNT1B BIT0
#define CNT2B BIT1
#define BTNB BIT6
#define BTN220B BIT5

#define BTNS (CNT1B | CNT2B | BTNB | BTN220B)
*/
#endif
/* Temperature section */
#if 0
#define T_CNT 5
#define MAXTEMP 140

#define T1B BIT3
#define T1P 3
#define T2B BIT4
#define T2P 4
#define T3B BIT5
#define T3P 5
#define T4B BIT7
#define T4P 7
#define T5B BIT6
#define T5P 6
#define TS (T1B | T2B | T3B | T4B | T5B)

#define T1T ntc1033470
#define T2T ntc1033470
#define T3T ntc1033470
#define T4T ntc1033470
#define T5T ntc1033470

//#define T_UP 0
//#define T_DOWN 1
#endif

/* ADC10 Section */
#define CONF_ADC10_IE
#endif
