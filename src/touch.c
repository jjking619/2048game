#include "touch.h"
#include "bmp.h"
#include "lcd.h"
#include "slide.h"
int touch_fd;//触摸屏文件
slideInfo info;
int mode_flag=0;//记录info.mode的值
int state_flag=0;   //  记录状态 0表示继续,1表示暂停 2表示返回
void touch_init(void)
{
  touch_fd = open("/dev/input/event0", O_RDWR);
  if (touch_fd == -1)
  {
    perror("tounch failed");
    return ;
  }
  return;
}

void touch_close(void)
{
  close(touch_fd);
  return;
}

//点击换页面
int touch_click(int x_read,int y_read)
{
struct input_event ev;
while (1)
{
  read(touch_fd, &ev, sizeof(ev)); // 一直等在这里直到点击屏幕
  if (ev.type == EV_KEY && ev.code == BTN_TOUCH)
  {
    if (ev.value == 1)
    {
      printf("press!!\n");
    }
    else if (ev.value == 0)
    {
      printf("songkai!!\n");
    }
  }
  else if (ev.type == EV_ABS)
  {
    if (ev.code == ABS_X)
    {
      x_read = ev.value * 800 / 1024;
    }
    else if (ev.code == ABS_Y)
    {
      y_read = ev.value * 480 / 600;
    }
  }
  if (x_read >= 0 && y_read >= 0)
  {
    printf("(%d,%d)\n", x_read, y_read);
    break;
  }
      
}
   return x_read  ;
}


//滑动翻页算法
int x0_read;
int y0_read;
int x1_read;
int y1_read;
void touch_slide()
{
  x0_read = -1;
  y0_read = -1;
  x1_read = -1;
  y1_read = -1;
  struct input_event ev;
  while (1)
  {
 
    read(touch_fd, &ev, sizeof(ev)); // 一直等在这里直到点击屏幕

    if (ev.type == EV_ABS)
    {
      if (ev.code == ABS_X)
      {
        if (x0_read == -1)
        {
          x0_read = ev.value * 800/ 1024;
        }
        else
        {
          x1_read = ev.value * 800 / 1024;
        }
      }
      else if (ev.code == ABS_Y)
      {
        if (y0_read == -1)
        {
          y0_read = ev.value * 480 / 600;
        }
        else
        {
          y1_read = ev.value * 480 / 600;
        }
      }
    }

    if (ev.type == EV_KEY && ev.code == BTN_TOUCH) // 退出条件
    {
      if (ev.value == 0 && x1_read >= 0 && y1_read >= 0) // 手指松开
      {
        printf("(%d,%d)------>(%d,%d)\n", x0_read, y0_read, x1_read, y1_read);
        break;
      }
    }
  }
    //判断模式
    if (!mode_flag) 
    {
      info.mode = judge_mode();
      mode_flag = 1;
    }
    //判断是否重新开始
    if (x1_read >= 500 && y1_read >= 260 &&y1_read<=320)
    {
      game_restart();
    }
     // 记录状态  //0表示继续,1表示暂停 2表示返回
    // 判断游戏继续还是暂停
    if (x1_read >= 500 && y1_read >= 420)
    {
      state_flag = 1;
      game_stop();
    }
    else if (x1_read >= 500 && y1_read>=340 &&y1_read < 420)
    {
      game_continue();
    }
    else if (x1_read >= 500 && y1_read >= 0 && y1_read <= 60)
    {
        state_flag = 2;
        back();
        // state_flag = 0;
    }
    info.dx = x1_read - x0_read;
    info.dy = y1_read - y0_read;
    //判断方向
    if (abs(info.dx) > abs(info.dy))
    {
      if (info.dx > 0)
      {
        info.dir = 2; // 向右
      }
      else
      {
        info.dir = 1; // 向左
      }
    }
    else
    {
      if (info.dy > 0)
      {
        info.dir = 4; // 向下
      }
      else
      {
        info.dir = 3; // 向上
      }
    }
}
/*如果返回值为1进入简单模式,滑到32即可胜利,如果为2,进入中等模式,滑到64即可胜利,
   如果为3进入简单模式,滑到2048即可胜利*/
int judge_mode()
{
     if(y1_read>=215&&y1_read<=314)
     {
       return 32;
     }
     else if (y1_read >= 315 && y1_read <= 414)
     {
       return 64;
     }
     else if (y1_read >= 415 && y1_read <= 480)
     {
       return 2048;
     }
     else{
       return 32;
     }
}