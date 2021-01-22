#ifndef _MENU_H_
#define _MENU_H_

#include "main.h"
#include "ssd1351.h"
#include "gfx.h"

extern Colors colors;

void Button_manager(uint8_t pressedButton);
char ButtonMax(uint8_t xy, uint8_t set);

char Menu_Flags(uint8_t pos, uint8_t set);

void setButton(uint8_t ButtonX, uint8_t ButtonY);
void SetMenu(uint8_t MenuNumber);
void MenuGoto(uint8_t ButtonX, uint8_t ButtonY);

void drawMenu(void);
void drawButton(uint8_t ButtonNumber,uint8_t selected);
void drawText(uint8_t TextNumber, uint8_t selected);

void show_QRCODE(void);
void show_LOGO(void);
void show_Mix(void);
void show_INFO(void);
void show_Mix(void);
void show_Ready(void);
#endif
