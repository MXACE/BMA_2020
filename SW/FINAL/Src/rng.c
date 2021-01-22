#include "rng.h"
#include "main.h"
#include "COM.h"
#include <stdio.h>

extern RNG_HandleTypeDef hrng;
volatile char string_buffer[50];

uint32_t GenerateRandomNumber()
{
		uint64_t temp_rng = 0;

		HAL_RNG_GenerateRandomNumber(&hrng,(uint32_t *)&temp_rng); //generiere Random Number
//		HAL_Delay(500);	//verezoegerung von 500ms
		sprintf(string_buffer, "%u", temp_rng); //Konvertiere dezimalzahl zu einem String
		COM_TX("[RNG]: ");
		COM_TX(string_buffer); //Schreibe String auf Seriel Schnittstelle
		COM_TX("\r\n");
		return temp_rng; //gebe zahl zurück 
}


uint8_t RNG_Prepare(uint8_t *number)
{
	//static uint8_t number[10] = {0,0,0,0,0,0,0,0,0,0};

	uint8_t counter = 0;
	uint8_t temp = 0;

	number[0] = GenerateRandomNumber() % 10;

	while(1)
	{
		if(number[counter] > 6 || number[counter] == 0)
		{
			number[counter] = GenerateRandomNumber() % 10;
		}
		else
		{
			counter++;
		}
		if(counter >= 10)
		{
			break;
		}
	}

	if(number[7] < number[8])
	{
		temp = number[8];
		number[8] = number[7];
		number[7] = temp;
	}
	if(number[7] < 3)
	{
		number[7] = 3;
	}

	//sprintf(string_buffer, "%i", number); //Konvertiere dezimalzahl zu einem String
	for(counter = 0; counter != 10; counter++)
	{
		string_buffer[counter] = number[counter] + 48;
	}

	COM_TX("[RNG]: Final Number: ");
	COM_TX(string_buffer); //Schreibe String auf Seriel Schnittstelle
	COM_TX("\r\n");

	return 0;
}
