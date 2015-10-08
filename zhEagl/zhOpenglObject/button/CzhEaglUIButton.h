//
//  CzhEaglUIButton.h
//  zhOpenglEs
//
//  Created by H.zh on 13-12-5.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#ifndef __zhOpenglEs__CzhEaglUIButton__
#define __zhOpenglEs__CzhEaglUIButton__

#include <iostream>
#include <string>
#include "zhEaglButtonDef.h"
#include "CzhEaglUIView.h"
#include "CzhEaglUILabel.h"
#include "CzhEaglFont.h"

using namespace std;

class CzhEaglUIButton:public CzhEaglUIView{

private:
    
    string _norFontname;
    string _hightFontname;
    string _selectFontname;
    string _disableFontname;
    
    short _norFontsize;
    short _hightFontsize;
    short _selectFontsize;
    short _disableFontsize;
    
    CzhEaglUILabel _norText;
    CzhEaglUILabel _hightText;
    CzhEaglUILabel _selectText;
    CzhEaglUILabel _disableText;
    
    CzhEaglUIView _norImg;
    CzhEaglUIView _hightImg;
    CzhEaglUIView _selectImg;
    CzhEaglUIView _disableImg;

public:

    // _active判断touchDown的时候是否选中BUTTON
    BOOL active;
    // state按钮的状态
    EzhEaglBtnState state;
    // 判断按钮是否为checkbox状态
    BOOL selected;

public:
    
    CzhEaglUIButton();
    ~CzhEaglUIButton();
    
    void setTitle(wstring str,EzhEaglBtnState bs);
    void setTitle(wstring str,
                   EzhEaglBtnState bs,
                   const char* fontname,
                   float fontsize);

    void setTitleImageByPNG(const char* path,EzhEaglBtnState bs);
    void setTitleImageByJPG(const char* path,EzhEaglBtnState bs);
    void setTitleColor(float r,float g,float b,EzhEaglBtnState bs);
    void setTitlteSize(float s,EzhEaglBtnState bs);

    void setTop(int t);
    void setLeft(int l);
    void setWidth(int w);
    void setHeight(int h);

    void setSelect(BOOL b);

    void reader();

    //事件检测
    CzhEaglUIView* eventDown(TzhEaglLine* linp);
    CzhEaglUIView* eventUp(TzhEaglLine* linp);

};

#endif /* defined(__zhOpenglEs__CzhEaglUIButton__) */
