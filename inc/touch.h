#ifndef __TOUCH_H__
#define __TOUCH_H__
#include <linux/input.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
typedef struct
{
  int dx;  // X轴方向上的滑动距离
  int dy;  // Y轴方向上的滑动距离
  int dir; // 滑动方向，例如：上、下、左、右
  int mode; //游戏模式值
  
} slideInfo;
extern slideInfo info;
extern int state_flag;
extern int mode_flag;
void touch_init(void);
void touch_close(void);
int touch_click(int x_read, int y_read);
void touch_slide();
int judge_mode();  //判断游戏模式
int display_Rectangle(int x0, int y0, int w, int h, int color);
#endif