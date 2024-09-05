#include "lcd.h"
#include "bmp.h"
#include "word.h"
int lcd_fd;

void lcd_init(void)
{
    lcd_fd= open("/dev/fb0",O_RDWR);
    if(lcd_fd == -1)
    {
        perror("open lcd failed");
        return ;
    }

    plcd = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_SHARED,lcd_fd,0); 
    return ;
}

//初始化地图 800*480
void Lcd_Draw_Map(int x0, int y0, unsigned int color)
{
    for ( x0 = 0; x0 < 800; x0++)
    {
    for ( y0 = 0; y0 < 480; y0++)
    {
       *(plcd + y0 * 800 + x0) = color;
    }
    }
    // 开始
    show_word(386, 220, 32, 39, ka, 0x4DFFFF);
    show_word(422, 220, 32, 39, shi, 0x4DFFFF);
}

void Lcd_Draw_Point(int x0, int y0, unsigned int color)
{
    if (x0 >= 0 && x0 < 800 && y0 >= 0 && y0 < 480)
    {
        *(plcd + y0 * 800 + x0) = color;
    }
}




void lcd_close(void)
{ 
    munmap(plcd,800*480*4); 
    close(lcd_fd);
}

