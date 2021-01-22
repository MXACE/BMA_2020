#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"
#include "ssd1351.h"
#include "gfx.h"

extern Colors colors;

void Button_manager(char pressedButton);
char ButtonMax(char xy, char set);

void SetMenu(char MenuNumber);

void drawTestMenu(void);
void drawButton(char ButtonNumber,char selected);
void drawText(char TextNumber, char selected);

void show_QRCODE(void);
void show_LOGO(void);

#endif
