//
//  CzhEaglFont.cpp
//  zhOpenglEs
//
//  Created by H.zh on 13-11-22.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#include "CzhEaglFont.h"
#include "zhEaglFunc.h"

CzhEaglFont::CzhEaglFont()
{

}

CzhEaglFont::CzhEaglFont(const char*font_path,
                               int fontSize,
                               int dpi,
                               FT_Encoding enc)
{
    init(font_path, fontSize, dpi, enc);
}

CzhEaglFont::CzhEaglFont(const char*font_path,
                         int fontSize,
                         int dpi)
{
    init(font_path, fontSize, dpi);
}

CzhEaglFont::~CzhEaglFont()
{

}

void CzhEaglFont::_setCharInfo(TzhEaglFontChar* retData,
                               int offset_x,int offset_y,
                               int fontWidth,int fontHeight,
                               int pic_width,int pic_height,
                               int gl_width,int gl_height,
                               float fontPersent)
{
    float tmpLeft;
    float tmpLeft_t;
    float tmpTop;
    float tmpTop_t;
    
    //调整GL显示的大小
    float tH=gl_height*fontPersent;
    float tW=gl_width*fontPersent;
    float offsetTop=offset_y*fontPersent;
    tmpLeft=_perWidth;
    tmpLeft_t=tmpLeft+tW;
    tmpTop=offsetTop-tH;
    tmpTop_t=offsetTop;
    
    tmpTop+=fontHeight;
    tmpTop_t+=fontHeight;
    
    int n=(pic_width+offset_x)*fontPersent+0.5f;
    _perWidth+=n;
    
    //平面顶点数组
    retData->gl_left=tmpLeft;
    retData->gl_top=tmpTop;
    retData->gl_right=tmpLeft_t;
    retData->gl_bottom=tmpTop_t;
    
    retData->width=pic_width*fontPersent;
    retData->height=pic_height*fontPersent;
    
}


int CzhEaglFont::next_p2 (int a )
{
    int rval=1;
    // rval<<=1 Is A Prettier Way Of Writing
    rval*=2;
    while(rval<a)
        rval<<=1;
    return rval;
}

BOOL CzhEaglFont::init(const char*font_path,
                               int fontSize,
                               int dpi,
                               FT_Encoding enc)
{
    _error = FT_Init_FreeType(&_library);
    if  (!_error)
    {
        // 是否初始化成功
    }
    // 加载一个字库
    _error = FT_New_Face(_library,font_path, 0, &_face);
    if  (FT_Err_Unknown_File_Format==_error)
    {
        // 表示可以打开和读此文件，但不支持此字体格式
    }
    else  if(_error)
    {
        // 其他错误
        return FALSE;
    }
    
    
    _font=font_path;
    _fontSize=fontSize;
    _dpi=dpi;
    _encode=enc;
    
    // 设定为UNICODE，默认也是
    FT_Select_Charmap(_face,_encode);
    // 设定字体字符宽高和分辨率
    _error = FT_Set_Char_Size(_face, 0 ,  _fontSize << 6, 0, _dpi);
 
    loadDefaultCharLeft();
    return TRUE;
}

BOOL CzhEaglFont::init(const char*font_path,
                       int fontSize,
                       int dpi)
{
    return init(font_path, fontSize, dpi, FT_ENCODING_UNICODE);
}

void CzhEaglFont::loadDefaultCharLeft()
{
    _perWidth=0;
}

BOOL CzhEaglFont::loadChar(FT_ULong chr,TzhEaglFontChar* retData,float*persent,int*font_width,int*font_height)
{
    if (_font.length()<=0) {
        printf("CzhEaglFont not set font\n");
        return FALSE;
    }
    if (0==_fontSize) {
        printf("CzhEaglFont not set font size\n");
        return FALSE;
    }

    //--------设置文字
    // 查找字符索引
    FT_UInt glyph_index = FT_Get_Char_Index(_face, chr);
    // 装载字型图像到字形槽
    _error = FT_Load_Glyph(_face, glyph_index, FT_LOAD_DEFAULT);
    if (_error) {
        return FALSE;
    }
    // 转换为位图数据
    if (_face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
    {
        //第二个参数为渲染模式
        //FT_RENDER_MODE_MONO渲染为1位位图（黑白位图）
        //若为FT_RENDER_MODE_NORMAL则渲染为256级灰度图
        _error = FT_Render_Glyph(_face->glyph, FT_RENDER_MODE_NORMAL);
        if (_error) {
            return FALSE;
        }
    }

    //---------字体图片数据
    int width = _face->glyph->bitmap.width;
    int height = _face->glyph->bitmap.rows;
    
    if (0==width || 0==height) {
        return FALSE;
    }
    
    unsigned char* pTxtBuf=_face->glyph->bitmap.buffer;
    
    //---------适应OPENGLES的图片格式和坐标体系
    int gl_width=next_p2(width);
    int gl_height=next_p2(height);
    
    if(gl_width>0 && gl_height>0)
    {
        GLubyte* e_data = (GLubyte*)malloc(gl_width * gl_height);
        if (NULL==e_data) {
            return FALSE;
        }
        memset(e_data, 0, gl_width * gl_height);
        
        for(int j=0; j< gl_height;j++)
        {
            for(int i=0; i< gl_width; i++)
            {
                e_data[i+j*gl_width] = (i<width && j<height)?pTxtBuf[i + width*j]:0;
            }
        }
        /*
        //打印测试
        for(int y=0;y<retData->gl_height;y++)
        {
            for(int x=0;x<retData->gl_width;x++)
            {
                printf("%02X",e_data[y*retData->gl_width+x]?0xff:0);
            }
            printf("\n");
        }
        printf("\n\n");
        */
        //载入图片纹理
        retData->gl_texID=gluLoadTexture(e_data,ezhEaglImg_A8, gl_width , gl_height);
        free(e_data);
        e_data=NULL;
        
        //-值 -------
        if (_dpi>0) {
            *persent=72.0f/_dpi;
        }
        else{
            *persent=1;
        }
        *font_width=(_face->size->metrics.max_advance>>6)*(*persent);
        *font_height=(_face->size->metrics.height>>6)*(*persent);
        //首先在创建好FTFace，Freetype推荐使用基线作为绘制基准，但是通常都是设置字符左上角的位置开始绘制。需要获
        //得基线到字符轮廓最高点的距离，这个信息放在
        float ascender=_face->size->metrics.ascender >> 6;
        _setCharInfo(retData,
                     _face->glyph->bitmap_left,
                     _face->glyph->bitmap_top-ascender,
                     *font_width,*font_height,
                     width,height,
                     gl_width, gl_height,
                     *persent);
    }
    return TRUE;
}

void CzhEaglFont::destory()
{
    //释放数据
    FT_Done_Face(_face);
    FT_Done_FreeType(_library);
}

FT_Library* CzhEaglFont::getLibrary()
{
    return &_library;
}
FT_Face* CzhEaglFont::getFace()
{
    return &_face;
}
FT_Error* CzhEaglFont::getError()
{
    return &_error;
}

int CzhEaglFont::getFontSize()
{
    return _fontSize;
}
int CzhEaglFont::getDpi()
{
    return _dpi;
}
const char* CzhEaglFont::getFontName()
{
    return _font.c_str();
}
