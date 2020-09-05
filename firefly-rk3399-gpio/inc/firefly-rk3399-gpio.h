#ifndef __FIREFLY_RK3399_GPIO_H__
#define __FIREFLY_RK3399_GPIO_H__

#define INPUT                    0
#define OUTPUT                   1

#define LOW                      0
#define HIGH                     1

#define PUD_OFF					1
#define PUD_DOWN				2
#define PUD_UP					3
#define PUD_BUS_HOLD			0

extern int firefly_rk3399_initRegMap();
extern void firefly_rk3399_pullUpDnControl (int pin, int pud);
extern int firefly_rk3399_digitalRead (int pin);
extern void firefly_rk3399_digitalWrite (int pin, int value);
extern void firefly_rk3399_pinMode(int pin, int mode );


#endif
