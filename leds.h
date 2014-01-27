#ifndef _LEDS_H_
#define _LEDS_H_

#include <config_lib.h>

void leds_init(void);
void leds_hello(void);
void led_toggle(void);

#ifdef OUT1B
void out1_turn(int on);
#endif
#ifdef OUT2B
void out2_turn(int on);
#endif


#endif /*_LEDS_H_*/
