//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#ifndef __zhOpenglEs__CzhEaglUILine__
#define __zhOpenglEs__CzhEaglUILine__

#include "CzhEaglUIView.h"


/*
 画直线的类
 
 CzhEaglUILine l;
 line.setLine(400, 400, 600, 600);
 //line.lineColor=zhEaglColorRGBMake(1, 0,0);
 line.setLineColor(1, 0,0);
 line.setLineSize(10);
 line.setAngle(0);
 
*/
class CzhEaglUILine :public CzhEaglUIBase
{
private:

public:
    TzhEaglColorRGB lineColor;
    
    //坐标
    GLfloat x1,y1,x2,y2;
    //线粗细
    unsigned short size;

    //左右偏移坐标
    int left;
    int top;
    
public:

    CzhEaglUILine();
    ~CzhEaglUILine();
    
    void setLeft(int l);
    void setTop(int t);
    int getLeft();
    int getTop();
    int getWidth();
    int getHeight();
    
    void setLine(int x,int y,int xx,int yy);
    void setX1(int x);
    void setY1(int y);
    void setX2(int xx);
    void setY2(int yy);
    
    //设线的粗细和偏移值
    void setLineSize(int n);
    
    void setLineColor(float r ,float g ,float b);
    void setLineColor(TzhEaglColorRGB rgb);
    
    //返回坐标
    float getX1();
    float getX2();
    float getY1();
    float getY2();
    
    void reader();
};

#endif

