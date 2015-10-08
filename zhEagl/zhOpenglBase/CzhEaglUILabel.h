//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

/*
 
 如果是XCODE的话setString可以配合以下函数使用
 wchar_t* charToWchar(NSString* str,wchar_t* dst_buf)
 
 例:
 lb.setString(L"AbcDefGH");
 
 wchar_t uuu[1024];
 charToWchar(@"我是一个苦B的代码工!!~!@#$%^&*" ,uuu);
 lb.setCharacters(uuu, wcslen(uuu));
 
 lb.setString(charToWchar(@"唉~!!" ,uuu));
 
 */

#ifndef __zhOpenglEs__CzhEaglUILabel__
#define __zhOpenglEs__CzhEaglUILabel__


#include "zhEaglFunc.h"
#include "zhEaglMath.h"
#include "CzhEaglUIView.h"
#include "CzhEaglImage.h"
#include "CzhEaglFont.h"

#include <string>
#include <list>
using namespace std;


/*
 细节:
    关于旋转,旋转的方式是根据backgrounp的大小决定
    关于拾取,拾取的块是以backgrounp的大小决定
 */
class CzhEaglUILabel :public CzhEaglUIBase
{
private:
    float _vertex[8];
    float _texCoodr[8];
    
    wstring _stext;
    float _scaleSize;
    float _fontPersent;
    int _fontWidth;
    int _fontPicMaxWidth;//pic图片的实际长度,非GL图片长度
    int _fontHeight;
    int _fontSpacing;
    CzhEaglFont* _pFont;
    list<TzhEaglFontChar> _lstTextTexture;
    
    //生成后字体的高宽
    int _width;
    int _height;
    
    //释放字体纹理
    void _freeTexture();
    //背景自适应图形的高宽度
    void _backgroundFixSize();
    
public:
    
    TzhEaglColorRGB fontColor;
    int left;
    int top;
    
public:
    
    CzhEaglUILabel();
    CzhEaglUILabel(CzhEaglFont* font);
    ~CzhEaglUILabel();
    
    void setLeft(int l);
    void setTop(int t);
    int getLeft();
    int getTop();
    int getWidth();
    int getHeight();
    
    void setFont(CzhEaglFont* font);
    void setString(wstring text);
    void setCharacters(const wchar_t* text,int len);
    void setScaleSize(float size);
    void setFontSpacing(int distance);

    void setFontColor(float r ,float g ,float b);
    void setFontColor(TzhEaglColorRGB rgb);
    
    wstring getString();
    
    void reader();
    /*
        销毁对象,可以用来释放内存
     */
    void destroy();
    
    
};

#endif
