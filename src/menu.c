#include "menu.h"
int num;        // 随机数
int sum;        //得分
int top_score;  // 最高分
char *bname[9]={"619.bmp","6190.bmp","background.bmp","gameOver.bmp","restart.bmp","victory.bmp",
"score.bmp","logo.bmp","back.bmp"};
int state_flag;
int map[4][4];
// 初始化游戏界面2048小游戏,模式选择,简单,中等,困难
void map_init()
{
  Display_bmp(bname[7], 0, 0);  //logo.bmp
  show_number(368, 38, 2048);
  int x0 = 392, y0 = 38, i;
  for (i = 0; i < 3; i++)
  {
    show_word(x0, y0, 32, 39, game_menu[i], 0x00FF00);
    x0 += 35;
  }
  x0 = 336, y0 = 125;
  for (i = 0; i < 4; i++)
  {
    show_word(x0, y0, 32, 39, mode[i], 0x00FF00);
    x0 += 35;
  }
  x0 = 368, y0 = 215;
  for (i = 0; i < 2; i++)
  {
    show_word(x0, y0, 32, 39, easy[i], 0x00FF00);
    x0 += 35;
  }
  x0 = 368, y0 = 315;
  for (i = 0; i < 2; i++)
  {
    show_word(x0, y0, 32, 39, middle[i], 0x00FF00);
    x0 += 35;
  }
  x0 = 368, y0 = 415;
  for (i = 0; i < 2; i++)
  {
    show_word(x0, y0, 32, 39, hard[i], 0x00FF00);
    x0 += 35;
  }
  // touch_slide();
}

// 产生一个随机位置
void rand_pos(){ 
  srand(time(0));
  int num = rand() % 2;
  if (num == 0)
  {
    num = 2;
  }
  else
  {
    num = 4;
  }
  int i, j;
  while (1)
  {
    i = rand() % 4;
    j = rand() % 4;
    if (map[i][j] == 0) // 找到了一个随机的空白的地方
    {
      map[i][j] = num;
      break;
    }
    else{
        continue;;
    }
  }
}

// 根据数组里面的数字去指定的位置上刷新图片
void load_map(int map[][4])
{
  int x0,y0,i,j;
  char name[1024] = {0};             
  // 画边框
  Display_bmp(bname[2], 0, 0);
  // 更新图片
  for (i = 0, y0 = 0; y0 <= 480&&i < 4; y0 += 120, i++)
  {
    for (j=0,x0 = 0; x0<=600&&j<4; x0 += 120,j++)
    {
      if (map[i][j]==0)
      {
        continue;
      } 
      sprintf(name, "./%d.bmp", map[i][j]); // 此时name这个数字里面的内容就变成了"./64.bmp"
      Display_bmp(name,x0,y0);                // 起始位置跟数组的下标有关系
    }
    
  }
}


void game_stop()
{
  // state_flag = 1;
  if (state_flag)
  {
    while (1)
    {
      sleep(1);
      touch_slide();
      if (state_flag == 0)
      {
        break;
      }
    }
    }
}

// 重新开始
void game_restart()
{
  int i, j;
  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 4; j++)
    {
      map[i][j] = 0;
    }
    }
    sum = 0;
    rand_pos();
    rand_pos();
    load_map(map);
    menu_right();
}

//求最高分
void top_grade(){
   top_score = sum;
}

//返回
void back(){  
     map_init();
     mode_flag = 0;
     touch_slide();
     state_flag = 0;
}

// 游戏继续
void game_continue()
{  
    state_flag = 0;
}

// 右边状态栏,包括姓名,得分,当前状态,暂停,开始
void menu_right()
{
  Display_bmp(bname[1],480,0);  //背景图
  Display_bmp(bname[8], 480, 0); //返回
  Display_bmp(bname[6],480, 60); //得分  480x196
  // 姓名
  // show_word(542, 14, 32, 39, xing, 0x00FF00);
  // show_word(575, 14, 32, 39, min, 0x00FF00);
  // show_word(608, 14, 32, 39, maohao, 0x00FF00);
  // show_word(641, 14, 32, 39, ji, 0x00FF00);
  // show_word(674, 14, 32, 39, kai, 0x00FF00);
  // show_word(707, 14, 32, 39, an, 0x00FF00);
  
  show_number(680, 82, top_score);
  show_number(680, 137, sum);
  show_number(680, 194, print_max());
  Display_bmp(bname[4], 480, 250);  //重新开始
  show_word(620, 340, 32, 39, ka, 0x00FFFF);
  show_word(654, 340, 32, 39, shi, 0x00FFFF);
  // 暂停
  show_word(620, 420, 32, 39, zan, 0x00FFFF);
  show_word(652, 420, 32, 39, ting, 0x00FFFF);
}

// 打印游戏over
void over()
{
  Display_bmp(bname[0], 0, 0);
  Display_bmp(bname[3], 300, 190);
  count_down();
}


//游戏胜利界面
void success()
{
  Display_bmp(bname[0], 0, 0);
  Display_bmp(bname[5], 300, 190);
  count_down();
}


// 倒计时
void count_down()
{
  int i;
  for (i = 3; i >= 0; i--)
  {
    // 显示数字
    show_number(400, 240, i);
    sleep(1);
    // 清除上一次的数据（覆盖矩形）
    clern_Lcd(400,240,24, 39, 0xFFFFFF);
  }
  top_grade(); //保留最高分
  game_restart();
}

int clern_Lcd(int x0, int y0, int w, int h, int color)
{
  int x, y;
  for (x = x0; x < x0 + w; x++)
  {
    for (y = y0; y < y0 + h; y++)
    {
      Lcd_Draw_Point(x, y, color); // 假设这个函数负责在LCD上绘制一个点
    }
  }
  return 1;
}


