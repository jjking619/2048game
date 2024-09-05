#ifndef __MENU_H__
#define __MENU_H__
#include <time.h>
#include <stdlib.h>
#include "touch.h"
#include "bmp.h"
#include "word.h"
#include "slide.h"
#include "lcd.h"
extern int map[4][4];
extern int score; // 得分
void rand_pos();
void menu_right();
void over();
void load_map(int map[][4]);
void game_stop(); //暂停
void game_continue();//继续
void game_restart();//重新开始
void back();  //返回初始界面
void map_init();
void top_grade(); //求最高分
void count_down(); //倒计时
void success(); // 游戏胜利界面
int clern_Lcd(int x0, int y0, int w, int h, int color); //清屏
#endif