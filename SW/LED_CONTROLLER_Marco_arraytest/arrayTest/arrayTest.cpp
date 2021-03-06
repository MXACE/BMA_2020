// arrayTest.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//
#include "stdafx.h"
#include <iostream>
#include "conio.h"

void RGB_Setup(void);
void RGB_setBC(uint8_t r, uint8_t g, uint8_t b);
void RGB_setLED(char pos, int r, int g, int b);
void showRGBDATA();

using namespace std;

char OUTTMG = 1; //Out-timing
char EXTGCK = 0; //Ext. Clock
char TMGRST = 1; //Timing reset
char DSPRPT = 1; //Display repeat
char BLANK = 0; //Blank (clear leds)

unsigned char RGB_DATA[224 * 2] =

// 0------------------------------------------------------
{	 1,0,0,1,0,1,		//write cmd 0-5

	OUTTMG,EXTGCK,TMGRST,DSPRPT,BLANK,	//function 6-10

	0,0,0,0,0,0,0,	//BC Blue 11-17
	0,0,0,0,0,0,0,	//BC Green 18-24
	0,0,0,0,0,0,0,	//BC RED 25-31

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 3 32-47
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 3 48-63
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 3	64-79

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 2	80-95
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 2 96-111
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 2 112-127

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 1 128-143
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 1 144-159
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 1 160-175

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 0 176-191
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 0 192-207
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 0 208-223

									//1-----------------------------------------------------
	1,0,0,1,0,1,		//write cmd 0-5

	OUTTMG,EXTGCK,TMGRST,DSPRPT,BLANK,	//function 6-10

	0,0,0,0,0,0,0,	//BC Blue 11-17
	0,0,0,0,0,0,0,	//BC Green 18-24
	0,0,0,0,0,0,0,	//BC RED 25-31

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 3 32-47
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 3 48-63
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 3	64-79

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 2	80-95
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 2 96-111
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 2 112-127

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 1 128-143
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 1 144-159
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Red 1 160-175

	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Blue 0 176-191
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//GS Green 0 192-207
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	//GS Red 0 208-223

unsigned char ENDpos[17] = {5,10,17,24,31,47,63,79,95,111,127,143,159,175,191,207,223};
char partText[18][20] =
{ "Write CMD\n",
	"Function CMD\n",
	"BC Blue\n",
	"BC Green\n",
	"BC Red\n",
	"GS Blue 3\n",
	"GS Green 3\n",
	"GS Red 3\n",
	"GS Blue 2\n",
	"GS Green 2\n",
	"GS Red 2\n",
	"GS Blue 1\n",
	"GS Green 1\n",
	"GS Red 1\n",
	"GS Blue 0\n",
	"GS Green 0\n",
	"GS Red 0\n",
	"LED: "
};

int main()
{
	/*
	int r = 255;
	for (int i = 16; i != 0; i--)
	{
		//if (r & (0x01 << i - 1)) printf("1");
		//else printf("0");
		if (r & 0x01 << i - 1) RGB_DATA[224 * 0 + 223 - (i - 1)] = 1;
		else RGB_DATA[224 * 0 + 223 - (i - 1)] = 0;
		//RGB_DATA[224 * 0 + 223 - (i - 1)] = (r & 0x01 << i - 1);
	}/*
	_getch();
	for (int i = 0; i != 448; i++)
	{
		RGB_DATA[i] = i;

	}*/
	RGB_Setup();
	//RGB_setBC(16,16,16);
	/*RGB_setLED(0, 255, 255, 255);
	RGB_setLED(1, 255, 255, 255);
	RGB_setLED(2, 255, 255, 255);
	RGB_setLED(3, 255, 255, 255);
	RGB_setLED(4, 65535, 65535, 65535);
	RGB_setLED(5, 65535, 65535, 65535);
	RGB_setLED(6, 65535, 65535, 65535);
	RGB_setLED(7, 65535, 65535, 65535);*/
	showRGBDATA();
}

void showRGBDATA()
{
	int Arraypos = 0;
	int Textpos = 0;
	int LEDpos = 0;
	int endLED = 2;

	for (LEDpos = 0; LEDpos != endLED; LEDpos++)
	{
		cout << partText[17] << LEDpos << '\n';

		for (Textpos = 0; Textpos != 17; Textpos++)
		{
			cout << partText[Textpos];

			for (Arraypos; Arraypos != 224 * LEDpos + (ENDpos[Textpos] + 1); Arraypos++)
			{
				//if(RGB_DATA[Arraypos])	cout << '1' << ' ';
				printf("%i ", RGB_DATA[Arraypos]);
				//else cout << '0' << ' ';
			}
			cout << "\n\n";
		}

		cout << "--------------------------------------------\n";
	}
	_getch();
}

void RGB_setLED(char pos, int r, int g, int b)
{
	int counter = 0;
	if (pos > 7) pos = 7;

	for (int i = 16; i != 0; i--)
	{
		switch (pos)
		{

		case 0:
			if(r & 0x01 << i - 1) RGB_DATA[224 * 0 + 223 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 223 - (i - 1)] = 0;

			if(g & 0x01 << i - 1) RGB_DATA[224 * 0 + 207 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 207 - (i - 1)] = 0;

			if(b & 0x01 << i - 1) RGB_DATA[224 * 0 + 191 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 191 - (i - 1)] = 0;
			break;

		case 1:
			if(r & 0x01 << i - 1) RGB_DATA[224 * 0 + 175 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 175 - (i - 1)] = 0;

			if(g & 0x01 << i - 1) RGB_DATA[224 * 0 + 159 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 159 - (i - 1)] = 0;

			if(b & 0x01 << i - 1) RGB_DATA[224 * 0 + 143 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 143 - (i - 1)] = 0;
			break;


			/*RGB_DATA[224 * 0 + 175 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 159 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 143 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 2:
			if (r & 0x01 << i - 1) RGB_DATA[224 * 0 + 127 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 127 - (i - 1)] = 0;

			if (g & 0x01 << i - 1) RGB_DATA[224 * 0 + 111 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 111 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * 0 + 95 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 95 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 0 + 127 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 111 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 95 - (i - 1)]  = (b & 0x01 << i - 1);
			break;*/
		case 3:
			if (r & 0x01 << i - 1) RGB_DATA[224 * 0 + 79 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 79 - (i - 1)] = 0;

			if (g & 0x01 << i - 1) RGB_DATA[224 * 0 + 63 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 63 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * 0 + 47 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 47 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 0 + 79 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 63 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 47 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 4:
			if (r & 0x01 << i - 1) RGB_DATA[224 * 1 + 223 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 223 - (i - 1)] = 0;

			if (g & 0x01 << i - 1) RGB_DATA[224 * 1 + 207 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 207 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * 1 + 191 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 191 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 223 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 207 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 191 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 5:
			if (r & 0x01 << i - 1) RGB_DATA[224 * 1 + 175 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 175 - (i - 1)] = 0;

			if (g & 0x01 << i - 1) RGB_DATA[224 * 1 + 159 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 159 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * 1 + 143 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 143 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 175 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 159 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 143 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 6:
			if (r & 0x01 << i - 1) RGB_DATA[224 * 1 + 127 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 127 - (i - 1)] = 0;

			if (g & 0x01 << i - 1) RGB_DATA[224 * 1 + 111 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 111 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * 1 + 95 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 95 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 127 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 111 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 95 - (i - 1)]  = (b & 0x01 << i - 1);*/
			break;
		case 7:
			if (r & 0x01 << i - 1) RGB_DATA[224 * 1 + 79 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 79 - (i - 1)] = 0;

			if (g & 0x01 << i - 1) RGB_DATA[224 * 1 + 63 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 63 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * 1 + 47 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 47 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 79 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 63 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 47 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/

		}
	}
}

void RGB_setBC(uint8_t r, uint8_t g, uint8_t b)
{
	char pos = 0;
	if (r > 127) r = 127;
	if (g > 127) g = 127;
	if (b > 127) b = 127;

	for (pos = 0; pos != 2; pos++)
	{
		/*for (counter = 0; counter != 7; counter++)
		{
			RGB_DATA[224 * pos + 17 - (i - 1)] = r & (0x01 >> counter);
			RGB_DATA[224 * pos + 24 - (i - 1)] = g & (0x01 >> counter);
			RGB_DATA[224 * pos + 31 - (i - 1)] = b & (0x01 >> counter);
		}*/
		for (int i = 7; i != 0; i--)
		{
			if (r & 0x01 << i - 1) RGB_DATA[224 * pos + 31 - (i - 1)] = 1;
			else RGB_DATA[224 * pos + 31 - (i - 1)] = 0;
			
			if (g & 0x01 << i - 1) RGB_DATA[224 * pos + 24 - (i - 1)] = 1;
			else RGB_DATA[224 * pos + 24 - (i - 1)] = 0;

			if (b & 0x01 << i - 1) RGB_DATA[224 * pos + 17 - (i - 1)] = 1;
			else RGB_DATA[224 * pos + 17 - (i - 1)] = 0;

		}
	}

	
}

void RGB_Setup(void)
{
	RGB_setBC(128, 128, 128);
}