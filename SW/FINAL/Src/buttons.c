#include "main.h"
#include "menu.h"
#include "COM.h"

char ReadButtons(uint8_t ButtonNumber)
{
	switch(ButtonNumber)
	{
		case 1:
			if(HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port,BUTTON_1_Pin))
			{
				return 1;
			}
			break;
			
		case 2:
			if(HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port,BUTTON_2_Pin))
			{
				return 1;
			}
			break;
			
		case 3:
			if(HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port,BUTTON_3_Pin))
			{
				return 1;
			}
			break;
			
		case 4:
			if(HAL_GPIO_ReadPin(BUTTON_4_GPIO_Port,BUTTON_4_Pin))
			{
				return 1;
			}
			break;
			
		case 5:
			if(HAL_GPIO_ReadPin(BUTTON_5_GPIO_Port,BUTTON_5_Pin))
			{
				return 1;
			}
			break;
			
		case 6:
			if(HAL_GPIO_ReadPin(BUTTON_6_GPIO_Port,BUTTON_6_Pin))
			{
				return 1;
			}
			break;
		}
	return 0;
}

char ReadJogpad(void)
{
	static uint8_t OldState[5] = {0,0,0,0,0};
	volatile uint8_t ButtonPressed[5] = {0,0,0,0,0};
	uint8_t ButtonChanged[5] = {0,0,0,0,0};
	
	if(HAL_GPIO_ReadPin(JOGPAD_TOP_GPIO_Port,JOGPAD_TOP_Pin))
	{
		ButtonPressed[0] = 1;
	}
	else
	{
		ButtonPressed[0] = 0;
	}
	
	if(HAL_GPIO_ReadPin(JOGPAD_LEFT_GPIO_Port,JOGPAD_LEFT_Pin))
	{
		ButtonPressed[1] = 1;
	}
	else
	{
		ButtonPressed[1] = 0;
	}
	
	if(HAL_GPIO_ReadPin(JOGPAD_RIGHT_GPIO_Port,JOGPAD_RIGHT_Pin))
	{
		ButtonPressed[2] = 1;
	}
	else
	{
		ButtonPressed[2] = 0;
	}
	
	if(HAL_GPIO_ReadPin(JOGPAD_BOTTOM_GPIO_Port,JOGPAD_BOTTOM_Pin))
	{
		ButtonPressed[3] = 1;
	}
	else
	{
		ButtonPressed[3] = 0;
	}
	
	if(HAL_GPIO_ReadPin(JOGPAD_MID_GPIO_Port,JOGPAD_MID_Pin))
	{
		ButtonPressed[4] = 1;
	}
	else
	{
		ButtonPressed[4] = 0;
	}
	
	//Buttons Changed
	unsigned char i = 0;
	for(i = 0; i != 5; i++)
	{
		if(ButtonPressed[i] != OldState[i])
		{
			ButtonChanged[i] = 1;
		}
		else
		{
			ButtonChanged[i] = 0;
		}
	}
	
	//Save new button state
	for(i = 0; i != 6; i++)
	{
		OldState[i] = ButtonPressed[i];
	}
	
	if(ButtonPressed[0] && ButtonChanged[0])
	{
		//COM_TX("TOP");
		return 4;
	}
	if(ButtonPressed[1] && ButtonChanged[1])
	{
		//COM_TX("LEFT");
		return 2;
	}
	if(ButtonPressed[2] && ButtonChanged[2])
	{
		//COM_TX("RIGHT");
		return 3;
	}
	if(ButtonPressed[3] && ButtonChanged[3])
	{
		//COM_TX("BOT");
		return 1;
	}
	if(ButtonPressed[4] && ButtonChanged[4])
	{
		//COM_TX("MID");
		return 5;
	}
	return 0;
}
