//
//  CzhEaglUIBase.cpp
//  zhOpenglEs
//
//  Created by H.zh on 13-12-1.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#include "CzhEaglUIBase.h"

CzhEaglUIBase::CzhEaglUIBase()
{
    tag=0;
    alpha=1;
    enable=true;
    hidden=false;
    angle=0;
}

CzhEaglUIBase::~CzhEaglUIBase()
{

}

void CzhEaglUIBase::setAlpha(float a)
{
    alpha=a;
}
void CzhEaglUIBase::setTag(int n)
{
    tag=n;
}
void CzhEaglUIBase::setEnable(BOOL b)
{
    enable=b;
}
void CzhEaglUIBase::setHidden(BOOL b)
{
    hidden=b;
}

void CzhEaglUIBase::setAngle(short r)
{
    angle=r;
}

//线性深入检测
float CzhEaglUIBase::lineRectangleInside(TzhEaglLine* linp,TzhEaglRectangle rectangle)
{
    TzhEaglPoint3 pointOnBox;
    TzhEaglPoint3 savePoint;
    float saveDepth = NSIntegerMax;
    float ret;
    
    if ((ret = isLineCrossRectangle(linp, &rectangle, &pointOnBox)) < saveDepth)  {
        saveDepth = ret;
        savePoint = pointOnBox;
    }
    
    if (saveDepth < NSIntegerMax) {
        _depth=saveDepth;
        _hitPoint=savePoint;
        return saveDepth;
    }else{
        return 0.0f;
    }
}

float CzhEaglUIBase::lineTriangleInside(TzhEaglLine* linp,TzhEaglTriangle triangle)
{
    TzhEaglPoint3 pointOnTriangle;
    TzhEaglPoint3 savePoint;
    float saveDepth = NSIntegerMax;
    float ret;
    
    if ((ret = isLineCrossTriangle(linp, &triangle, &pointOnTriangle)) < saveDepth)  {
        saveDepth = ret;
        savePoint = pointOnTriangle;
    }
    
    if (saveDepth < NSIntegerMax) {
        _depth=saveDepth;
        _hitPoint=savePoint;
        return saveDepth;
    }else{
        return 0.0f;
    }
}
