//
//  CzhEaglExpPng.cpp
//  zhOpenglEs
//
//  Created by H.zh on 13-11-20.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#include "CzhEaglExpPng.h"


CzhEaglExpPng::CzhEaglExpPng()
{
    data=NULL;

}

CzhEaglExpPng::~CzhEaglExpPng()
{
    destroy();
}


/*
 判断是否为PNG文件
 */
#define PNG_BYTES_TO_CHECK 4
int CzhEaglExpPng::_isPNG(FILE *fp) {
    char buf[PNG_BYTES_TO_CHECK] = {0};
    /* Open the prospective PNG file. */
    if (fp == NULL)
    {
        return 0;
    }
    /* Read in some of the signature bytes */
    if (fread(buf, 1, PNG_BYTES_TO_CHECK, fp) != PNG_BYTES_TO_CHECK)
    {
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    return(!png_sig_cmp((png_byte*)buf, (png_size_t)0, PNG_BYTES_TO_CHECK));
}

void CzhEaglExpPng::destroy()
{
    //初始化数据
    len=0;
    bit_depth=0;
    width=0;
    height=0;
    if (data) {
        free(data);
        data=NULL;
    }
}

int CzhEaglExpPng::loadFile(const char*path)
{
    int ret;
    FILE* pic_fp;
    
    destroy();
    
    ret=0;
    pic_fp= fopen(path, "rb");
    //判断文件
    if (!_isPNG(pic_fp)) {
        //不是PNG文件
        if (pic_fp) {
            fclose(pic_fp);
        }
        return 1;
    }
    
    /* 初始化各种结构 */
    png_structp png_ptr;
    png_infop  info_ptr;
    int color_type,channels;
    
    png_ptr  = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    info_ptr = png_create_info_struct(png_ptr);
    
    setjmp(png_jmpbuf(png_ptr)); // 这句很重要
    
    rewind(pic_fp);
    /*开始读文件*/
    png_init_io(png_ptr, pic_fp);
    // 读文件了
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    
    
    /*获取宽度，高度，位深，颜色类型*/
    channels    = png_get_channels(png_ptr, info_ptr); /*获取通道数*/
    bit_depth   = png_get_bit_depth(png_ptr, info_ptr); /* 获取位深 */
    color_type  = png_get_color_type(png_ptr, info_ptr); /*颜色类型*/
    
    /* row_pointers里边就是rgba数据 */
    png_bytep* row_pointers;
    row_pointers = png_get_rows(png_ptr, info_ptr);
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    
    len = width * height; /* 计算图片的总像素点数量 */
    
    if(channels == 4 || color_type == PNG_COLOR_TYPE_RGB_ALPHA)
    {
        /*如果是RGB+alpha通道，或者RGB+其它字节*/
        len *= (4*sizeof(unsigned char));      /* 每个像素点占4个字节内存 */
        
        flag = ezhEaglExpPngFlag_Have_Alpha;    /* 标记 */
        data = (unsigned char*) malloc(len);
        if(data == NULL)
        {
            /* 如果分配内存失败 */
            printf("png no memory");
            ret=1;
            goto _end;
        }

        int i,j,temp;
        int pos=0;
        temp = (4 * width);/* 每行有4 * width个字节 */
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < temp; j += 4)
            {
                data[pos++] = row_pointers[i][j];   // red
                data[pos++] = row_pointers[i][j+1]; // green
                data[pos++] = row_pointers[i][j+2];  //blue
                data[pos++] = row_pointers[i][j+3]; // alpha
            }
        }
    }
    else if(channels == 3 || color_type == PNG_COLOR_TYPE_RGB)
    {
        /* 如果是RGB通道 */
        len *= (3*sizeof(unsigned char)); /* 每个像素点占3个字节内存 */
        
        flag = ezhEaglExpPngFlag_No_Alpha;    /* 标记 */
        data = (unsigned char*) malloc(len);
        if(data == NULL)
        {
            /* 如果分配内存失败 */
            printf("png no memory");
            ret=1;
            goto _end;
        }
       
        int i,j,temp;
        int pos=0;
        temp = (3 * width);/* 每行有3 * width个字节 */
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < temp; j += 3)
            {
                data[pos++] = row_pointers[i][j];   // red
                data[pos++] = row_pointers[i][j+1]; // green
                data[pos++] = row_pointers[i][j+2];  //blue
            }
        }
    }
    else
    {
        ret=1;
    }
_end:
    /* 撤销数据占用的内存 */
    png_destroy_read_struct(&png_ptr, &info_ptr, 0); 
    fclose(pic_fp);
    return ret;
}