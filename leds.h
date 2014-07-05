#ifndef _LEDS_H_
#define _LEDS_H_

#include <config_lib.h>

void leds_init(void);
void leds_hello(led_role_t led);
void led_set(led_role_t led, int val);
void led_toggle(led_role_t led);

#endif /*_LEDS_H_*/
