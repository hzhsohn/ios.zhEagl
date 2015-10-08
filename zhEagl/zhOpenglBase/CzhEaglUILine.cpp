//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#include "CzhEaglUILine.h"


CzhEaglUILine::CzhEaglUILine()
{
    left=0;
    top=0;
    
    lineColor.r=0;
    lineColor.g=0;
    lineColor.b=0;
    
    size=0;
}

CzhEaglUILine::~CzhEaglUILine()
{

}

void CzhEaglUILine::setLine(int x,int y,int xx,int yy)
{
    x1=x;
    y1=y;
    x2=xx;
    y2=yy;
}
void CzhEaglUILine::setLeft(int l)
{
    left=l;
}
void CzhEaglUILine::setTop(int t)
{
    top=t;
}

int CzhEaglUILine::getLeft()
{
    return left;
}
int CzhEaglUILine::getTop()
{
    return top;
}
int CzhEaglUILine::getWidth()
{
    return x2-x1;
}
int CzhEaglUILine::getHeight()
{
    return y2-y1;
}

void CzhEaglUILine::setX1(int x)
{
    x1=x;
}
void CzhEaglUILine::setY1(int y)
{
    y1=y;
}
void CzhEaglUILine::setX2(int xx)
{
    x2=xx;
}
void CzhEaglUILine::setY2(int yy)
{
    y2=yy;
}

void CzhEaglUILine::setLineSize(int n)
{
    size=n;
}

float CzhEaglUILine::getX1()
{
    return x1;
}

float CzhEaglUILine::getY1()
{
    return y1;
}

float CzhEaglUILine::getX2()
{
    return x2;
}

float CzhEaglUILine::getY2()
{
    return y2;
}

void CzhEaglUILine::setLineColor(float r ,float g ,float b)
{
    lineColor.r=r;
    lineColor.g=g;
    lineColor.b=b;
}

void CzhEaglUILine::setLineColor(TzhEaglColorRGB rgb)
{
    lineColor.r=rgb.r;
    lineColor.g=rgb.g;
    lineColor.b=rgb.b;
}

void CzhEaglUILine::reader()
{
    //隐藏----------------------------
    if (hidden) { return ; }
    if (0==alpha) { return ; }
    
    //绘制----------------------------
    glPushMatrix();
    //文字位置
    glTranslatef(left,top, 0);
    
    if (angle) {
        glRotatef(angle, 0, 0, 1);
    }
    
    float lineBuf[]={
        x1,y1,
        x2,y2
    };
    
    //演示抗锯齿效果
    glEnable(GL_BLEND);//启用融合效果
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//设置融合方式

    //最后一是透明度
    glColor4f(lineColor.r, lineColor.g, lineColor.b, alpha);
    if (size>0) {
        glLineWidth(size);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, lineBuf);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableClientState(GL_VERTEX_ARRAY);
    glLineWidth(1);
    glColor4f(1, 1, 1, 1);

    glDisable(GL_BLEND);

    glPopMatrix();
}

