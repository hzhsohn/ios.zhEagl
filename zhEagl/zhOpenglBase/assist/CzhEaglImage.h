//
//  CzhEaglUIImage.h
//  zhOpenglEs
//
//  Created by H.zh on 13-10-22.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglUIImage__
#define __zhOpenglEs__CzhEaglUIImage__

#include <iostream>

#include "zhEaglHeader.h"
#include "zhEaglFunc.h"
#include "zhEaglMath.h"
#include "../expand/CzhEaglExpPng.h"
#include "../expand/CzhEaglExpJpg.h"

using namespace std;

/*
 图片类,用于处理图片转到纹理里
 
 This class allows to easily create OpenGL 2D textures from images, text or raw data.
 The created Texture2D object will always have power-of-two dimensions.
 Depending on how you create the Texture2D object, the actual image area of the texture might be smaller than the texture dimensions i.e. "imgSize" != (pixelsWide, pixelsHigh) and (maxS, maxT) != (1.0, 1.0).
 Be aware that the content of the generated textures will be upside-down!
 
 */
class CzhEaglImage
{
private:
    TzhEaglTexture2DFormat _pixelFormat;
    GLuint      _textureID;
    TzhEaglSize _piexlSize;
    
public:
    CzhEaglImage();
    ~CzhEaglImage();
    
    /*返回最接近2次方的数*/
    inline int next_p2 (int a );
    
    /*
      用于加载数据到纹理的函数
      这函数与类里面的相关变量绑定
     */
    BOOL loadImage(const void* data ,TzhEaglTexture2DFormat pixelFormat,int width ,int height);
    GLuint getTextureID();
    void deleteTexture();
    
    /*
      直接加载文件
      autoGLImg自转转换成opengl的图片格式
     */
    BOOL loadPNG(const char*path,BOOL autoGLImg);
    BOOL loadJPG(const char*path,BOOL autoGLImg);
};

#endif /* defined(__zhOpenglEs__CzhEaglUIImage__) */
