#ifndef _TLC5971_C_
#define _TLC5971_C_

#include "main.h"

char OUTTMG = 1; //Out-timing
char EXTGCK = 0; //Ext. Clock
char TMGRST = 1; //Timing reset
char DSPRPT = 1; //Display repeat
char BLANK = 0; //Blank (clear leds)

void RGB_Setup(void);
void RGB_setBC(uint8_t r, uint8_t g, uint8_t b);
void RGB_setLED(char pos, int r, int g, int b);
void LEDC_CLKPuls(void);
void RGB_SHOW(void);

void magnet(char state);

#endif
