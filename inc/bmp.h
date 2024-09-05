#ifndef __BMP_H__
#define __BMP_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>

void Draw_point(int x0,int y0,unsigned int color); //描点函数
int Display_bmp(char *bmpname,int x0,int y0); //显示图片
extern int *plcd;//外部声明
extern int bmp_fd; // 图片描述符外部声明
#endif 
