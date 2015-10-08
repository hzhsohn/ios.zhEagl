//
//  zhOpenglEs
//
//  Created by han on 13-7-2.
//  Copyright (c) 2013年 Han.zhihong. All rights reserved.
//
//  Blog
//  http://www.hanzhihong.cn
//

#ifndef __zhEaglGLMath__H__
#define __zhEaglGLMath__H__

#ifdef __cplusplus
extern "C"{
#endif

#include <math.h>

#define M_PI       3.14159265358979323846
#define	DegreesToRadians(x) ((x) * M_PI / 180.0)
#define	RadiansToDegrees(x) ((x) * 180.0 / M_PI)
#define	Norm(X, Y, Z) (sqrt((X)*(X) + (Y)*(Y) + (Z)*(Z)))
#define Sign(X) ((X < 0.) ? -1 : ((X == 0.) ? 0 : 1))
#define Clamp(X, A, B) ((X < A) ? A : ((X > B) ? B : X))

//STRUCTURES:
typedef struct _TzhEaglSize {
    float width;
    float height;
}TzhEaglSize;

//二维方块
typedef struct _TzhEaglRect {
    float x;
    float y;
    float width;
    float height;
}TzhEaglRect;

//RGB颜色
typedef struct _TzhEaglColorRGB{
    float r;
    float g;
    float b;
}TzhEaglColorRGB;

//RGBA颜色
typedef struct _TzhEaglColorRGBA{
    float r;
    float g;
    float b;
    float a;
}TzhEaglColorRGBA;

//二维空间 点 向量
typedef struct _TzhEaglPoint2{
    float x;
    float y;
}TzhEaglPoint2,TzhEaglVector2,Point2, Vector2;

//三维空间 点 向量
typedef struct _TzhEaglPoint3{
    float x;
    float y;
    float z;
}TzhEaglPoint3,TzhEaglVector3,Point3, Vector3;

//四维空间 点
typedef struct _TzhEaglPoint4{
    float x;
    float y;
    float z;
    float w;
}TzhEaglPoint4,TzhEaglVector4,Point4, Vector4;

//三维空间 线
typedef struct _TzhEaglLine{
    TzhEaglPoint3 p1;
    TzhEaglPoint3 p2;
    TzhEaglVector3 direct;
}TzhEaglLine,Line;

//三维空间 矩形
typedef struct _TzhEaglRectangle{
    TzhEaglPoint3 leftTop;
    TzhEaglPoint3 leftButtom;
    TzhEaglPoint3 rightButtom;
    TzhEaglPoint3 rightTop;
    float  width;
    float  length;
    TzhEaglVector3 normalVec;
}TzhEaglRectangle,Rectangle;

//三维空间 三角形
typedef struct _TzhEaglTriangle{
    TzhEaglPoint3 top;
    TzhEaglPoint3 leftButtom;
    TzhEaglPoint3 rightButtom;
    TzhEaglVector3 normalVec;
}TzhEaglTriangle,Triangle;
// 4 * 4 矩阵下标
typedef enum {
	kIndice_x1 = 0,
	kIndice_y1,
	kIndice_z1,
	kIndice_w1,
	
	kIndice_x2,
	kIndice_y2,
	kIndice_z2,
	kIndice_w2,
	
	kIndice_x3,
	kIndice_y3,
	kIndice_z3,
	kIndice_w3,
	
	kIndice_x4,
	kIndice_y4,
	kIndice_z4,
	kIndice_w4,
	
	kNumMatrixIndices
} MatrixIndex;

//STRUCTURES:

/* A 4x4 matrix */
typedef float TzhEaglMatrix[kNumMatrixIndices];
typedef TzhEaglMatrix Matrix;
typedef float* MatrixPtr;
typedef MatrixPtr TzhEaglMatrixPtr;

//FUNCTION PROTOTYPES:
//点  线  矩阵变换   矩阵相关函数
void MatrixCopy(const MatrixPtr m, MatrixPtr res);
void   MatrixReset(MatrixPtr M);
Point3 Point3TransformFromModelViewToModelView(Point3 v, Matrix m1, Matrix m2);
Point3 Point3Transform(Point3 v, Matrix m);
Point4 Point4TransformFromModelViewToModelView(Point4 v, Matrix m1, Matrix m2);
Point3 Point3Normalize(Point3 v1);
float Point3DotProduct(Point3 v1, Point3 v2);
Point3 Point3CrossProduct(Point3 v1, Point3 v2);

//创建函数
void MakeRotationPoint3(float rX, float rY, float rZ,TzhEaglPoint3* v);
void TransformPoint4_Copy(MatrixPtr m, TzhEaglPoint4* v, TzhEaglPoint4* res);
void MakeTransformationMatrix(float rX, float rY, float rZ, float tX, float tY, float tZ,MatrixPtr matrix);
void MakeTransformationMatrixFromVec2Vec(const TzhEaglVector3* fromVec,const TzhEaglVector3* toVec,const float offsetX,const float offsetY, const float offsetZ,MatrixPtr matrix);


//求两向量 之间的 夹角  和角度
void MakePoint3RotationAxis(TzhEaglPoint3* vSrc, TzhEaglPoint3* vDst,TzhEaglPoint3* outAxis);
void MakePoint3RotationAngle(TzhEaglPoint3* vSrc, TzhEaglPoint3* vDst,float* outAngle);

//将矩阵反转
void TransposeMatrix_Copy(MatrixPtr m, MatrixPtr res);
//点 ＊ 矩阵
void MatrixMultByPoint3(const MatrixPtr m, const TzhEaglPoint3* v, TzhEaglPoint3* res);
//矩阵*四元
void MatrixMultByQuaternion(const MatrixPtr m, const TzhEaglPoint4* v, TzhEaglPoint4* res);

//两个矩阵相乘
void MatrixMultByMatrix(const MatrixPtr m1, const MatrixPtr m2, MatrixPtr res);
//两个矩阵相乘,这个函数m2不能与res相同
void MatrixMultByMatrixNoCopy(const MatrixPtr m1, const MatrixPtr m2, MatrixPtr res);

//矩阵行列式
float Matrix4Det(Matrix m);
/***
 *功能 ： 计算矩阵的行列式
 *参数 ： ＊p ： 指向矩阵数组的指针
 numofrow ： 矩阵的行数
 *******/
float _Matrix_Det(float *p, int numOfRow);

/***
 *功能：创造一个3维空间正交坐标系
 *参数： pVx : 接收x轴方向向量
 pVy : y轴方向向量
 outMatrix : 需要施加变换的矩阵
 *注意：z轴方向向量通过x，y轴计算而来；
 当y轴方向向量会重新计算，保证 正交
 *********/
void Make3DCoordSystemWith2Vec(const TzhEaglVector3* pVx, const TzhEaglVector3* pVy, Matrix outMatrix);
/***
 *功能 ： 平移三维坐标系 矩阵
 *参数 ： Matrix :需要施加变换的矩阵
 x, y, z : 分别向x，y， z轴方向平移的量
 *********/
void Transfort3DCoordSystem(Matrix res, float x, float y, float z);
/***
 *功能 ： 制造旋转矩阵——绕任意轴旋转
 *参数 ： ［out］matrix ： 待制造的矩阵
 angle  ： 旋转角度
 vX, vY,vZ : 分别表示中轴线向量的 x， y， z轴分量
 注意 ： 算法思想来源于 ： http://blog.csdn.net/tan625747/article/details/5523728
 *****/
void MakeRotatefMatrix( float angle, float vX, float vY, float vZ,Matrix outMatrix);

//求逆
void Matrix4Reverse(Matrix m, Matrix res);

//四维空间向量乘以矩阵
void Vector4MultMatrix4(const TzhEaglVector4* v, const MatrixPtr m, TzhEaglVector4* out);

/***
 *功能 ： 对矩形做 平移，旋转等变换
 *参数 ：
 rect ： 源矩形
 M : 施加变换的矩阵
 [out]outRect ： 变换后的矩阵
 *****/
void RectangleMultMatrix(const TzhEaglRectangle* rect,TzhEaglMatrix M,TzhEaglRectangle* outRect);

/***
 *功能   : 对矩形做 平移，旋转等变换
 *参数
 rect   :源矩形
 xyz    :向量
 [out]outRect : 变换后的矩阵
 *****/
void RectangleMultDirect(const TzhEaglRectangle* rect, float x, float y, float z,TzhEaglRectangle* outRect);

//制造一个3维空间 坐标系 以pVx向量为主（当 与pvy不垂直时，会改变pvy的方向  z轴方向根据 x y轴计算而来 ）
void make3DCoorSystem(const TzhEaglVector3* pVx, const TzhEaglVector3* pVy, float offsetX, float offsetY, float offsetZ, Matrix outMatrix);

//创造一个3维空间坐标系 以x轴为主
void make3DCoordSystemByPoint(const TzhEaglPoint3* originPoint, const TzhEaglPoint3* Xaxis, const TzhEaglPoint3* Yaxis,Matrix outMatrix);
void MakeTranslation(float offsetX, float offsetY, float offsetZ, Matrix matrix);

//打印矩阵
void printMatrix4(Matrix m);

//常用 点 向量操作
Point3 Point3Make(float x, float y, float z);
Point3 Point3Add(Point3 p1, Vector3 p2);
Point3 Point3Sub(Point3 p1, Point3 p2);
Point3 Point3Mult(Point3 p1, float l);
int Point3EqualsPoint3(Point3 p1, Point3 p2);
float Point3Norm(Point3 p);

/* Point4 */
Point4 Point4Make(float x, float y, float z, float w);
Point4 Point4Mult(Point4 p1, float l);

float distanceOfPoint(const TzhEaglPoint3* p1,const TzhEaglPoint3* p2);
float DotOf2Vector(const TzhEaglVector3* v1,const TzhEaglVector3* v2);
float ValueOfVector(const TzhEaglVector3* v );
float AeraOf2Vector(const TzhEaglVector3* v1, const TzhEaglVector3* v2);
TzhEaglVector3 crossOf2Vector( const TzhEaglVector3* v1,const TzhEaglVector3* v2);

//向量 归一化
void  normalOfVector(TzhEaglVector3* v);

//求平面法向量
TzhEaglVector3 getNormalVectorOfPlane(const TzhEaglRectangle* p );

//判断两向量是否平行
int   isParallelOf2Vector(const TzhEaglVector3* v1, const TzhEaglVector3* v2);

//判断两向量是否垂直
int   isVerticalOf2Vector(const TzhEaglVector3* v1, const TzhEaglVector3* v2);

//判断一条直线是否在一个矩形
int isInsidePlane(const TzhEaglLine* l, const TzhEaglRectangle* p );

//点到直线的距离
float distanceOfPoint2Line(const TzhEaglLine* l, const TzhEaglPoint3* p);

/***
 *功能 ： 判断一条射线是否穿越一个三角形
 *参数 ： l : 直线指针
 rect : 矩形指针
 ［out］pointOnTriangle : 直线与平面的交点
 *返回
 0 ： 不相交
 否则 ： 射线起点到碰撞平面的距离
 *****/
float isLineCrossTriangle(const TzhEaglLine* l , const TzhEaglTriangle* triangle, TzhEaglPoint3* pointOnTriangle);

/***
 *功能 ： 判断一条射线是否穿越一个空间矩形
 *参数 ： l : 直线指针
 rect : 矩形指针
 ［out］pointrectangle : 直线与平面的交点
 *返回
 0 ： 不相交
 否则 ： 射线起点到碰撞平面的距离
 *****/
float isLineCrossRectangle(const TzhEaglLine* l, const TzhEaglRectangle* rect,  TzhEaglPoint3* pointOnRectangle);

Vector3  vector3Transfort(TzhEaglVector3* v, float x, float y, float z);
Vector3  vector3MadeBy2Point(const TzhEaglPoint3* p1, const TzhEaglPoint3* p2);

TzhEaglPoint3 Point3Transform_w(const TzhEaglPoint3* p, Matrix m);

/* rectangle */
TzhEaglRectangle zhEaglRectangleMake(Point3 leftTop, Point3 leftButtom, Point3 rightButtom);
/* Triangle*/
TzhEaglTriangle zhEaglTriangleMake(Point3 top, Point3 leftButtom, Point3 rightButtom);
TzhEaglLine zhEaglLineMake(Point3 p1, Point3 P2);
    
//生成函数
TzhEaglRect zhEaglRectMake(float x, float y, float width, float height);
TzhEaglSize zhEaglSizeMake(float width, float height);
TzhEaglColorRGB zhEaglColorRGBMake(float r,float g,float b);
TzhEaglColorRGBA zhEaglColorRGBAMake(float r,float g,float b,float a);

#ifdef __cplusplus
}
#endif
#endif