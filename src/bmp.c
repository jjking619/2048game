#include "bmp.h"

int *plcd;
int bmp_fd;
void Draw_point(int x0, int y0, unsigned int color)
{
    if(x0>=0&&x0<800&&y0>=0&&y0<480)
    {
        *(plcd+y0*800+x0) = color;
    }
}

int Display_bmp(char *bmpname,int x0,int y0)
{
     //3.打开图片 
    int bmp_fd = open(bmpname,O_RDWR);
    if(bmp_fd == -1)
    {
        perror("open bmp failed");
        return -1;
    }
    //4.读取图片的宽、高、色深以及是否需要赖子
    int width = 0;
    lseek(bmp_fd,0x12,SEEK_SET);
    int ret = read(bmp_fd,&width,4);
    if(ret == -1)
    {
        perror("read failed");
        return -1;
    }
    // printf("width = %d\n",width);

    int high = 0;
    lseek(bmp_fd,0x16,SEEK_SET);
    ret = read(bmp_fd,&high,4);
    if(ret == -1)
    {
        perror("read failed");
        return -1;
    }
    // printf("high = %d\n",high);

    int depth = 0;
    lseek(bmp_fd,0x1C,SEEK_SET);
    ret = read(bmp_fd,&depth,2);
    if(ret == -1)
    {
        perror("read failed");
        return -1;
    }
    // printf("depth = %d\n",depth);

    int bytes_per_line = abs(width)*(depth/8);
    int laizi = 0;
    if(bytes_per_line %4 !=0)
    {
        laizi = 4 - bytes_per_line %4;
    }
    //每一行实际的字节数为
    int bytes_lines = bytes_per_line + laizi;
    //整张图片的所有像素点大小为：
    int size = abs(high)*bytes_lines;

    //5.定义数组去读取图片的所有像素
    char p[size];//数组定义好了
    lseek(bmp_fd,0x36,SEEK_SET);
    read(bmp_fd,p,size);

    //6.解析像素数组
    unsigned char a,r,g,b;
    unsigned int color;
    int i=0;
    int x,y;
    for(y=0;y<abs(high);y++)
    {
        for(x=0;x<abs(width);x++)
        {
            b=p[i++];
            g=p[i++];
            r=p[i++];
            if(depth == 32)
            {
                a=p[i++];
            }
            else
            {
                a=0;
            }
            color = (a<<24)|(r<<16)|(g<<8)|(b);
            Draw_point((width>0)?x+x0:abs(width)-x-1+x0,(high>0)?high-y-1+y0:y+y0,color);
        }
        //跳过赖子
        i=i+laizi;
    }
    //7.关闭图片 
    close(bmp_fd);
}

