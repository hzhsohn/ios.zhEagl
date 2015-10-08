//
//  CzhEaglUIBase.h
//  zhOpenglEs
//
//  Created by H.zh on 13-12-1.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglUIBase__
#define __zhOpenglEs__CzhEaglUIBase__

#include <iostream>

#include "zhEaglFunc.h"
#include "zhEaglMath.h"
#include "CzhEaglImage.h"

class CzhEaglUIBase
{
//private:
    
protected:
    
    float           _depth;//点击深度测试 －－－》射线 原点到物体的距离
    TzhEaglPoint3   _hitPoint;//点击 交点
    
public:
    
    int tag; //识别的标签
    BOOL enable;
    BOOL hidden;
    float alpha;
    short angle;

public:
    
    CzhEaglUIBase();
    ~CzhEaglUIBase();
    
    void setAlpha(float a);
    void setTag(int n);
    void setEnable(BOOL b);
    void setHidden(BOOL b);
    void setAngle(short r);
    
    //判断图形是否被选中
    float lineRectangleInside(TzhEaglLine* linp,TzhEaglRectangle rectangle);//四方形
    float lineTriangleInside(TzhEaglLine* linp,TzhEaglTriangle triangle);//三角形
};

#endif /* defined(__zhOpenglEs__CzhEaglUIBase__) */
