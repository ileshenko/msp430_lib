#ifndef _TIMER_LIB_H_
#define _TIMER_LIB_H_

void timer_init(void);

#ifdef FEATURE_RTC
extern unsigned long jiffies;

void rtc_sleep(void);
/* Low Resolution Sleep - delay measured in jiffies */
void rtc_sleep_for(unsigned int j_ticks);
/* High Resolution Sleep - in main clock ticks */
void rtc_hr_sleep(unsigned int hr_ticks);
#endif

#endif
