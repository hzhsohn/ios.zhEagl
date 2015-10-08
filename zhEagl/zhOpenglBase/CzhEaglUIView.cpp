#include "CzhEagluiView.h"



CzhEaglUIView::CzhEaglUIView()
{
    _vertex[0]=-0.5f;_vertex[1]=0.5f;//top left
    _vertex[2]=-0.5f;_vertex[3]=-0.5f;//bottom left
    _vertex[4]=0.5f;_vertex[5]=-0.5f;//bottom right
    _vertex[6]=0.5f;_vertex[7]=0.5f;//top right
    
    _texCoodr[0]=0.0f;_texCoodr[1]=0.0f;//bottom top
    _texCoodr[2]=0.0f;_texCoodr[3]=1.0f;//top left of square
    _texCoodr[4]=1.0f;_texCoodr[5]=1.0f;//top right of square
    _texCoodr[6]=1.0f;_texCoodr[7]=0.0f;//bottom right of square
    
    left=0;
    top=0;
    width=100;
    height=100;
    
    _x=0;
    _y=0;
    
    memset(&backgroundImage, 0, sizeof(CzhEaglImage));
    
    backgroundColor.r=1;
    backgroundColor.g=1;
    backgroundColor.b=1;
    backgroundColor.a=1;
}

CzhEaglUIView::~CzhEaglUIView()
{
 
}

void CzhEaglUIView::setLeft(int l)
{
    left=l;
}
void CzhEaglUIView::setTop(int t)
{
    top=t;
}
void CzhEaglUIView::setWidth(int w)
{
    width=w;
}
void CzhEaglUIView::setHeight(int h)
{
    height=h;
}
int CzhEaglUIView::getLeft()
{
    return left;
}
int CzhEaglUIView::getTop()
{
    return top;
}
int CzhEaglUIView::getWidth()
{
    return width;
}
int CzhEaglUIView::getHeight()
{
    return height;
}

BOOL CzhEaglUIView::setBackgroundImage(const void* data ,TzhEaglTexture2DFormat pixelFormat,int width ,int height)
{
    backgroundImage.deleteTexture();
    return backgroundImage.loadImage(data, pixelFormat, width, height);
}

BOOL CzhEaglUIView::setBackgroundImageByPNG(const char* imgPath)
{
    backgroundImage.deleteTexture();
    return backgroundImage.loadPNG(imgPath,TRUE);
}
BOOL CzhEaglUIView::setBackgroundImageByJPG(const char* imgPath)
{
    backgroundImage.deleteTexture();
    return backgroundImage.loadJPG(imgPath,TRUE);
}

void CzhEaglUIView::reader()
{
    //隐藏----------------------------
    if (hidden) { return; }
    if (0==alpha) { return; }
    if (0==backgroundColor.a) { return; }
    
    //绘制----------------------------
    glPushMatrix();
    
    _x=left+(width>>1);
    _y=top+(height>>1);
    glTranslatef(_x, _y, 0);

    
    if (angle) {
        glRotatef(angle, 0, 0, 1);
    }
    
    glScalef(width, height, 0);
    
    //先启用纹理功能,再录入图片里的坐标
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, backgroundImage.getTextureID());
    glTexCoordPointer(2, GL_FLOAT, 0, &_texCoodr);
    
    glEnable(GL_BLEND);//启用融合效果
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);//设置融合方式
    //透明度
    glColor4f(backgroundColor.r,
                  backgroundColor.g,
                  backgroundColor.b,
                  alpha*backgroundColor.a);
    //平面
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, _vertex);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glColor4f(1, 1, 1, 1);//恢复透明度不影响别的模型
    glDisable(GL_BLEND); //关闭融合效果
    
    //关闭纹理
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glPopMatrix();
}

void CzhEaglUIView::setBackgroundColor(float r ,float g ,float b)
{
    backgroundColor.r=r;
    backgroundColor.g=g;
    backgroundColor.b=b;
}
void CzhEaglUIView::setBackgroundColor(float r ,float g ,float b ,float a)
{
    backgroundColor.r=r;
    backgroundColor.g=g;
    backgroundColor.b=b;
    backgroundColor.a=a;
}
void CzhEaglUIView::setBackgroundColor(TzhEaglColorRGB rgb)
{
    backgroundColor.r=rgb.r;
    backgroundColor.g=rgb.g;
    backgroundColor.b=rgb.b;
}
void CzhEaglUIView::setBackgroundColor(TzhEaglColorRGBA rgba)
{
    backgroundColor.r=rgba.r;
    backgroundColor.g=rgba.g;
    backgroundColor.b=rgba.b;
    backgroundColor.a=rgba.a;
}
void CzhEaglUIView::setBackgroundColorAlpha(float a)
{
    backgroundColor.a=a;
}

TzhEaglRectangle CzhEaglUIView::getRectangle()
{
    TzhEaglRectangle rect;
    TzhEaglPoint3 p1,p2,p3;
    
    float l=angle*M_PI/180;
    
    TzhEaglMatrix tm={
        1,        0,  0, 0,
        0,        1,  0, 0,
        0,        0,  0, 0,
        (float)_x,   (float)_y,  0, 1
    };
    TzhEaglMatrix sm={
        (float)width,    0,  0, 0,
        0,    (float)height,  0, 0,
        0,         0,  0, 0,
        0,         0,  0, 1
    };
    TzhEaglMatrix rm={
        cosf(l),   sinf(l),  0, 0,
        -sinf(l),  cosf(l),  0, 0,
        0,             0,  0, 0,
        0,             0,  0, 1
    };
    
    p1=Point3Make(_vertex[0], _vertex[1], 0);
    p2=Point3Make(_vertex[2], _vertex[3], 0);
    p3=Point3Make(_vertex[4], _vertex[5], 0);
    rect=zhEaglRectangleMake(p1, p2, p3);
    
    RectangleMultMatrix(&rect, sm, &rect);
    RectangleMultMatrix(&rect, rm, &rect);
    RectangleMultMatrix(&rect, tm, &rect);
    return rect;
}
void CzhEaglUIView::setRect(TzhEaglRect rect)
{
    width=rect.width;
    height=rect.height;
    left=rect.x;
    top=rect.y;
}
TzhEaglRect CzhEaglUIView::getRect()
{
    TzhEaglRectangle rect= getRectangle();
    return zhEaglRectMake(rect.leftButtom.x,
                      rect.leftButtom.y,
                      rect.width,
                      rect.length);
}


//检测是否被射线选中
CzhEaglUIView* CzhEaglUIView::pickUp(TzhEaglLine* linp)
{
    CzhEaglUIView* ret = NULL;
    
    if (linp==NULL) {
        return NULL;
    }
    
    if (enable) {
        float depth = lineRectangleInside(linp,getRectangle());
        if (depth) {
            ret = this;
            _depth=depth;
        }else{
            _depth=NSIntegerMax;
        }
        return ret;
    }
    return NULL;
}