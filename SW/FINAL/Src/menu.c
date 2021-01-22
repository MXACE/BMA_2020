#include "main.h"
#include "ssd1351.h"
#include "gfx.h"
#include "menu.h"
#include "menu_windows.h"
#include "COM.h"
#include <stdio.h>
#include "FLASH_SECTOR.h"

#define BACKGROUND colors.blue
extern Colors colors;
	
uint8_t ACTIVE_MENU = 0;

uint8_t x = 0;
uint8_t y = 0;
uint8_t oldx = 0;
uint8_t oldy = 0;

void drawButton(uint8_t ButtonNumber,uint8_t selected);
void drawText(uint8_t TextNumber, uint8_t selected);

void Button_manager(uint8_t pressedButton)
{
	oldy = y;
	oldx = x;
	uint8_t changed = 0;
	
	if(pressedButton == 5)
	{
		MenuGoto(x,y);
	}
	if(!menu[ACTIVE_MENU].OnlyMidButton)
	{
		switch(pressedButton)
		{
			case 1:
				if(y > 0)
				{
					y -= 1;
				}
				else
				{
					//y = ButtonMax(1,0);
					y = menu[ACTIVE_MENU].MaxY;
				}
				if(menu[ACTIVE_MENU].MaxY > 0)
				{
					changed = 1;
				}
				break;
			case 2:
				if(x > 0)
				{
					x -= 1;
				}
				else
				{
					//x = ButtonMax(0,0);
					x = menu[ACTIVE_MENU].MaxX;
				}
				if(menu[ACTIVE_MENU].MaxX > 0)
				{
					changed = 1;
				}
				break;
			case 3:
				//if(x >= ButtonMax(0,0))
				if(x >= menu[ACTIVE_MENU].MaxX)
				{
					x = 0;
				}
				else
				{
					x += 1;
				}
				if(menu[ACTIVE_MENU].MaxX > 0)
				{
					changed = 1;
				}
				break;
			case 4:
				//if(y >= ButtonMax(1,0))
				if(y >= menu[ACTIVE_MENU].MaxY)
				{
					y = 0;
				}
				else
				{
					y += 1;
				}
				if(menu[ACTIVE_MENU].MaxY > 0)
				{
					changed = 1;
				}
				break;
				break;
				
			default:
				break;
		}
	
		if(changed)
		{
			setButton(x,y);
		}
	}
	
	changed = 0;
}

char Menu_Flags(uint8_t pos, uint8_t set)
{
	/*	Flag 0: LEDs
	 * 	Flag 1: Motor
	 * 	Flag 2: Info
	 * 	Flag 3: Start
	 * 	Flag 4: back
	*/
	volatile static uint8_t flags[10] = {0,0,0,0,0,0,0,0,0,0};
	uint8_t flag_buf = 0;

	char string_buf[1] = {0};

	switch(set)
	{
	case 0:
		flag_buf = flags[pos];
		flags[pos] = 0;

		sprintf(string_buf, "%i", pos);
		COM_TX("[FLAG]: READ ");
		COM_TX(string_buf);
		COM_TX("\r\n");

		return flag_buf;
		break;

	case 1:

		sprintf(string_buf, "%i", pos);
		COM_TX("[FLAG]: SET ");
		COM_TX(string_buf);
		COM_TX("\r\n");

		flags[pos] = 1;
		break;
	}
	return 0;
}

