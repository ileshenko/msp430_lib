#ifndef _X10_H_
#define _X10_H_

void x10tx_init(void);
void x10tx_putn(unsigned char *ch, int len);
//int x10_is_ready(void);

void x10rx_init(void (*cb)(unsigned char ch));

#if 0
//void uart_report(char *line);
void uart_data(char *data, int len);

char *cat_ul(char *buf, unsigned long val);
char *cat_str(char *buf, char *str);
#define tab_ul(buf, val) cat_ul(cat_str(buf, "\t"), val)

#endif
#endif /*_X10_H_*/
