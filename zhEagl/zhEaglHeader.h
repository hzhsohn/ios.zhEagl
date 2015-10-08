#ifndef __zhEaglGLHeader__H__
#define __zhEaglGLHeader__H__

static const char* zhEgal_default_fontname="Hiragino Sans GB W3.otf";
static const short zhEgal_default_fontsize=17;


#ifdef __APPLE__
#import <UIKit/UIKit.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/EAGLDrawable.h>

//
static const char* zhLocalPath()
{
    NSString* str=[[NSBundle mainBundle] resourcePath];
    str=[str stringByAppendingString:@"/"];
    return [str UTF8String];
}


static wchar_t* zhCharToWchar(NSString* str,wchar_t* dst_buf)
{
    // author: Han.zhihong 
    int i;
    unichar *uu;
    int n;
    
    n=[str length]+2;
    uu=(unichar*)malloc(n*sizeof(unichar));
    [str getCharacters:uu];
    
    for(i=0;i<[str length];i++)
    {
        dst_buf[i]=uu[i];
    }
    dst_buf[i]=0;
    
    free(uu);
    uu=NULL;
    return dst_buf;
}
#endif

#ifdef _WIN32
#include <Windows.h>
//#include <afx.h>

#include <gl/glut.h>
#include <gl/gl.h> 
#include <gl/glu.h>

#endif

//÷ÿ∂®“Â
#define localPath()                     zhLocalPath()
#define charToWchar(ns_str,dst_buf)     zhCharToWchar(ns_str,dst_buf)

#endif