void MenuGoto(uint8_t ButtonX, uint8_t ButtonY)
{
	switch(ACTIVE_MENU)
	{
		//Main
		case 0:
			//QR
			if(ButtonX == 0 && ButtonY == 0)
			{
				COM_TX("[MENU]: GOTO QR\r\n");
				SetMenu(3);
			}
			//INFO
			if(ButtonX == 0 && ButtonY == 1)
			{
				COM_TX("[MENU]: GOTO INFO\r\n");
				Menu_Flags(2,1);
				SetMenu(6);
			}
			//MOTOR
			if(ButtonX == 0 && ButtonY == 2)
			{
				COM_TX("[MENU]: GOTO MOTOR READY\r\n");
				Menu_Flags(1,1);
				SetMenu(2);
			}
			//LEDs
			if(ButtonX == 0 && ButtonY == 3)
			{
				COM_TX("[MENU]: GOTO LED READY\r\n");
				Menu_Flags(0,1);
				SetMenu(2);
			}
			break;
			
		//Ready
		case 1:
			//BACK
			if(HAL_GPIO_ReadPin(SUPPLY_SUPPLY_GPIO_Port,SUPPLY_SUPPLY_Pin))
			{
				if(ButtonX == 0 && ButtonY == 0)
				{
					COM_TX("[MENU]: GOTO MAIN\r\n");
					Menu_Flags(4,1);
					Menu_Flags(0,0);
					Menu_Flags(1,0);
					SetMenu(1);
				}
			}
			else
			{
				if(ButtonX == 0 && ButtonY == 0)
				{
					COM_TX("[MENU]: GOTO MAIN\r\n");
					Menu_Flags(4,1);
					Menu_Flags(0,0);
					Menu_Flags(1,0);
					SetMenu(7);
				}
			}
			//START
			if(ButtonX == 0 && ButtonY == 1)
			{
				COM_TX("[MENU]: GOTO MIX\r\n");
				Menu_Flags(3,1);
				SetMenu(5);	
			}
			break;
			
		//QR
		case 2:
			if(HAL_GPIO_ReadPin(SUPPLY_SUPPLY_GPIO_Port,SUPPLY_SUPPLY_Pin))
			{
				if(ButtonX == 0 && ButtonY == 0)
				{
					COM_TX("[MENU]: GOTO MAIN\r\n");
					SetMenu(1);
				}
			}
			else
			{
				if(ButtonX == 0 && ButtonY == 0)
				{
					COM_TX("[MENU]: GOTO MAIN\r\n");
					SetMenu(7);
				}
			}
			break;
		
		//MAIN
		case 3:
			break;
		//INFO
		case 5:
			if(HAL_GPIO_ReadPin(SUPPLY_SUPPLY_GPIO_Port,SUPPLY_SUPPLY_Pin))
			{
				if(ButtonX == 0 && ButtonY == 0)
				{
					COM_TX("[MENU]: GOTO MAIN\r\n");
					SetMenu(1);
				}
			}
			else
			{
				if(ButtonX == 0 && ButtonY == 0)
				{
					COM_TX("[MENU]: GOTO MAIN\r\n");
					SetMenu(7);
				}
			}
			break;
		//Main
		case 6:
			//QR
			if(ButtonX == 0 && ButtonY == 0)
			{
				COM_TX("[MENU]: GOTO QR\r\n");
				SetMenu(3);
			}
			//INFO
			if(ButtonX == 0 && ButtonY == 1)
			{
				COM_TX("[MENU]: GOTO INFO\r\n");
				Menu_Flags(2,1);
				SetMenu(6);
			}
			//MOTOR
			if(ButtonX == 0 && ButtonY == 2)
			{
				COM_TX("[MENU]: GOTO LED READY\r\n");
				Menu_Flags(0,1);
				SetMenu(2);
			}
			break;
		default:
			break;
	}
	
}

void SetMenu(uint8_t MenuNumber)
{
	//uint8_t counter = 0;
	ACTIVE_MENU = MenuNumber - 1;
	blankscreen(BACKGROUND);
	x = 0;
	y = 0;
	switch(MenuNumber)
	{
		//Main
		case 1:
			drawMenu();
			break;
		//Ready
		case 2:
			y = 1;
			drawMenu();
			break;
		//QR
		case 3:
			show_QRCODE();
			break;
		//LOGO
		case 4:
			show_LOGO();
			break;
		//Mixing
		case 5:
			show_Mix();
			break;
		case 6:
			show_INFO();
			break;
		case 7:
			drawMenu();
			break;
		case 8:
			show_Ready();
			break;
	}
	setButton(x,y);
}

char ButtonMax(uint8_t xy, uint8_t set)
{
	static uint8_t Max = 0;
	uint8_t counter = 0;
	if(set)
	{
		Max = menu[ACTIVE_MENU].buttonConfig[0][xy];
		for(counter = 1; counter != menu[ACTIVE_MENU].buttonAmount; counter++)
		{
			if(menu[ACTIVE_MENU].buttonConfig[counter][xy] > Max)
			{
				Max = menu[ACTIVE_MENU].buttonConfig[counter][xy];
			}
		}
		for(counter = 1; counter != menu[ACTIVE_MENU].buttonAmount; counter++)
		{
			if(menu[ACTIVE_MENU].buttonConfig[counter][xy] > Max)
			{
				Max = menu[ACTIVE_MENU].buttonConfig[counter][xy];
			}
		}
	}
	return Max;
}

void setButton(uint8_t ButtonX, uint8_t ButtonY)
{
	uint8_t counter = 0;
	
	for(counter = 0; counter != menu[ACTIVE_MENU].buttonAmount; counter++)
	{
		if(oldx == menu[ACTIVE_MENU].buttonConfig[counter][0] && oldy == menu[ACTIVE_MENU].buttonConfig[counter][1])
		{
			drawButton(counter, 0);
			drawText(counter,0);
		}
	}
	
	for(counter = 0; counter != menu[ACTIVE_MENU].buttonAmount; counter++)
	{
		if(ButtonX == menu[ACTIVE_MENU].buttonConfig[counter][0] && ButtonY == menu[ACTIVE_MENU].buttonConfig[counter][1])
		{
			drawButton(counter, 1);
			drawText(counter,1);
		}
	}
}

