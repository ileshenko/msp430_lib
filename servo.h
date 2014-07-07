#ifndef _SERVO_H_
#define _SERVO_H_

#include <config_lib.h>

void servo_init(void);
/* The angle should be in range SRV_ANGLE_MIN .. SRV_ANGLE_MAX */
void servo_set(srv_role_t srv, int angle);

#endif
