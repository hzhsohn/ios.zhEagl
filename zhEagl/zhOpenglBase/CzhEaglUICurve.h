//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#ifndef __zhOpenglEs__CzhEaglUICurve__
#define __zhOpenglEs__CzhEaglUICurve__

#include "CzhEaglUIView.h"
#include <vector>

using namespace std;

/*
 画曲线的类
 
 _line=[[MzhEaglUI_EQ_Line alloc] init];
 [_line setOffsetX:0];
 [_line setOffsetY:0];
 
 [self setLineSize:2];
 [self setColorR:0 G:1 B:0 A:1];
 [self setAntiAliasing:true];
 
 char w[300];//w为曲线的数据缓冲区
 [_line setLineBuf:ezhEaglUICurveData_Y_1B :w length:sizeof(w)];
 
 [egalView addSubView:_line];
 [_line release];

*/

#define CurveList_Vec   vector<TzhEaglPoint2>

typedef enum _EzhEaglUICurveBufType
{
    ezhEaglUICurveData_XY_2Byte,   //X坐标1个字节,Y坐标1个字节
    ezhEaglUICurveData_XY_4Byte,   //X坐标2个字节,Y坐标2个字节
    ezhEaglUICurveData_XY_8Byte    //X坐标4个字节,Y坐标4个字节
}EzhEaglUICurveBufType;

class CzhEaglUICurve :public CzhEaglUIBase
{
private:

    //最长高宽
    int _width;
    int _height;
    
public:

    //线粗细
    unsigned short size;
    TzhEaglColorRGB lineColor;

    //链表
    CurveList_Vec lstPoint;

    //左右偏移坐标
    int left;
    int top;
    
public:
    
    CzhEaglUICurve();
    ~CzhEaglUICurve();
    
    void setLeft(int l);
    void setTop(int t);
    int getLeft();
    int getTop();
    int getWidth();
    int getHeight();

    void setPointBuf(EzhEaglUICurveBufType type,char* buf, int len);
    void addPoint(int x,int y);
    void removeAllPoint();

    //设线的粗细
    void setLineSize(int n);

    void setLineColor(float r ,float g ,float b);
    void setLineColor(TzhEaglColorRGB rgb);
    
    void reader();
};

#endif
