#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include <config_lib.h>

void buttons_init(void);

/* returns true if pressed */
int button_get(btn_role_t btn);

#endif /* BUTTONS_H_ */
