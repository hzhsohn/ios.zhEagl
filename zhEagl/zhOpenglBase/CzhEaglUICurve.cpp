//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#include "CzhEaglUICurve.h"

CzhEaglUICurve::CzhEaglUICurve()
{
    left=0;
    top=0;
    
    lineColor.r=0;
    lineColor.g=0;
    lineColor.b=0;
    
    size=0;
}

CzhEaglUICurve::~CzhEaglUICurve()
{
    
}

void CzhEaglUICurve::setLeft(int l)
{
    left=l;
}
void CzhEaglUICurve::setTop(int t)
{
    top=t;
}

int CzhEaglUICurve::getLeft()
{
    return left;
}
int CzhEaglUICurve::getTop()
{
    return top;
}
int CzhEaglUICurve::getWidth()
{
    return _width;
}
int CzhEaglUICurve::getHeight()
{
    return _height;
}

void CzhEaglUICurve::setPointBuf(EzhEaglUICurveBufType type,char* buf, int len)
{
    TzhEaglPoint2 p2;
    int bytes=0;

    if (len<0) {
        return;
    }
    switch (type) {
        case ezhEaglUICurveData_XY_2Byte:   //X坐标1个字节,Y坐标1个字节
        {
            char tmp;
            removeAllPoint();
            bytes=2;
            for (int i=0; i<len; i+=bytes) {
                tmp=0;
                memcpy(&tmp, &buf[i], 1);
                p2.x=(int)tmp;
                tmp=0;
                memcpy(&tmp, &buf[i+1],1);
                p2.y=(int)tmp;
                lstPoint.push_back(p2);
            }
        }
            break;
        case ezhEaglUICurveData_XY_4Byte:   //X坐标2个字节,Y坐标2个字节
        {
            short tmp;
            removeAllPoint();
            bytes=4;
            for (int i=0; i<len; i+=bytes) {
                tmp=0;
                memcpy(&tmp, &buf[i], 2);
                p2.x=(int)tmp;
                tmp=0;
                memcpy(&tmp, &buf[i+2], 2);
                p2.y=(int)tmp;
                lstPoint.push_back(p2);
            }
        }
            break;
        case ezhEaglUICurveData_XY_8Byte:    //X坐标4个字节,Y坐标4个字节
        {
            int tmp;
            removeAllPoint();
            bytes=8;
            for (int i=0; i<len; i+=bytes) {
                tmp=0;
                memcpy(&tmp, &buf[i], 4);
                p2.x=(int)tmp;
                tmp=0;
                memcpy(&tmp, &buf[i+4], 4);
                p2.y=(int)tmp;
                lstPoint.push_back(p2);
            }
        }
            break;
    }
}

void CzhEaglUICurve::addPoint(int x,int y)
{
    TzhEaglPoint2 p2;
    p2.x=x;
    p2.y=y;
    lstPoint.push_back(p2);
}

void CzhEaglUICurve::removeAllPoint()
{
    lstPoint.clear();
}

void CzhEaglUICurve::setLineSize(int n)
{
    size=n;
}

void CzhEaglUICurve::setLineColor(float r ,float g ,float b)
{
    lineColor.r=r;
    lineColor.g=g;
    lineColor.b=b;
}

void CzhEaglUICurve::setLineColor(TzhEaglColorRGB rgb)
{
    lineColor.r=rgb.r;
    lineColor.g=rgb.g;
    lineColor.b=rgb.b;
}

void CzhEaglUICurve::reader()
{
    //隐藏----------------------------
    if (hidden) { return ; }
    if (0==alpha) { return ; }
    
    //绘制----------------------------
    TzhEaglPoint2 p2;
    
    if (lstPoint.size()<2) {
        return;
    }
    
    //演示抗锯齿效果
    glEnable(GL_BLEND);//启用融合效果
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//设置融合方式
    
    glPushMatrix();
    
    glTranslatef(left, top, 0);
    
    if (angle) {
        glRotatef(angle, 0, 0, 1);
    }
    
    p2=lstPoint[0];
    for (int i=1;i<lstPoint.size();i++) {
        
        GLfloat line[]={
            p2.x,p2.y,
            lstPoint[i].x, lstPoint[i].y,
        };
        p2=lstPoint[i];
        
        //颜色
        glColor4f(lineColor.r, lineColor.g, lineColor.b, alpha);
        
        if (size>0) {
            glLineWidth(size);
        }
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, line);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableClientState(GL_VERTEX_ARRAY);
        glLineWidth(1);
        glColor4f(1, 1, 1, 1);
        
        
    }
    glPopMatrix();
    
    glDisable(GL_BLEND);
}