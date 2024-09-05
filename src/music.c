#include "music.h"
char *mp3name[2] = {"merge.mp3", "start.mp3"};
char cmd[100] = {0};

void *music_start()
{
    sprintf(cmd, "madplay ./%s &", mp3name[0]);
    // system(cmd);
}
void music_move()
{
   sprintf(cmd, "madplay ./%s &", mp3name[1]);
  //  system(cmd);
}

void stop()
{
  system("killall -STOP madplay &"); // 暂停播放
}

void recover()
{
  system("killall -CONT madplay &"); // 恢复播放
}