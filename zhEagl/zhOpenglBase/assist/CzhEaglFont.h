//
//  CzhEaglFont.h
//  zhOpenglEs
//
//  Created by H.zh on 13-11-22.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglFont__
#define __zhOpenglEs__CzhEaglFont__

#include <iostream>
#include "zhEaglHeader.h"

#include <ft2build.h>
#include FT_FREETYPE_H

using namespace std;

typedef struct _TzhEaglFontChar
{
    //文字的实际高宽度,非GL图片高度
    int width;
    int height;
    
    //OPENGL的转换的宽高
    int gl_top;
    int gl_left;
    int gl_right;
    int gl_bottom;
    GLuint gl_texID;//纹理ID
}TzhEaglFontChar;

class CzhEaglFont
{
private:
    //描述
    unsigned short _fontSize;
    unsigned int _dpi;
    string _font;
    FT_Encoding _encode;
    //文字位置
    int _perWidth;
    
    //字体库内容
    FT_Library _library;
    FT_Face _face;
    FT_Error _error;
    FT_Encoding _enc;
    
    void _setCharInfo(TzhEaglFontChar* retData,int offset_x,int offset_y,int fontWidth,int fontHeight,int pic_width,int pic_height,int gl_width,int gl_height,float fontPersent);
    
public:
    CzhEaglFont();
    CzhEaglFont(const char*font_path,
                   int fontSize,
                   int dpi,
                   FT_Encoding enc);
    //默认是unicode编码
    CzhEaglFont(const char*font_path,
                int fontSize,
                int dpi);
    ~CzhEaglFont();
    
    /*返回最接近2次方的数*/
    inline int next_p2 (int a );
    
    BOOL init(const char*font_path,
                  int fontSize,
                  int dpi,
                  FT_Encoding enc);
    BOOL init(const char*font_path,
              int fontSize,
              int dpi);
    
    /*由CzhEaglFont::loadChar加载字符串转成内存图片会绑定到gl的纹理里,
     所以释放时一定要glDeleteTextures将纹理也销掉,初始化的位置要使用loadDefaultCharLeft()*/
    void loadDefaultCharLeft();
    BOOL loadChar(FT_ULong chr,TzhEaglFontChar* retData,float*persent,int*font_width,int*font_height);
    
    //
    void destory();
    
    FT_Library* getLibrary();
    FT_Face* getFace();
    FT_Error* getError();
    
    int getFontSize();
    int getDpi();
    const char* getFontName();
};

#endif /* defined(__zhOpenglEs__CzhEaglFont__) */
