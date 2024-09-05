#ifndef __WORD_H__
#define __WORD_H__
#include "bmp.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "menu.h"
void show_word(int x0, int y0, int w, int h, unsigned char word[][w / 8], int color);
void show_number(int x0, int y0, int num);
extern unsigned char ji[39][32/ 8];
extern unsigned char kai[39][32 / 8];
extern unsigned char an[39][32 / 8];
extern unsigned char xing[39][32 / 8];
extern unsigned char min[39][32 / 8];
extern unsigned char de[39][32 / 8];
extern unsigned char fen[39][32 / 8];
extern unsigned char zan[39][32 / 8];
extern unsigned char ting[39][32 / 8];
extern unsigned char zhuang[39][32 / 8];
extern unsigned char tai[39][32 / 8];
extern unsigned char maohao[39][32 / 8];
extern unsigned char ka[39][32 / 8];
extern unsigned char shi[39][32 / 8];
extern unsigned char wei[39][32 / 8];
extern unsigned char suc[5][39][32 / 8];
extern unsigned char game_menu[3][39][32 / 8]; // 小游戏
extern unsigned char numbers[10][39][24 / 8];
extern unsigned char mode[4][39][32 / 8];
extern unsigned char easy[2][39][32 / 8];
extern unsigned char middle[2][39][32 / 8];
extern unsigned char hard[2][39][32 / 8];
#endif 