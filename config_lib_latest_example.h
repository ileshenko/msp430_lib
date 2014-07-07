/* library configuration file */
/* PHOne ROBOt project */
#ifndef _CONFIG_LIB_H_
#define _CONFIG_LIB_H_

/* ==========================================================================
 *          Features list
 * ==========================================================================
 */
#define FEATURE_SERVO
#define FEATURE_LEDS
#undef FEATURE_BUTTONS

/* ==========================================================================
 * 			Generic macros, used in different features
 * ==========================================================================
 */
#define PORT_1 0
#define PORT_2 0x100
#define PORT_MASK PORT_2
#define TA_SHIFT 9
#define TA_MASK (0x7 << TA_SHIFT)
#define TA_X_0 (0x1 << TA_SHIFT)
#define TA_X_1 (0x2 << TA_SHIFT)
#define TA_X_2 (0x4 << TA_SHIFT)
/* ==========================================================================
 * 			Clock section
 * ==========================================================================
 */

/* Internal digitally controlled oscillator DCO frequency in MHz.
 * Possible values are 1 8 12 16 */
#define DCO_CLK 8

/* Divider for Master Clock. Possible values are 1, 2, 4, 8, */
#define MCLK_DIV 1

/* Divider for Sub Master Clock. Possible values are 1, 2, 4, 8, */
#define SMCLK_DIV 1

/* TODO configurable input for Master Clock (MCLK) and Sub Main Clock (SMLK)
 * Currently both of them driven by DCO */

/* ==========================================================================
 *			Timer section
 * ==========================================================================
 * Timer A - AKA TA0
 * Timer B - AKA TA1 (Timer B from User MAnual is not present in MSP430G2553)
 */

/* Timer A subsection */
#define CONF_TIMER_A0_USE
#ifdef CONF_TIMER_A0_USE

/* Possible sources TACLK, ACLK, SMLK, INCLK */
/*  CONF_TIMER_A0_SRC_TACLK CONF_TIMER_A0_SRC_ACLK CONF_TIMER_A0_SRC_SMCLK CONF_TIMER_A0_SRC_INCLK */
#define CONF_TIMER_A0_SRC_SMCLK

#define CONF_TIMER_A0_DIV 8

/* Possible modes "up to CCR0", "up", "up/down" */
/* CONF_TIMER_A0_MODE_UP_TO_CCR0 CONF_TIMER_A0_MODE_UP CONF_TIMER_A0_MODE_UP_DOWN */
#define CONF_TIMER_A0_MODE_UP
#endif

/* Timer B subsection */
#define CONF_TIMER_A1_USE
#ifdef CONF_TIMER_A1_USE
#define CONF_TIMER_A1_SRC_SMCLK
#define CONF_TIMER_A1_DIV 8
#define CONF_TIMER_A1_MODE_UP_TO_CCR0
#define CONF_TIMER_A1_CCR0_VAL 20000 /* 1 MHz (Timer A1), 20 ms - period */
//#define CONF_TIMER_B_IV_IE /* timer B (AKA TA1) Interrupt Enabled */
#endif



//#define USE_ALARM
#define CONF_TIMER_A_IV_IE /* timer A (AKA TA0) Interrupt Enabled */
/* UART section */
//#define UART_BAUDRATE 300
#define UART_BAUDRATE 9600
//#define UART_BAUDRATE 115200
#define UART_TX
//#define UART_RX

//#define REPORT_SZ


/* X10 section */
//#define X10TX
#ifdef X10TX
/* We assume, that OUT and Zero Cross pins belongs to the same port */
#define X10_PORT 1
#define X10_OUT_B BIT2
#define X10_ZC_B BIT0 /* Zero Cross Detector Bit */

#define CONF_PORT1_VECTOR /* disable ZC interrupt stub */
#define CONF_TIMER_B_CCR0_IE /* Use timer B (AKA TA1) for short time x10 bursts */
#endif

//#define X10RX
#ifdef X10RX
#define X10_PORT 1
#define X10_IN_B BIT1

#define CONF_PORT1_VECTOR /* disable port interrupt stub */

#endif

/* ============================ LEDS section ================== */
#ifdef FEATURE_LEDS
#define LEDS_P1 (BIT3 | BIT4 | BIT5)
#define LEDS_P2 (BIT0 | BIT1 | BIT4)

typedef enum {
	MLF = PORT_2 | BIT1, /* Motor Left Forward */
	MLR = PORT_2 | BIT0, /* Motor Left Reverse */
	MRF = PORT_1 | BIT5, /* Motor Right Forward */
	MRR = PORT_1 | BIT4, /* Motor Right Reverse */
	TURBO = PORT_1 | BIT3,
	LED = PORT_2 | BIT4
} led_role_t;
#endif

#ifdef FEATURE_BUTTONS
/* Buttons section */
#define BTNP 2

#define CNT1B BIT0
#define CNT2B BIT1
#define BTNB BIT6
#define BTN220B BIT5

#define BTNS (CNT1B | CNT2B | BTNB | BTN220B)
*/
#endif

/* ============================ SERVO section ================== */
#ifdef FEATURE_SERVO
//#define SERVO_P1 ()
#define SERVO_P2 (BIT2 | BIT5)
#define SERVO_T1 (TA_X_1 | TA_X_2)

typedef enum {
	SRV1 = TA_X_1 | PORT_2 | BIT2, /* JP7 */
	SRV2 = TA_X_2 | PORT_2 | BIT5  /* JP6 */
} srv_role_t;

/* In theory - valid pulse width is 1 .. 2 ms.
 * Really measured for HK15138 range 0.6 .. 2.6 ms
 */
#define SERVO_0 600
#define SERVO_180 2600
#define SRV_ANGLE_MIN 0
#define SRV_ANGLE_MAX 1800
#endif
/* ==========================================================================
 *			Audio Jack section
 * ==========================================================================
 */

#define JACK_P2 (BIT6 | BIT7)
#define JACK_L BIT6
#define JACK_R BIT7
#define CONF_PORT2_VECTOR /* disable port interrupt stub */

/* Temperature section */
#define T_CNT 5
#define MAXTEMP 100

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

/* ADC10 Section */
//#define CONF_ADC10_IE
#endif
