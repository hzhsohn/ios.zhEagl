#include "CzhEaglImage.h"


CzhEaglImage::CzhEaglImage()
{
    _textureID=0;
}

CzhEaglImage::~CzhEaglImage()
{
    
}

int CzhEaglImage::next_p2 (int a )
{
    int rval=1;
    // rval<<=1 Is A Prettier Way Of Writing
    rval*=2;
    while(rval<a)
        rval<<=1;
    return rval;
}

BOOL CzhEaglImage::loadImage(const void* data ,TzhEaglTexture2DFormat pixelFormat,int width ,int height)
{
    _piexlSize.width = width;
    _piexlSize.height = height;
    _pixelFormat = pixelFormat;
    
    _textureID=gluLoadTexture(data ,pixelFormat,width ,height);
    if (_textureID) {
        return TRUE;
    }
    return FALSE;
}

GLuint CzhEaglImage::getTextureID()
{
    return _textureID;
}

void CzhEaglImage::deleteTexture()
{
    if(_textureID)
	{
        glDeleteTextures(1, &_textureID);
        _textureID=0;
    }
}

BOOL CzhEaglImage::loadPNG(const char*path,BOOL autoGLImg)
{
    CzhEaglExpPng png;
    int byteNum;
    if(0==png.loadFile(path))
    {
        TzhEaglTexture2DFormat format;
        format=ezhEaglImg_Automatic;
        switch (png.flag) {
            case ezhEaglExpPngFlag_No_Alpha:
            {
                byteNum=3;
                switch (png.bit_depth) {
                    case 8:
                        format=ezhEaglImg_RGB888;
                        
                        break;
                    case 16:
                        format=ezhEaglImg_RGB565;
                        break;
                }
                
            }
                break;
                
            case ezhEaglExpPngFlag_Have_Alpha:
            {
                byteNum=4;
                switch (png.bit_depth) {
                    case 8:
                        format=ezhEaglImg_RGBA8888;
                        break;
                    case 16:
                        format=ezhEaglImg_RGBA5551;
                        break;
                }
            }
                break;
        }
        
        if (autoGLImg) {
            int w;
            int h;
            w=next_p2(png.width);
            h=next_p2(png.width);
            if (png.width==w && png.height==h) {
                goto _not_need;
            }
            
            GLubyte* e_data = (GLubyte*)malloc(w * h *byteNum);
            memset(e_data, 0, w * h*byteNum);

            for(int j=0; j< h;j++)
            {
                for(int i=0; i< w; i++)
                {
                    int tmp1=i*byteNum+w*byteNum*j;
                    int tmp2=i*byteNum+png.width*byteNum*j;
                    for (int k=0; k<byteNum; k++) {
                        e_data[tmp1+k] = (i<png.width && j<png.height)?png.data[tmp2+k]:0;
                    }
                }
            }
           
            loadImage(e_data, format, w, h);
            free(e_data);
            e_data=NULL;
        }
        else
        {
        _not_need:
            loadImage(png.data, format, png.width, png.height);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CzhEaglImage::loadJPG(const char*path,BOOL autoGLImg)
{
    CzhEaglExpJpg jpg;
    if(0==jpg.loadFile(path))
    {
        if (autoGLImg) {
            int w;
            int h;
            w=next_p2(jpg.width);
            h=next_p2(jpg.width);
            if (jpg.width==w && jpg.height==h) {
                goto _not_need;
            }
            
            GLubyte* e_data = (GLubyte*)malloc(w * h *3);
            memset(e_data, 0, w*h*3);
            
            for(int j=0; j< h;j++)
            {
                for(int i=0; i< w; i++)
                {
                    int tmp1=i*3+w*3*j;
                    int tmp2=i*3+jpg.width*3*j;
                    for (int k=0; k<3; k++) {
                        e_data[tmp1+k] = (i<jpg.width && j<jpg.height)?jpg.data[tmp2+k]:0;
                    }
                }
            }
            
            loadImage(e_data, ezhEaglImg_RGB888, w, h);
            free(e_data);
            e_data=NULL;
        }
        else
        {
        _not_need:
            loadImage(jpg.data, ezhEaglImg_RGB888, jpg.width, jpg.height);
        }
        return TRUE;
    }
    return FALSE;
}
