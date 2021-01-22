#include "main.h"
#include "ssd1351.h"
#include "gfx.h"
#include "menu.h"
#include "menu_windows.h"

#define BACKGROUND colors.blue
extern Colors colors;
	
uint8_t ACTIVE_MENU = 0;

uint8_t x = 0;
uint8_t y = 0;
uint8_t oldx = 0;
uint8_t oldy = 0;

void drawButton(char ButtonNumber,char selected);
void drawText(char TextNumber, char selected);

void Button_manager(char pressedButton)
{
	oldy = y;
	oldx = x;
	char changed = 0;
	
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
				changed = 1;
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
				changed = 1;
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
				changed = 1;
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
				changed = 1;
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

void MenuGoto(char ButtonX, char ButtonY)
{
	switch(ACTIVE_MENU)
	{
		//Main
		case 0:
			//QR
			if(ButtonX == 0 && ButtonY == 0)
			{
				SetMenu(3);
			}
			//INFO
			if(ButtonX == 0 && ButtonY == 1)
			{
				SetMenu(6);
			}
			//MOTOR
			//LEDs
			if(ButtonX == 0 && ButtonY == 3)
			{
				SetMenu(2);
			}
			break;
			
		//Ready
		case 1:
			//BACK
			if(ButtonX == 0 && ButtonY == 0)
			{
				SetMenu(1);
			}
			//START
			if(ButtonX == 0 && ButtonY == 1)
			{
				SetMenu(5);	
			}
			break;
			
		//QR
		case 2:
			if(ButtonX == 0 && ButtonY == 0)
			{
				SetMenu(1);
			}
			break;
		
		//MAIN
		case 3:
			break;
		
		
		default:
			break;
		//INFO
		case 5:
			if(ButtonX == 0 && ButtonY == 0)
			{
				SetMenu(1);
			}
			break;		
	}
	
}

void SetMenu(char MenuNumber)
{
	unsigned char counter = 0;
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
			x = 0;
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
	}
	setButton(x,y);
}
char ButtonMax(char xy, char set)
{
	static char Max = 0;
	char counter = 0;
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

void setButton(char ButtonX, char ButtonY)
{
	unsigned char counter = 0;
	
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
	unsigned char counter = 0;
	
	for(counter = 0; counter != menu[ACTIVE_MENU].buttonAmount; counter++)
	{
			drawButton(counter,0);
			drawText(counter,0);
	}
	
}

void drawButton(char ButtonNumber,char selected)
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
void drawText(char TextNumber, char selected)
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
	unsigned char counterX = 0,counterY = 0;
		
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
	unsigned char counterX = 0,counterY = 0;
		
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
	stringxy("Press a box button if ready",10,60,colors.white,BACKGROUND,0);
}
void show_INFO(void)
{
	stringxy("BMA 2020",10,100,colors.black,BACKGROUND,0);
	stringxy("Lionardo Wernli",10,86,colors.black,BACKGROUND,0);
	stringxy("Marco Stauber",10,72,colors.black,BACKGROUND,0);
	stringxy("Bel17a",10,58,colors.black,BACKGROUND,0);
}
