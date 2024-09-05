#include "slide.h"
#include "touch.h"
#include "bmp.h"
#include "menu.h"
int sum; //得分
int max_score;//最大得分

int map[4][4];
int judge_down()
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
    {
      if (map[i][j] == map[i+1][j] && map[i+1][j] > 0)
        return 1;
      if (map[i][j] != map[i+1][j] && map[i+1][j] == 0)
        return 1;
    }
  return 0;
}
int judge_up()
{
  int i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
    {
      if (map[i][j] == map[i+1][j] && map[i][j] > 0)
        return 1;
      if (map[i][j] != map[i+1][j] && map[i][j] == 0)
        return 1;
    }
  return 0;
}
int judge_left()
{
  int i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 3; j++)
    {
      if (map[i][j] == map[i][j + 1] && map[i][j] > 0)
        return 1;
      if (map[i][j] != map[i][j + 1] && map[i][j] == 0)
        return 1;
    }
  return 0;
}
int judge_right()
{
  int i, j;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 3; j++)
    {
      if (map[i][j] == map[i][j + 1] && map[i][j+1] > 0)
        return 1;
      if (map[i][j] != map[i][j + 1] && map[i][j+1] == 0)
        return 1;
    }
  return 0;
}
//返回1就是能动,返回2说明有2048,返回3就是四个不能移动,返回4是某个方向不能移动
int judge_move()
{
  // 遍历数组，比较是否有2048---有就直接返回2
  int i, j;
  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){
      if(map[i][j] == info.mode)
      {
        printf("%d\n", info.mode);
        return 2;
      }
    }
  }
  // 判断四个方向能不能移动
  int ret = 0;
  switch (info.dir)
  {
  case  1:
    ret += judge_left();
  case  2:
    ret += judge_right();
  case  3:
    ret += judge_up();
  case  4:
    ret += judge_down();
    break;
  default:
    printf("input error\n");
    break;
  }
  if(ret==0)
  {
    return 3;
  }
  // 判断单个方向能不能移动
  ret = 0;
  switch (info.dir)
  {
  case 1:
    ret += judge_left();
  case 2:
    ret += judge_right();
  case 3:
    ret += judge_up();
  case 4:
    ret += judge_down();
    break;
  default:
    printf("input error\n");
    break;
  }
  if(ret)
    return 1;
  else
    return 4;
}
// 左滑 
void left()
{
  int i, j, k;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 3; j++)
      if (map[i][j] != 0)
      {
        for (k = j + 1; k < 4; k++)
        {
          if( map[i][j] != map[i][k] && map[i][j] != 0)
               break;
          else if (map[i][j] == map[i][k])
          {
            map[i][j] *= 2;
            map[i][k] = 0;
            sum += map[i][k];
            break;
          }
        }
      }

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (map[i][j] == 0)
      {
        for (k = j + 1; k < 4; k++)
        {
          if (map[i][k] != 0)
          {
            map[i][j] = map[i][k];
            map[i][k] = 0;
            break;
          }
        }
      }
}
// 右滑
void right()
{
 int i, j, k;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 3; j++)
      if (map[i][j] != 0)
      {
        for (k = j + 1; k < 4; k++)
        {
          if( map[i][j] != map[i][k] && map[i][k] != 0)
            break;
          else if (map[i][j] == map[i][k])
          {
            map[i][k] *= 2;
            sum += map[i][k];
            map[i][j] = 0;
            break;
          }
        }
      }

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (map[i][j] != 0)
      {
        for (k = j + 1; k < 4; k++)
        {
          if (map[i][k] == 0)
          {
            map[i][k] = map[i][j];
            map[i][j] = 0;
            break;
          }
        }
      }
}
// 上滑
void up()
{
  int i, j, k;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
      if (map[i][j] != 0)
      {
        for (k = i + 1; k < 4; k++)
        {
          if (map[i][j] != map[k][j] && map[k][j] != 0)
            break;
          else if (map[i][j] == map[k][j])
          {
            map[i][j] *=2;
            sum += map[i][j];
            map[k][j] = 0;
            break;
          }
        }
      }

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (map[i][j] == 0)
      {
        for (k = i + 1; k < 4; k++)
        {
          if (map[k][j] != 0)
          {
            map[i][j] = map[k][j];
            map[k][j] = 0;
            break;
          }
        }
      }
}
// 下滑
void down()
{
  int i, j, k;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 4; j++)
      if (map[i][j] != 0)
      {
        for (k = i + 1; k < 4; k++)
        {
          if (map[i][j] != map[k][j] && map[i][j] != 0)
            break;
          else if (map[i][j] == map[k][j])
          {
            map[k][j] *= 2;
            sum += map[k][j];
            map[i][j] = 0;
            break;
          }
        }
      }

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (map[i][j] != 0)
      {
        for (k = i + 1; k < 4; k++)
        {
          if (map[k][j] == 0)
          {
            map[k][j] = map[i][j];
            map[i][j] = 0;
            break;
          }
        }
      }
}
void move()
{
  switch (info.dir)
  {
  case 1:
      left();
      break;
  case 2:
      right();
      break;
  case 3:
      up();
      break;
  case 4:
      down();
      break;
  default:
    printf("input error\n");
    break;
  }
  // refresh_num(map);
}

//求最大得分
int print_max()
{
  int i, j,max_score=map[0][0];
  for (i = 0; i <4; i++)
  {
      for (j = 0; j <4; j++)
      {
          if(map[i][j]>max_score)
          {
             max_score=map[i][j];     
          }
          // printf("%d", map[i][j]);
      }
  }
  return max_score;
}