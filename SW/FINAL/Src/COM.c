#include "main.h"
#include <string.h>
#include "COM.h"


extern UART_HandleTypeDef huart1;

void COM_TX(char string[])
{
	HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), 2000);
}	

