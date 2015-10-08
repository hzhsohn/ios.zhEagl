//
//  CzhEaglUIButton.cpp
//  zhOpenglEs
//
//  Created by H.zh on 13-12-5.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//

#include "CzhEaglUIButton.h"

CzhEaglUIButton::CzhEaglUIButton()
{
    //字体
    _norFontname = string(localPath())+zhEgal_default_fontname;
    _hightFontname = string(localPath())+zhEgal_default_fontname;
    _selectFontname = string(localPath())+zhEgal_default_fontname;
    _disableFontname = string(localPath())+zhEgal_default_fontname;
    
    _norFontsize = zhEgal_default_fontsize;
    _hightFontsize = zhEgal_default_fontsize;
    _selectFontsize = zhEgal_default_fontsize;
    _disableFontsize = zhEgal_default_fontsize;
    
    _norText.setEnable(FALSE);
    _hightText.setEnable(FALSE);
    _selectText.setEnable(FALSE);
    _disableText.setEnable(FALSE);
}
CzhEaglUIButton::~CzhEaglUIButton()
{
    
}

void CzhEaglUIButton::setTop(int t)
{
    int tt;
    CzhEaglUIView::setTop(t);
    
    tt=t+height/2-_norText.getHeight()/2;
    _norText.setTop(tt);
    
    tt=t+height/2-_hightText.getHeight()/2;
    _hightText.setTop(tt);
    
    tt=t+height/2-_selectText.getHeight()/2;
    _selectText.setTop(tt);
    
    tt=t+height/2-_disableText.getHeight()/2;
    _disableText.setTop(tt);
    
    _norImg.setTop(t);
    _hightImg.setTop(t);
    _selectImg.setTop(t);
    _disableImg.setTop(t);
}
void CzhEaglUIButton::setLeft(int l)
{
    int ll;
    CzhEaglUIView::setLeft(l);
    
    ll=l+width/2-_norText.getWidth()/2;
    _norText.setLeft(ll);
    
    ll=l+width/2-_hightText.getWidth()/2;
    _hightText.setLeft(ll);
    
    ll=l+width/2-_selectText.getWidth()/2;
    _selectText.setLeft(ll);
    
    ll=l+width/2-_disableText.getWidth()/2;
    _disableText.setLeft(ll);
    
    _norImg.setLeft(l);
    _hightImg.setLeft(l);
    _selectImg.setLeft(l);
    _disableImg.setLeft(l);
}
void CzhEaglUIButton::setWidth(int w)
{
    CzhEaglUIView::setWidth(w);
    
    _norImg.setWidth(w);
    _hightImg.setWidth(w);
    _selectImg.setWidth(w);
    _disableImg.setWidth(w);
}
void CzhEaglUIButton::setHeight(int h)
{
    CzhEaglUIView::setHeight(h);
    
    _norImg.setHeight(h);
    _hightImg.setHeight(h);
    _selectImg.setHeight(h);
    _disableImg.setHeight(h);
}

void CzhEaglUIButton::setTitle(wstring str,EzhEaglBtnState bs)
{
    switch (bs) {
        case ezhEaglBtnStateNor:
            setTitle(str, bs,_norFontname.c_str(),_norFontsize);
            break;
        case ezhEaglBtnStateHight:
            setTitle(str, bs,_hightFontname.c_str(),_hightFontsize);
            break;
        case ezhEaglBtnStateSelect:
            setTitle(str, bs,_selectFontname.c_str(),_selectFontsize);
            break;
        case ezhEaglBtnStateDisable:
            setTitle(str, bs,_disableFontname.c_str(),_disableFontsize);
            break;
    }
}
void CzhEaglUIButton::setTitle(wstring str,
              EzhEaglBtnState bs,
              const char* fontname,
              float fontsize)
{
    CzhEaglFont font;

    switch (bs) {
        case ezhEaglBtnStateNor:
        {
            _norFontname=fontname;
            _norFontsize=fontsize;
            if(FALSE==font.init(_norFontname.c_str(), _norFontsize, 0))
            { return; }
            
            _norText.setFont(&font);
            _norText.setString(str);
            font.destory();
            
            if (0==_hightText.getString().length()) {
                goto __setHight;
            }
            
        }
            break;
        case ezhEaglBtnStateHight:
        {
        __setHight:
            _hightFontname=fontname;
            _hightFontsize=fontsize;
            if(FALSE==font.init(_hightFontname.c_str(), _hightFontsize, 0))
            { return; }
            
            _hightText.setFont(&font);
            _hightText.setString(str);
            font.destory();
        }
            break;
        case ezhEaglBtnStateSelect:
        {
            _selectFontname=fontname;
            _selectFontsize=fontsize;
            if(FALSE==font.init(_selectFontname.c_str(), _selectFontsize, 0))
            { return; }
            _selectText.setFont(&font);
            _selectText.setString(str);
            font.destory();
        }
            break;
        case ezhEaglBtnStateDisable:
        {
            _disableFontname=fontname;
            _disableFontsize=fontsize;
            if(FALSE==font.init(_disableFontname.c_str(), _disableFontsize, 0))
            { return; }
            _disableText.setFont(&font);
            _disableText.setString(str);
            font.destory();
        }
            break;
    }

    setTop(top);
    setLeft(left);
}

