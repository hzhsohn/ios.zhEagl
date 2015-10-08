//
//  CzhEaglExpJpg.h
//  zhOpenglEs
//
//  Created by H.zh on 13-11-21.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglExpJpg__
#define __zhOpenglEs__CzhEaglExpJpg__

#include <iostream>
#include "jpeglib.h"
#include <setjmp.h>

class CzhEaglExpJpg
{
private:
    
protected:
    
public:
    CzhEaglExpJpg();
    ~CzhEaglExpJpg();
    
    int width;
    int height;             /* 尺寸 */
    int gamma;              /* 位深 */
    unsigned char *data;    /* 图片数组 */
    unsigned int len;
    
    void destroy();
    int loadFile(const char*path);
};



#endif /* defined(__zhOpenglEs__CzhEaglExpJpg__) */
