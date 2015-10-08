//
//  MzhEaglUILabel.m
//  eq_sample
//
//  Created by sohn on 13-7-4.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#include "CzhEaglUILabel.h"

#define zhEaglUILabel_Default_Scale_Size    1

CzhEaglUILabel::CzhEaglUILabel()
{
    _scaleSize=zhEaglUILabel_Default_Scale_Size;
    
    fontColor.r=0;
    fontColor.g=0;
    fontColor.b=0;
    
    _texCoodr[0]=0.0f;_texCoodr[1]=0.0f;//bottom top
    _texCoodr[2]=0.0f;_texCoodr[3]=1.0f;//top left of square
    _texCoodr[4]=1.0f;_texCoodr[5]=1.0f;//top right of square
    _texCoodr[6]=1.0f;_texCoodr[7]=0.0f;//bottom right of square
    
    _fontSpacing=0;
    
    left=0;
    top=0;
    _width=0;
    _height=0;
}

CzhEaglUILabel::CzhEaglUILabel(CzhEaglFont* font)
{
    CzhEaglUILabel();
    setFont(font);
}

CzhEaglUILabel::~CzhEaglUILabel()
{
    destroy();
}

void CzhEaglUILabel::_freeTexture()
{
    //由CzhEaglFont::loadChar加载字符串转成内存图片会绑定到gl的纹理里,所以释放时一定要将纹理也销掉
    list<TzhEaglFontChar>::iterator it;
    for (it=_lstTextTexture.begin(); it!=_lstTextTexture.end(); it++) {
        if (it->gl_texID) {
            glDeleteTextures(1, &it->gl_texID);
        }
    }
    _lstTextTexture.clear();
}

void CzhEaglUILabel::_backgroundFixSize()
{
    //计算字体总长度
    if (_lstTextTexture.size()>0) {
        
        list<TzhEaglFontChar>::iterator it;
        int scatWidth=0;
        int max_it=0;
        int tmpN=0;
        for (it=_lstTextTexture.begin(); it!=_lstTextTexture.end(); it++)
        {
            //最长的Right
            scatWidth+=_fontSpacing;
            tmpN=it->gl_left+it->width+scatWidth;
            if (max_it<tmpN) {
                max_it=tmpN;
            }
        }
        _width=max_it*_scaleSize;
        if (_width<_fontPicMaxWidth) {
            _width=_fontPicMaxWidth;
        }
        _height=_fontHeight*_scaleSize;
    }
}

void CzhEaglUILabel::setLeft(int l)
{
    left=l;
}
void CzhEaglUILabel::setTop(int t)
{
    top=t;
}

int CzhEaglUILabel::getLeft()
{
    return left;
}
int CzhEaglUILabel::getTop()
{
    return top;
}
int CzhEaglUILabel::getWidth()
{
    return _width;
}
int CzhEaglUILabel::getHeight()
{
    return _height;
}

void CzhEaglUILabel::setFont(CzhEaglFont* font)
{
    _pFont=font;
    if (_stext.length()>0) {
        setCharacters(_stext.c_str(),_stext.length());
    }
}

void CzhEaglUILabel::setString(wstring text)
{
    setCharacters(text.c_str(),text.length());
}

void CzhEaglUILabel::setCharacters(const wchar_t* text,int len)
{
    if (NULL==_pFont) {
        printf("CzhEaglUILabel not set font\n");
        return;
    }
    
    //清空所有字
    _freeTexture();
    _stext=text;
    
    if (len<=0) {
        return;
    }
    
    TzhEaglFontChar retData;
    vector<TzhEaglFontChar>::iterator it;
    
    _fontPicMaxWidth=0;
    _pFont->loadDefaultCharLeft();
    for (int i=0; i<len; i++)
    {
        if(_pFont->loadChar(text[i],&retData,&_fontPersent,&_fontWidth,&_fontHeight))
        {
            if (_fontPicMaxWidth<retData.width) {
                _fontPicMaxWidth=retData.width;
            }
            //添加到链表
            _lstTextTexture.push_back(retData);
        }
    }
    
    _backgroundFixSize();
}

