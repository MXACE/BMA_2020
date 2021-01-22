#include "main.h"

/*
char OUTTMG = 1; //Out-timing
char EXTGCK = 0; //Ext. Clock
char TMGRST = 1; //Timing reset
char DSPRPT = 1; //Display repeat
char BLANK = 0; //Blank (clear leds)
*/
#define OUTTMG 1 //Out-timing
#define EXTGCK 0 //Ext. Clock
#define TMGRST 1 //Timing reset
#define DSPRPT 1 //Display repeat
#define BLANK 0 //Blank (clear leds)

void LEDC_CLKPuls(void);

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


void RGB_setLED(char pos, int r, int g, int b)
{
//	int counter = 0;
	if (pos > 7) pos = 7;

	for (int i = 16; i != 0; i--)
	{
		switch (pos)
		{

		case 5:
			if(r & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 223 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 223 - (i - 1)] = 0;

			if(g & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 207 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 207 - (i - 1)] = 0;

			if(b & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 191 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 191 - (i - 1)] = 0;
			break;

		case 6:
			if(r & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 175 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 175 - (i - 1)] = 0;

			if(g & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 159 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 159 - (i - 1)] = 0;

			if(b & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 143 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 143 - (i - 1)] = 0;
			break;


			/*RGB_DATA[224 * 0 + 175 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 159 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 143 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 7:
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 127 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 127 - (i - 1)] = 0;

			if (g & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 111 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 111 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 95 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 95 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 0 + 127 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 111 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 95 - (i - 1)]  = (b & 0x01 << i - 1);
			break;*/
		case 8:
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 79 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 79 - (i - 1)] = 0;

			if (g & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 63 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 63 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * 0 + 47 - (i - 1)] = 1;
			else RGB_DATA[224 * 0 + 47 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 0 + 79 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 63 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 0 + 47 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 1:
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 223 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 223 - (i - 1)] = 0;

			if (g & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 207 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 207 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 191 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 191 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 223 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 207 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 191 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 2:
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 175 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 175 - (i - 1)] = 0;

			if (g & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 159 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 159 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 143 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 143 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 175 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 159 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 143 - (i - 1)] = (b & 0x01 << i - 1);
			break;*/
		case 3:
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 127 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 127 - (i - 1)] = 0;

			if (g & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 111 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 111 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 95 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 95 - (i - 1)] = 0;
			break;

			/*RGB_DATA[224 * 1 + 127 - (i - 1)] = (r & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 111 - (i - 1)] = (g & 0x01 << i - 1);
			RGB_DATA[224 * 1 + 95 - (i - 1)]  = (b & 0x01 << i - 1);
			break;*/
		case 4:
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 79 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 79 - (i - 1)] = 0;

			if (g & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 63 - (i - 1)] = 1;
			else RGB_DATA[224 * 1 + 63 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * 1 + 47 - (i - 1)] = 1;
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
			if (r & 0x01 << (i - 1)) RGB_DATA[224 * pos + 31 - (i - 1)] = 1;
			else RGB_DATA[224 * pos + 31 - (i - 1)] = 0;
			
			if (g & 0x01 << (i - 1)) RGB_DATA[224 * pos + 24 - (i - 1)] = 1;
			else RGB_DATA[224 * pos + 24 - (i - 1)] = 0;

			if (b & 0x01 << (i - 1)) RGB_DATA[224 * pos + 17 - (i - 1)] = 1;
			else RGB_DATA[224 * pos + 17 - (i - 1)] = 0;

		}
	}
}

void RGB_Setup(void)
{
	RGB_setBC(20, 20, 20);
}

void RGB_SHOW(void)
{
	int i = 0;
	for(i = 0; i != 448; i++)
	{
		HAL_GPIO_WritePin(RGB_DATA_GPIO_Port, RGB_DATA_Pin, RGB_DATA[i]);
		LEDC_CLKPuls();
	}
}

void LEDC_CLKPuls(void)
{
	int i = 0;
		//HAL_Delay(1);
		for(i = 0; i!= 100; i++)
		{
			__NOP();
		}
    HAL_GPIO_WritePin(RGB_PWM_GPIO_Port, RGB_PWM_Pin, GPIO_PIN_SET);
		for(i = 0; i!= 100; i++)
		{
			__NOP();
		}
    //HAL_Delay(1);
    HAL_GPIO_WritePin(RGB_PWM_GPIO_Port, RGB_PWM_Pin, GPIO_PIN_RESET);
}

void magnet(char state)
{
	if(state)	HAL_GPIO_WritePin(MAGNET_GPIO_Port,MAGNET_Pin,GPIO_PIN_SET);
	else HAL_GPIO_WritePin(MAGNET_GPIO_Port,MAGNET_Pin,GPIO_PIN_RESET);
}
