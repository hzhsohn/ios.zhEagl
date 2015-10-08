//
//  CzhEaglUIView.h
//  zhOpenglEs
//
//  Created by H.zh on 13-10-21.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglUIView__
#define __zhOpenglEs__CzhEaglUIView__

#include <iostream>
#include <vector>
#include "CzhEaglUIBase.h"

using namespace std;


class CzhEaglUIView:public CzhEaglUIBase
{
    
private:
    //顶点和纹理
    float _vertex[8];
    float _texCoodr[8];
    
    //以中心为点的坐标
    int _x;
    int _y;
    
public:

    int left;
    int top;
    int width;
    int height;
    
    CzhEaglImage backgroundImage;
    TzhEaglColorRGBA backgroundColor;
    

public:
    CzhEaglUIView();
    ~CzhEaglUIView();
    
    void setLeft(int l);
    void setTop(int t);
    void setWidth(int w);
    void setHeight(int h);
    int getLeft();
    int getTop();
    int getWidth();
    int getHeight();
    
    /*
     保证纹理的唯一性,所以设置图片不能使用CzhEaglUIImage的直接附值
     void setBackgroundImage(CzhEaglUIImage* img);<<--禁止使用,编写逻辑时容易影响opengl纹理的管理
     */
    BOOL setBackgroundImage(const void* data ,TzhEaglTexture2DFormat pixelFormat,int width ,int height);
    BOOL setBackgroundImageByPNG(const char* imgPath);
    BOOL setBackgroundImageByJPG(const char* imgPath);

    void setBackgroundColor(float r ,float g ,float b);
    void setBackgroundColor(float r ,float g ,float b ,float a);
    void setBackgroundColor(TzhEaglColorRGB rgb);
    void setBackgroundColor(TzhEaglColorRGBA rgba);
    void setBackgroundColorAlpha(float a);

    TzhEaglRectangle getRectangle();
    void setRect(TzhEaglRect rect);
    TzhEaglRect getRect();

    //检测是否被射线选中
    CzhEaglUIView* pickUp(TzhEaglLine* linp);

    //绘制
    void reader();
};

#endif /* defined(__zhOpenglEs__CzhEaglUIView__) */
