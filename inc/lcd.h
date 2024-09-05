#ifndef __LCD_H__
#define __LCD_H__
#include "word.h"
void lcd_init(void);
void lcd_close(void);
void Lcd_Draw_Point(int x0, int y0, unsigned int color);
void Lcd_Draw_Map(int x0, int y0, unsigned int color);
#endif 
