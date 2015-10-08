//
//  CzhEaglExpPng.h
//  zhOpenglEs
//
//  Created by H.zh on 13-11-20.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglExpPng__
#define __zhOpenglEs__CzhEaglExpPng__

#include <iostream>
#include "png.h"


typedef enum _EzhEaglExpPngFlag
{
    ezhEaglExpPngFlag_No_Alpha=0,
    ezhEaglExpPngFlag_Have_Alpha=1
}EzhEaglExpPngFlag;

class CzhEaglExpPng
{
private:
    
protected:
    int _isPNG(FILE *fp);
    
public:
    CzhEaglExpPng();
    ~CzhEaglExpPng();
    
    int width;
    int height;             /* 尺寸 */
    int bit_depth;          /* 位深 */
    EzhEaglExpPngFlag flag; /* 一个标志，表示是否有alpha通道 */
    unsigned char *data;    /* 图片数组 */
    unsigned int len;
    
    void destroy();
    int loadFile(const char*path);
};


#endif /* defined(__zhOpenglEs__CzhEaglExpPng__) */
