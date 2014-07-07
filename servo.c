#include <msp430g2553.h>
#include <config_lib.h>
#include "servo.h"

void servo_init(void)
{
#ifdef SERVO_P1
#error TODO
#endif

#ifdef SERVO_P2
	/* Servo 1. JP7, P2.2.
	 * Pin to mode TA1.1:
	 * DIR - 1
	 * SEL - 1
	 * SEL2 - 0
	 */
	P2DIR |= SERVO_P2;
	P2SEL |= SERVO_P2;

	/* Port 2 works with TA1 */
#if SERVO_T1 & TA_X_0
#error check this code.
	TA1CCTL0 = OUTMOD_7;			// CCR1 reset/set
	TA1CCR0 = (SERVO_0 + SERVO_180)>>1;					// CCR1 PWM duty cycle
#endif
#if SERVO_T1 & TA_X_1
	TA1CCTL1 = OUTMOD_7;			// CCR1 reset/set
	TA1CCR1 = (SERVO_0 + SERVO_180)>>1;					// CCR1 PWM duty cycle
#endif
#if SERVO_T1 & TA_X_2
	TA1CCTL2 = OUTMOD_7;			// CCR1 reset/set
	TA1CCR2 = (SERVO_0 + SERVO_180)>>1;					// CCR1 PWM duty cycle
#endif
#endif
}

void servo_set(srv_role_t srv, int angle)
{
	static const float degree_weight = ((float)SERVO_180 - (float)SERVO_0)/1800.0;
	int val;

	if (angle < SRV_ANGLE_MIN)
		angle = SRV_ANGLE_MIN;
	else if (angle > SRV_ANGLE_MAX)
		angle = SRV_ANGLE_MAX;

	val = angle*degree_weight +  SERVO_0;
	switch (srv & TA_MASK)
	{
#if SERVO_T1 & TA_X_0
	case TA_X_0:
		TA1CCR0 = val;
		break;
#endif
#if SERVO_T1 & TA_X_1
	case TA_X_1:
		TA1CCR1 = val;
		break;
#endif
#if SERVO_T1 & TA_X_2
	case TA_X_2:
		TA1CCR2 = val;
		break;
#endif
	}
}
