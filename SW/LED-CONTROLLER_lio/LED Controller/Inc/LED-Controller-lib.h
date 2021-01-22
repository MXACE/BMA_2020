#ifndef __LEDCONTROLLERLIB_H
#define __LEDCONTROLLERLIB_H



#include <stm32f4xx.h>	 																															//Fun Fact: Wird als nicht gefunden angezeigt. Wenn aber Entfernt, fehlen Begrifflichkeiten wie TIM3_SR
#include <stm32f407xx.h>
#include <string.h>
#include <stdbool.h>

void LEDC_DATA(void);
void LEDC_CLKPuls(void);
void LEDC_Set(void);

typedef struct LEDC
{
	char DataPosition;
	char DataN;
}LEDC;




#endif