void CzhEaglUIButton::setTitleImageByPNG(const char* path,EzhEaglBtnState bs)
{
    switch (bs) {
        case ezhEaglBtnStateNor:
            _norImg.setBackgroundImageByPNG(path);
            break;
        case ezhEaglBtnStateHight:
            _hightImg.setBackgroundImageByPNG(path);
            break;
        case ezhEaglBtnStateSelect:
            _selectImg.setBackgroundImageByPNG(path);
            break;
        case ezhEaglBtnStateDisable:
            _disableImg.setBackgroundImageByPNG(path);
            break;
    }
}

void CzhEaglUIButton::setTitleImageByJPG(const char* path,EzhEaglBtnState bs)
{
    switch (bs) {
        case ezhEaglBtnStateNor:
            _norImg.setBackgroundImageByJPG(path);
            break;
        case ezhEaglBtnStateHight:
            _hightImg.setBackgroundImageByJPG(path);
            break;
        case ezhEaglBtnStateSelect:
            _selectImg.setBackgroundImageByJPG(path);
            break;
        case ezhEaglBtnStateDisable:
            _disableImg.setBackgroundImageByJPG(path);
            break;
    }
}

void CzhEaglUIButton::setTitleColor(float r,float g,float b,EzhEaglBtnState bs)
{
    switch (bs) {
        case ezhEaglBtnStateNor:
            _norText.setFontColor(r, g, b);
            break;
        case ezhEaglBtnStateHight:
            _hightText.setFontColor(r, g, b);
            break;
        case ezhEaglBtnStateSelect:
            _selectText.setFontColor(r, g, b);
            break;
        case ezhEaglBtnStateDisable:
            _disableText.setFontColor(r, g, b);
            break;
    }
}
void CzhEaglUIButton::setTitlteSize(float s,EzhEaglBtnState bs)
{
    
    switch (bs) {
        case ezhEaglBtnStateNor:
            setTitle(_norText.getString(), bs,_norFontname.c_str(),s);
            break;
        case ezhEaglBtnStateHight:
            setTitle(_hightText.getString(), bs,_hightFontname.c_str(),s);
            break;
        case ezhEaglBtnStateSelect:
            setTitle(_selectText.getString(), bs,_selectFontname.c_str(),s);
            break;
        case ezhEaglBtnStateDisable:
            setTitle(_disableText.getString(), bs,_disableFontname.c_str(),s);
            break;
    }
}

void CzhEaglUIButton::setSelect(BOOL b)
{
    selected=b;
}

void CzhEaglUIButton::reader()
{
    CzhEaglUIView::reader();
    
    switch (state) {
        case ezhEaglBtnStateNor:
            if (selected) {
                state=ezhEaglBtnStateSelect;
                goto __jumpSelect;
            }
            _norImg.reader();
            _norText.reader();
            
            break;
            
        case ezhEaglBtnStateHight:
            _hightImg.reader();
            _hightText.reader();
            
            break;
            
        case ezhEaglBtnStateSelect:
        __jumpSelect:
            _selectImg.reader();
            _selectText.reader();
            
            break;
            
        case ezhEaglBtnStateDisable:
            _disableImg.reader();
            _disableText.reader();
            
            break;
    }
  
}

//事件检测
CzhEaglUIView* CzhEaglUIButton::eventDown(TzhEaglLine* linp)
{
    CzhEaglUIView* vi;
    vi=CzhEaglUIView::pickUp(linp);
    if (vi) {
        state=ezhEaglBtnStateHight;
        active=true;
    }
    else
    {
        active=false;
    }
    return vi;
}

CzhEaglUIView* CzhEaglUIButton::eventUp(TzhEaglLine* linp)
{
    state=ezhEaglBtnStateNor;
    return CzhEaglUIView::pickUp(linp);
}