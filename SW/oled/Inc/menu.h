#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"
#include "ssd1351.h"
#include "gfx.h"

extern Colors colors;

void Button_manager(char pressedButton);
char ButtonMax(char xy, char set);

void setButton(char ButtonX, char ButtonY);
void SetMenu(char MenuNumber);
void MenuGoto(char ButtonX, char ButtonY);

void drawMenu(void);
void drawButton(char ButtonNumber,char selected);
void drawText(char TextNumber, char selected);

void show_QRCODE(void);
void show_LOGO(void);
void show_Mix(void);
void show_INFO(void);
#endif
