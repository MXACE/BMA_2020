#include "rng.h"
#include "main.h"
#include "COM.h"
#include <stdio.h>

extern RNG_HandleTypeDef hrng;
uint64_t temp_rng = 0;
	char buffer[50];

uint32_t GenerateRandomNumber()
{
		HAL_RNG_GenerateRandomNumber(&hrng,(uint32_t *)&temp_rng); //generiere Random Number
//		HAL_Delay(500);	//verezoegerung von 500ms
	sprintf(buffer, "RandomNum: %lld \n", temp_rng); //Konvertiere dezimalzahl zu einem String
		COM_TX(buffer); //Schreibe String auf Seriel Schnittstelle
		return temp_rng; //gebe zahl zurück 
}
