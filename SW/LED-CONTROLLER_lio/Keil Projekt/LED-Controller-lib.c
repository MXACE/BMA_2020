/* ================================================================================ */
/* @autor   Lionardo Wernli                                                         */
/* @file    LED-CONTROLLER.c                                                        */
/* @date    28.08.2020                                                              */
/* @uC      STM32F407VET                                                            */
/* @purpose Libary für LED-Controller TLC5971                                       */
/* ================================================================================ */

#include <stm32f4xx.h>	 																															//Fun Fact: Wird als nicht gefunden angezeigt. Wenn aber Entfernt, fehlen Begrifflichkeiten wie TIM3_SR
#include <stm32f407xx.h>
#include <string.h>
#include <stdbool.h>

struct LEDC
{
	char DataPosition;
	char DataN;
};

void LEDC_DATA(void);
void LEDC_CLKPuls(void);
bool buffer[2][224] = 
{
	{																 //LED Controller 2
	1,0,0,1,0,1,                             //WRITE 25h
	0, 					                     //OUTTMG
	0,					                     //EXTGCK
	0,					                     //TMGRST
	0,					                     //DSPRPT
	0,					                     //BLANK
	0,0,0,0,0,0,0,									 //BCB
	0,0,0,0,0,0,0,									 //BCG
	0,0,0,0,0,0,0,									 //BCR
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  //GSR0
	}, 
	{                                //LED Controller 1
	1,0,0,1,0,1,                     //WRITE 25h
	0, 					                     //OUTTMG
	0,					                     //EXTGCK
	0,					                     //TMGRST
	0,					                     //DSPRPT
	0,					                     //BLANK
	0,0,0,0,0,0,0,									 //BCB
	0,0,0,0,0,0,0,									 //BCG
	0,0,0,0,0,0,0,									 //BCR
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSB0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  //GSR0
	} 
};


void LEDC_Set(void)
{
	for(int i = 0; i < strlen(buffer[LEDC.DataN][]);i++)
	{
		LEDC_DATA();
		LEDC_CLKPuls();
	}
}

void LEDC_DATA(void)
{
	if(LEDC.DataPosition >= strlen(buffer[LEDC.DataN][]))
	{
		LEDC.DataN++;
		LEDC.DataPosition = 0;
	}
	if(LEDC.DataN >= 3)
	{
		LEDC.DataN = 0;
	}
	GPIOC -> ODR = buffer[LEDC.DataN][LEDC.DataPosition] << 7;
}

void LEDC_CLKPuls(void)
{
	GPIOC -> ODR = 1 << 6;
	for(int i = 0; i<12;i++);
	GPIOC -> ODR = 0 << 6;
}