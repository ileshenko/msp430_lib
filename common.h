#ifndef _COMMON_H_
#define _COMMON_H_

//#define UART_BAUDRATE 9600
#define MAGIC_BEGIN 0xAC
#define MAGIC_END 0xDC
#define LEDS_CNT 5

void default_state(void);
void clock_init(void);

//#define BTN BIT3
//#define LED1 BIT0
//#define LED2 BIT6

//void leds_init(void);
void uart_init(void);


#endif