void CzhEaglUILabel::setScaleSize(float size)
{
    _scaleSize=size;
    _backgroundFixSize();
}

void CzhEaglUILabel::setFontSpacing(int distance)
{
    _fontSpacing=distance;
    _backgroundFixSize();
}

void CzhEaglUILabel::destroy()
{
    _freeTexture();
    
    _stext=L"";
    _pFont=NULL;
    _scaleSize=zhEaglUILabel_Default_Scale_Size;
    _width=0;
    _height=0;
}

void CzhEaglUILabel::setFontColor(float r ,float g ,float b)
{
    fontColor.r=r;
    fontColor.g=g;
    fontColor.b=b;
}

void CzhEaglUILabel::setFontColor(TzhEaglColorRGB rgb)
{
    fontColor.r=rgb.r;
    fontColor.g=rgb.g;
    fontColor.b=rgb.b;
}

wstring CzhEaglUILabel::getString()
{
    return _stext;
}

void CzhEaglUILabel::reader()
{
#if 0
    //调试---
    #include "CzhEaglUIView.h"
    CzhEaglUIView v;
    v.setTop(top);
    v.setLeft(left);
    v.setWidth(_width);
    v.setHeight(_height);
    v.setAngle(angle);
    v.setAlpha(0.2);
    v.reader();
#endif
    //隐藏----------------------------
    if (hidden) { return ; }
    if (0==alpha) { return ; }
    if (0>=_stext.length()) {
        return;
    }
    
    //绘制----------------------------
    float scatWidth;
    
    //旋转偏移计算
    if (angle) {
        int half_width=_width>>1;
        int half_height=_height>>1;
        
        glPushMatrix();
        glTranslatef(left+half_width,top+half_height, 0);
        glRotatef(angle, 0, 0, 1);

        //文字位置
        glPushMatrix();
        glTranslatef(-half_width,-half_height, 0);
    }
    else
    {
        glPushMatrix();
        //文字位置
        glTranslatef(left,top, 0);
    }
    
    if (1!=_scaleSize) {
        glScalef(_scaleSize, _scaleSize, 0);
    }
    
    //先启用纹理功能,再录入图片里的坐标
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_BLEND);//启用融合效果
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//设置融合方式
    
    //绘制文字
    list<TzhEaglFontChar>::iterator it;
    it=_lstTextTexture.begin();
    scatWidth=0;
    int tmpW;
    int tmpL;
    int tmpR;
    for (; it!=_lstTextTexture.end(); it++) {
        
        scatWidth+=_fontSpacing;

        tmpW=it->gl_right-it->gl_left;
        tmpL=it->gl_left+scatWidth;
        tmpR=it->gl_right+scatWidth;
        
        //平面顶点数组
        _vertex[0]=tmpL;     _vertex[1]=it->gl_bottom;    //top left
        _vertex[2]=tmpL;     _vertex[3]=it->gl_top;      //bottom left
        _vertex[4]=tmpR;    _vertex[5]=it->gl_top;      //bottom right
        _vertex[6]=tmpR;    _vertex[7]=it->gl_bottom;    //top right
        
        if (_vertex[0]<0) {
            _vertex[0]=0;
        }
        if (_vertex[2]<0) {
            _vertex[2]=0;
        }
        
        if (_vertex[4]< tmpW) {
            _vertex[4]= tmpW;
        }
        if (_vertex[6]< tmpW) {
            _vertex[6]= tmpW;
        }
        
        //绘制
        glBindTexture(GL_TEXTURE_2D, it->gl_texID);
        glTexCoordPointer(2, GL_FLOAT, 0, &_texCoodr);
        
        //透明度
        glColor4f(fontColor.r,
                  fontColor.g,
                  fontColor.b,
                  alpha);
    
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, _vertex);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glColor4f(1, 1, 1, 1);//恢复透明度不影响别的模型
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_BLEND); //关闭融合效果
    glDisable(GL_TEXTURE_2D);//关闭纹理
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    //恢复旋转偏移计算
    if (angle) {
        glPopMatrix();
    }
    
    glPopMatrix();
    
}