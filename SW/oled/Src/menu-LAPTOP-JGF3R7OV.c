#include "main.h"
#include "ssd1351.h"
#include "gfx.h"
#include "menu.h"
#include "menu_windows.h"

#define BACKGROUND colors.blue
extern Colors colors;
	
uint8_t ACTIVE_MENU = 0;

void Button_manager(char pressedButton)
{
	static unsigned char x = 0;
	static unsigned char y = 0;
	switch(pressedButton)
	{
		case 1:
			if(y > 0)
			{
				y -= 1;
			}
			else
			{
				y = ButtonMax(1,0);
			}
			break;
		case 2:
			if(x > 0)
			{
				x -= 1;
			}
			else
			{
				x = ButtonMax(0,0);
			}
			break;
		case 3:
			if(x >= ButtonMax(0,0))
			{
				x = 0;
			}
			else
			{
				x += 1;
			}
			break;
		case 4:
			if(y >= ButtonMax(1,0))
			{
				y = 0;
			}
			else
			{
				y += 1;
			}
			break;
		case 5:
			break;
		default:
			break;
	}
}

void SetMenu(char MenuNumber)
{
	unsigned char counter = 0;
	
	blankscreen(BACKGROUND);
	switch(MenuNumber)
	{
		case 1:
			drawTestMenu();
			break;
		case 2:
			show_LOGO();
			break;
		case 3:
			show_QRCODE();
			break;
	}
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
	}
	return Max;
}

void drawTestMenu(void)
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
		colors.black,colors.gray,0);
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
