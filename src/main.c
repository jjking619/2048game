#include <pthread.h>
#include <stdio.h>
#include "bmp.h"
#include "lcd.h"
#include "touch.h"
#include "word.h"
#include "menu.h"
#include "slide.h"
#include "music.h"
int map[4][4];
int main()
{
    lcd_init();//初始化屏幕
    touch_init(); // 初始化触摸屏
    // pthread_t id1;
    // pthread_create(&id1, NULL, music_start, NULL); //开始页面
    map_init();
    rand_pos();
    rand_pos();
    int flag = 0;
    while (1)
    {
        touch_slide();
        if (state_flag==2)
        {
            continue;
        }
        flag = judge_move();
        if (flag == 1)
        {
            move();
            // music_move();
            rand_pos();
            load_map(map);
            menu_right();   
            flag = judge_move();// 移动之后还要判断游戏是否结束
            if (flag == 2)
            {
                printf("success\n");
                success();  //成功界面
                // break;
            }
            else if (flag == 3)
            {
                printf("defeat\n");
                over();  //游戏结束
                continue;
            }
        }
        else if (flag == 2)
        {
            printf("success  2048\n"); // 请你刷新一张胜利的图片
            success();                 // 成功界面
            continue;
        }
        else if (flag == 3)
        {
            printf("defeat  2048\n");
            over();  //游戏结束
            continue;
        }
        else if (flag == 4)
        {
            printf("No through road\n");
            continue;
        }
    }
    lcd_close(); // 关闭屏幕
    touch_close(); // 关闭触摸屏
    return 0;
}

