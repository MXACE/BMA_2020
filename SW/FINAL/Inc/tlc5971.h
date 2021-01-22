#ifndef _TLC5971_C_
#define _TLC5971_C_

#include "main.h"

void RGB_Setup(void);
void RGB_setBC(uint8_t r, uint8_t g, uint8_t b);
void RGB_setLED(char pos, int r, int g, int b);
void LEDC_CLKPuls(void);
void RGB_SHOW(void);

void magnet(char state);

#endif
