//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#ifndef __zhEaglGLfunc__H__
#define __zhEaglGLfunc__H__


#include "zhEaglHeader.h"
#include "zhEaglInternal.h"

#ifdef __cplusplus
extern "C"{
#endif



void normalize(GLfloat v[3]);
void cross(GLfloat v1[3], GLfloat v2[3], GLfloat result[3]);
void __gluMakeIdentityf(GLfloat m[16]);
int __gluInvertMatrixd(const GLfloat m[16], GLfloat invOut[16]);
void __gluMultMatrixVecd(const GLfloat matrix[16], const GLfloat in[4],
                         GLfloat out[4]);
void __gluMultMatricesd(const GLfloat matrix1[16], const GLfloat matrix2[16], GLfloat out[16]);

//辅助函数
void printArray(GLfloat *point, GLuint count);

//重载函数
void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
			   GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy,
			   GLfloat upz);

int gluUnProject(GLfloat winx, GLfloat winy, GLfloat winz,
                 const GLfloat modelMatrix[16],
                 const GLfloat projMatrix[16],
                 const GLint viewport[4],
                 GLfloat *objx, GLfloat *objy, GLfloat *objz);

void gluPerspective(GLfloat fieldOfView,GLfloat aspect,GLfloat zNear, GLfloat zFar);

#define glOrtho glOrthof

    

typedef enum _TzhEaglTexture2DFormat{
    ezhEaglImg_Automatic = 0,
    ezhEaglImg_RGBA8888,
    ezhEaglImg_RGBA4444,
    ezhEaglImg_RGBA5551,
    ezhEaglImg_RGB565,
    ezhEaglImg_RGB888,
    ezhEaglImg_L8,
    ezhEaglImg_A8,
    ezhEaglImg_LA88,
    ezhEaglImg_RGB_PVRTC2,
    ezhEaglImg_RGB_PVRTC4,
    ezhEaglImg_RGBA_PVRTC2,
    ezhEaglImg_RGBA_PVRTC4
} TzhEaglTexture2DFormat;
/*
 独立的纹理ID绑定函数
 用于绑定数据到纹理里面
 这函数与类里面其它变量不相关
 */
GLuint gluLoadTexture(const void* data ,TzhEaglTexture2DFormat pixelFormat,int width ,int height);


#ifdef __cplusplus
}
#endif

#endif
