#ifndef _THERMISTOR_H_
#define _THERMISTOR_H_

//#define UP_PORT 4
//#define BOTTOM_PORT 5
//#define CTL_PORT 1

//extern int temp_up, temp_bottom, temp_ctl;

#if 0
typedef enum {
	SEN_UP = 0,
	SEN_BOTTOM = 1,
	SEN_CTL = 2 /* third sensor for investigation purpoces */
} sensor_t;
#endif

void thermistor_init(void);
//int themp_get(sensor_t sensor);
void themps_update(void);
/* Does not actually measure themperatures. Call themps_update() before */
int themp_delta_get(void);

extern int t[];

#endif /*_THERMISTOR_H_*/