void drawMenu(void)
{
	blankscreen(BACKGROUND);
	uint8_t counter = 0;
	
	for(counter = 0; counter != menu[ACTIVE_MENU].buttonAmount; counter++)
	{
			drawButton(counter,0);
			drawText(counter,0);
	}
	
}

void drawButton(uint8_t ButtonNumber,uint8_t selected)
{
	if(selected)
	{
		filled_rect_xy_ab(
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][0],
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][1],
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][2],
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][3],
			colors.gray,
			0);
	}
	else
	{
		filled_rect_xy_ab(
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][0],
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][1],
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][2],
			menu[ACTIVE_MENU].buttonPos[ButtonNumber][3],
			colors.white,
			0);
	}
}
void drawText(uint8_t TextNumber, uint8_t selected)
{
	if(selected)
	{
		stringxy((char *)menu[ACTIVE_MENU].buttonText[TextNumber],
		menu[ACTIVE_MENU].buttonTextPos[TextNumber][0],
		menu[ACTIVE_MENU].buttonTextPos[TextNumber][1],
		colors.white,colors.gray,0);
	}
	else
	{
		stringxy((char *)menu[ACTIVE_MENU].buttonText[TextNumber],
		menu[ACTIVE_MENU].buttonTextPos[TextNumber][0],
		menu[ACTIVE_MENU].buttonTextPos[TextNumber][1],
		colors.black,colors.white,0);
	}
}

void show_QRCODE(void)
{
	uint8_t counterX = 0,counterY = 0;
		
	for(counterY = 0 ; counterY != 25; counterY++)
	{
		for(counterX = 0 ; counterX != 25; counterX++)
		{
			if(QR_CODE_GITHUB[counterX][counterY])
			{
				filled_rect_xy_ab(14+4*counterY,14+4*counterX,4,4,colors.black,0);
			}
		}
	}
}

void show_LOGO(void)
{
	uint8_t counterX = 0,counterY = 0;
		
	for(counterY = 0 ; counterY != 57; counterY++)
	{
		for(counterX = 0 ; counterX != 128; counterX++)
		{
			if(LOGO[counterY][counterX])
			{
				plot_dot_xy_extern(counterX,93-counterY,colors.black,0);
			}
		}
	}
}

void show_Mix(void)
{
	stringxy("Preparing",10,60,colors.white,BACKGROUND,0);
}
void show_INFO(void)
{
	uint32_t data[] = {0,0,0,0};
	int number[4] = {0,0,0,0};

	char LEDAmount[5] = {0,0,0,0,0};
	char LEDRate[5] = {0,0,0,0,0};
	char MotorAmount[5] = {0,0,0,0,0};
	char MotorRate[5] = {0,0,0,0,0};

	//Flash_Read_Data(0x08060000, data);

	/*for(int i = 0; i != 4; i++)
	{
		number[i] = data[i] - 0xAAAAAAAA;
	}

	sprintf(LEDAmount, "%i", number[0]);
	sprintf(LEDRate, "%i%c", ((int)100/(number[0]/number[1])), '%'); // KEEP = 100
	//sprintf(LEDRate, "%i", number[1]);
	sprintf(MotorAmount, "%i", number[2]);
	sprintf(MotorRate, "%i%c", (100/(number[2]/number[3])), '%');
	//sprintf(MotorRate, "%i", number[3]);
*/
	stringxy("BMA 2020 BEL17a",5,100,colors.black,BACKGROUND,0);
	stringxy("Lionardo Wernli",5,86,colors.black,BACKGROUND,0);
	stringxy("Marco Stauber",5,72,colors.black,BACKGROUND,0);

	/*stringxy("LED tries", 5, 50,colors.black,BACKGROUND,0);
	stringxy(LEDAmount, 90, 50,colors.black,BACKGROUND,0);

	stringxy("LED rate",5,36,colors.black,BACKGROUND,0);
	stringxy(LEDRate, 90, 36,colors.black,BACKGROUND,0);

	stringxy("Motor tries",5,22,colors.black,BACKGROUND,0);
	stringxy(MotorAmount, 90, 22,colors.black,BACKGROUND,0);

	stringxy("Motor rate",5,8,colors.black,BACKGROUND,0);
	stringxy(MotorRate, 90, 8,colors.black,BACKGROUND,0);*/
}

void show_Ready(void)
{
	stringxy("READY",45,60,colors.black,colors.green,0);
}
