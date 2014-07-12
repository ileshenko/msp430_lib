#include <msp430g2553.h>
#include <config_lib.h>
#include "step_motor.h"
#include "leds.h"
#include "buttons.h"
#include "timer_lib.h"

#define COIL_PATTERN 0x36 /* 0011 0110 */

#define STEP_DELAY (20 * HZ / 1000) /* 20 ms per step */

static int stepm_pos;

void stepm_init(void)
{
	stepm_pos = -1;
	led_set(ST_ON, 1); /* Switch driver off */
}

static void coils_set(int idx)
{
	unsigned int coil = COIL_PATTERN;

	idx &= 0x3;
	coil >>= idx;
	led_set(ST_AP, coil & 0x1);
	led_set(ST_AN, !(coil & 0x1));

	coil >>= 4;
	led_set(ST_BP, coil & 0x1);
	led_set(ST_BN, !(coil & 0x1));

	rtc_sleep_for(STEP_DELAY);

}

void stepm_zeroise(void)
{
	if (stepm_pos == -1)
		stepm_pos = 4;

	led_set(ST_ON, 0);

	while (button_get(ST_ZERO) || (stepm_pos & 0x3) )
		coils_set(--stepm_pos);

	stepm_pos = 0;

	led_set(ST_ON, 1);
}

void stepm_set_pos(int pos)
{
	int delta;

	if (pos <= 0 )
	{
		stepm_zeroise();
		return;
	}
	if (pos > STEPM_POS_MAX)
		pos = STEPM_POS_MAX;

	if  (pos == stepm_pos)
		return;

	delta = (pos < stepm_pos) ? -1 : +1;
	led_set(ST_ON, 0);
	rtc_sleep_for(STEP_DELAY);

	while (pos != stepm_pos)
	{
		stepm_pos += delta;
		coils_set(stepm_pos);
		if (delta < 0 && !(stepm_pos & 0x3) && !button_get(ST_ZERO))
		{
			stepm_pos = 0;
			break;
		}
	}
	led_set(ST_ON, 1);
}

int stepm_get_pos(void)
{
	return stepm_pos;
}
