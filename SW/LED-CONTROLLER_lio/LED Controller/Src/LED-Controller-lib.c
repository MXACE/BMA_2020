/* ================================================================================ */
/* @autor   Lionardo Wernli                                                         */
/* @file    LED-CONTROLLER.c                                                        */
/* @date    28.08.2020                                                              */
/* @uC      STM32F407VET                                                            */
/* @purpose Libary für LED-Controller TLC5971                                       */
/* ================================================================================ */


#include "LED-Controller-lib.h"
LEDC Data = 
{
	.DataPosition = 0,
	.DataN = 0,
};

bool buffer[2][224] = 
{
	{																 //LED Controller 2
	1,0,0,1,0,1,                             //WRITE 25h
	1, 					                     //OUTTMG
	0,					                     //EXTGCK
	1,					                     //TMGRST
	1,					                     //DSPRPT
	0,					                     //BLANK
	1,1,1,1,1,1,1,									 //BCB
	0,0,0,0,0,0,0,									 //BCG
	0,0,0,0,0,0,0,									 //BCR
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG3
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSR3
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR2
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG1
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSR1
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB0
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSG0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  //GSR0
	}, 
	{                                //LED Controller 1
	1,0,0,1,0,1,                             //WRITE 25h
	1, 					                     //OUTTMG
	0,					                     //EXTGCK
	1,					                     //TMGRST
	1,					                     //DSPRPT
	0,					                     //BLANK
	1,1,1,1,1,1,1,									 //BCB
	0,0,0,0,0,0,0,									 //BCG
	0,0,0,0,0,0,0,									 //BCR
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB3
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG3
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSR3
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG2
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSR2
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB1
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, //GSG1
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSR1
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSB0
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //GSG0
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  //GSR0
	} 
};

char LEDC_DataLenghs = sizeof buffer / sizeof buffer[0];

void LEDC_Set(void)
{
	for(int i = 0; i < LEDC_DataLenghs;i++)
	{
		LEDC_DATA();
		LEDC_CLKPuls();
	}
}

void LEDC_DATA(void)
{
	if(Data.DataPosition >= LEDC_DataLenghs)
	{
		Data.DataN++;
		Data.DataPosition = 0;
	}
	if(Data.DataN >= 3)
	{
		Data.DataN = 0;
	}
	GPIOC -> ODR = buffer[Data.DataN][Data.DataPosition] << 7;
}

void LEDC_CLKPuls(void)
{
	GPIOC -> ODR = 1 << 6;
	for(int i = 0; i<12;i++);
	GPIOC -> ODR = 0 << 6;
}
