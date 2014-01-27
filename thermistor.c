#include <msp430g2553.h>
#include <config_lib.h>
#include "thermistor.h"


#include "ntc1033470_gnd_472.c"
//#include "ntc1523950_gnd_471.c"

//#define BIT(bit) (1<<bit)
#if 0
static const char tb[T_CNT] =
{
		T1B,
#ifdef T2B
		T2B,
#endif
#ifdef T3B
		T3B,
#endif
#ifdef T4B
		T4B,
#endif
#ifdef T5B
		T5B,
#endif
#ifdef T6B
		T6B,
#endif
#ifdef T7B
		T7B,
#endif
};
#endif

static const char tp[T_CNT] =
{
		T1P,
#ifdef T2P
		T2P,
#endif
#ifdef T3P
		T3P,
#endif
#ifdef T4P
		T4P,
#endif
#ifdef T5P
		T5P,
#endif
#ifdef T6P
		T6P,
#endif
#ifdef T7P
		T7P,
#endif
};

static const int *ntc[T_CNT] =
{
		T1T,
#ifdef T2T
		T2T,
#endif
#ifdef T3T
		T3T,
#endif
#ifdef T4T
		T4T,
#endif
#ifdef T5T
		T5T,
#endif
#ifdef T6T
		T6T,
#endif
#ifdef T7T
		T7T,
#endif
};

int t[T_CNT];

#define BSIZE 16

#if BSIZE == 16
#define B_SHIFT 4
#elif BSIZE == 8
#define B_SHIFT 3
#else
#error
#endif
//const int *ntc;

int adc_buff[BSIZE];
#define ADC10CTL_INCH(port) (((unsigned int)port)<<12)

//int temp_up, temp_bottom, temp_ctl;

void thermistor_init(void)
{
	int i;

    ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON; //  ??? SHT2? IE???
    ADC10AE0 = TS /*BIT(UP_PORT) + BIT(BOTTOM_PORT) + BIT(CTL_PORT)*/; // ADC ports option select
    ADC10DTC1 = BSIZE;                           // Conversions count
    
    for (i = 0; i < T_CNT; i++)
    	t[i] = 0;
    
//    ntc=ntc1033470;
//    ntc=ntc2233600;
}

static inline unsigned int get_average(void)
{
	unsigned int ret = 0;
	int i;
	
	for (i = 0; i< BSIZE; i++)
		ret += adc_buff[i];
		
	return ret>>B_SHIFT;
}

static inline int thermistor_ntc(unsigned int idx, unsigned int raw)
{
	unsigned int ret;
	
	for (ret = 0; ret < MAXTEMP; ret++)
	{
		if (ntc[idx][ret] <= raw)
			return ret;
	}
	return ret;
}

//static const char sensor_map[] = {UP_PORT /*, BOTTOM_PORT, CTL_PORT*/};

static int themp_get(int idx)
{
//	char port;
	unsigned int raw_val;

//	port = sensor_map[sensor];
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active

    ADC10CTL1 = ADC10CTL_INCH(tp[idx]) + CONSEQ_2; // Set channel. Repeat single channel

    ADC10SA = (unsigned int)adc_buff;//0x200;                        // Data buffer start
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion ready
    while (!(ADC10CTL0 & ADC10IFG));               // Wait if ADC10 core is active
    ADC10CTL0 &= ~ADC10IFG;					// Clear interrupt flag
    
    raw_val = get_average();
		
	return  thermistor_ntc(idx, raw_val);
}

void themps_update(void)
{
	int i;

	for (i = 0; i < T_CNT; i++)
		t[i] = themp_get(i);
//    up_up = themp_get(SEN_UP);
//    temp_bottom = themp_get(SEN_BOTTOM);
//    temp_ctl = themp_get(SEN_CTL);
}

#ifdef T_UP
int themp_delta_get(void)
{
    if (!t[T_UP] || !t[T_DOWN])
    	return 0;
    	
    return t[T_UP] - t[T_DOWN];
}
#endif
