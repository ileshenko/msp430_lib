#ifndef _STEP_MOTOR_H_
#define _STEP_MOTOR_H_

#include <config_lib.h>

void stepm_init(void);

/* blocking functions */
void stepm_zeroise(void);
void stepm_set_pos(int pos);
int stepm_get_pos(void);

#endif
