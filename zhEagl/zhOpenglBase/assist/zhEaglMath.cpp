//
//  Math.c
//
//
//  Created by WenXiong on 11-7-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#include <malloc.h>
#include <stdio.h>
#include "zhEaglMath.h"
#include "string.h"
#define	MatrixGetPoint31(m)	((TzhEaglPoint4*) &(m)[kIndice_x1])
#define	MatrixGetPoint32(m)	((TzhEaglPoint4*) &(m)[kIndice_x2])
#define	MatrixGetPoint33(m)	((TzhEaglPoint4*) &(m)[kIndice_x3])
#define	MatrixGetPoint34(m)	((TzhEaglPoint4*) &(m)[kIndice_x4])
/***
 *功能 ： 判断一点是否在一个以三个点组成的三角形内
 *参数 ： px : 待判断的点
 p1, p2, p3 :  指向三角形三个定点的坐标
 *返回 ： 0 ： 不在三角形能
 1 ： 在三角形内
 *****/
int _isPointInTriangle(const TzhEaglPoint3* px, const TzhEaglPoint3* p1,const TzhEaglPoint3* p2,const TzhEaglPoint3* p3){
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;

    v1.x = px->x - p1->x;
    v1.y = px->y - p1->y;
    v1.z = px->z - p1->z;

    v2.x = px->x - p2->x;
    v2.y = px->y - p2->y;
    v2.z = px->z - p2->z;

    v3.x = px->x - p3->x;
    v3.y = px->y - p3->y;
    v3.z = px->z - p3->z;
 
    normalOfVector(&v1);//单位化
    normalOfVector(&v2);//单位化
    normalOfVector(&v3);//单位化
    
    float cosValue1 = DotOf2Vector(&v1, &v2);
    float cosValue2 = DotOf2Vector(&v2, &v3);
    float cosValue3 = DotOf2Vector(&v3, &v1);
    
    float detal =acosf(cosValue1) + acosf(cosValue2) + acosf(cosValue3);
    //printf("[_isPointInTriangle] detal = %f \n", detal);
    if(detal <2 * M_PI + 0.0001 && detal >2 * M_PI - 0.0001)
        return  1;
    else
        return 0;
}
/***
 *功能 ： 判断一条射线是否和一个三角形由焦点
 *参数 ： l : 指向一条射线的指针
 triangle ： 三角形指针
 ［out］pointOnTriangel ： 射线与三角形平面的焦点
 ＊返回 ： 0 ：没有焦点
 否则 ： 射线起点 到三角形的距离
 注意 ： 就算直线与三角形没有焦点，只要射线与三角形平面有焦点 就会返回pointOnTriangel。
 *****/
//判断一条直线是否 和三角形 有焦点
float _isLineCrossTriangle(const TzhEaglLine* l,const TzhEaglTriangle* triangle, TzhEaglPoint3* pointOnTriangel)
{
    if(l == NULL)return 0;
    if(DotOf2Vector(&l->direct, &triangle->normalVec) == 0)
        return 0 ;
    
    Vector3 direct = l->direct;
    Vector3 normalVec = triangle->normalVec;
    normalOfVector(&direct);
    normalOfVector(&normalVec);
    //printf("######################################\n");
    //printf("[_isLineCrossTriangle] : l->direct------>%f %f %f\n",direct.x, direct.y, direct.z );
    //printf("[_isLineCrossTriangle] : normalVec------>%f %f %f \n",normalVec.x, normalVec.y, normalVec.z);
    float d = DotOf2Vector(&normalVec, &triangle->leftButtom);
    float t = (d - DotOf2Vector(&normalVec , &l->p1)) / DotOf2Vector(&normalVec , &direct);//计算出碰撞时间 (单位速度下) = 距离
    //printf("[_isLineCrossTriangle] : t = %f\n", t);
    if(t < 0)  //方向相反
        return  0;
    else if(t > 0)
    {
        Point3 pointOnPlane ; //计算出射线与平面的交点
            pointOnPlane.x = l->p1.x + t * direct.x;
            pointOnPlane.y = l->p1.y + t * direct.y;
            pointOnPlane.z = l->p1.z + t * direct.z;

        //printf("[_isLineCrossTriangle] : the point on plane ------>\nx = %f, y = %f, z = %f\n", pointOnPlane.x, pointOnPlane.y, pointOnPlane.z);
        if(pointOnTriangel != NULL){
            pointOnTriangel->x = pointOnPlane.x;
            pointOnTriangel->y = pointOnPlane.y;
            pointOnTriangel->z = pointOnPlane.z;
        }
        
        //判断点是否在平面内
        if(_isPointInTriangle(&pointOnPlane, &triangle->top, &triangle->leftButtom, &triangle->rightButtom))
            return t;//返回 到焦点 的距离
        else
            return 0;
    }
    //printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    return  0 ;
}
float isLineCrossTriangle(const TzhEaglLine* l , const TzhEaglTriangle* triangle, TzhEaglPoint3* pointOnTriangle){
    return _isLineCrossTriangle(l, triangle, pointOnTriangle);
}

/***
 *功能 ： 判断一条射线是否穿越一个空间矩形
 *参数 ： l : 直线指针
 rect : 矩形指针
 ［out］pointrectangle : 直线与平面的交点
 *返回
 0 ： 不相交
 否则 ： 射线起点到碰撞平面的距离
 *****/
float isLineCrossRectangle(const TzhEaglLine* l, const TzhEaglRectangle* rect, TzhEaglPoint3* pointOnRectangle){
    TzhEaglTriangle tr1 = zhEaglTriangleMake(rect->leftTop, rect->leftButtom, rect->rightButtom);
    TzhEaglTriangle tr2 = zhEaglTriangleMake(rect->leftTop, rect->rightButtom, rect->rightTop);
    /*printf("[isLineCrossRect] : tr1 normal---->%f %f %f\n", tr1.normalVec.x, tr1.normalVec.y, tr1.normalVec.z);
     printf("[isLineCrossRect] : tr2 normal---->%f %f %f\n", tr2.normalVec.x, tr2.normalVec.y, tr2.normalVec.z);
     printf("[isLineCrossRect] : rect normal----->%f %f %f\n", rect->normalVec.x, rect->normalVec.y, rect->normalVec.z);*/
    tr1.normalVec = tr2.normalVec = rect->normalVec;
    float t1, t2;
    t1 = isLineCrossTriangle(l, &tr1, pointOnRectangle);
    t2 = isLineCrossTriangle(l, &tr2, pointOnRectangle);
    if( t1 || t2)
        return t1 > 0 ? t1 : t2;
    else
        return 0;
}
/* rectangle  maker */
TzhEaglRectangle zhEaglRectangleMake(Point3 leftTop, Point3 leftButtom, Point3 rightButtom){
    Rectangle r ;
	float x, y, z;
	Vector3 v1;
    Vector3 v2;

    r.leftTop = leftTop,
    r.leftButtom = leftButtom,
    r.rightButtom = rightButtom;

    //计算第四个坐标点    
    x = rightButtom.x - leftButtom.x + leftTop.x;
    y = rightButtom.y - leftButtom.y + leftTop.y;
    z = rightButtom.z - leftButtom.z + leftTop.z;
    r.rightTop = Point3Make(x, y, z);
    r.width = distanceOfPoint(&leftTop, &leftButtom);
    r.length = distanceOfPoint(&leftButtom, &rightButtom);

    v1.x = leftTop.x - leftButtom.x;
    v1.y = leftTop.y - leftButtom.y;
    v1.z = leftTop.z - leftButtom.z;

    v2.x = rightButtom.x - leftButtom.x;
    v2.y = rightButtom.y - leftButtom.y;
    v2.z = rightButtom.z - leftButtom.z;

    r.normalVec = crossOf2Vector(&v2, &v1);
    // normalOfVector(&r.normalVec);//单位化
    return  r;
}
/* Triangle  maker 三角形*/
TzhEaglTriangle zhEaglTriangleMake(Point3 top, Point3 leftButtom, Point3 rightButtom){
    Triangle t;
    Vector3 v1;
    Vector3 v2;

    t.top = top;
    t.leftButtom = leftButtom;
    t.rightButtom = rightButtom;

    v1.x = top.x - leftButtom.x;
    v1.y = top.y - leftButtom.y;
    v1.z = top.z - leftButtom.z;

    v2.x = rightButtom.x - leftButtom.x;
    v2.y = rightButtom.y - leftButtom.y;
    v2.z = rightButtom.z - leftButtom.z;

    t.normalVec = crossOf2Vector(&v2, &v1);
    //normalOfVector(&t.normalVec);
    return t;
}
//直线生产者
TzhEaglLine zhEaglLineMake(Point3 p1, Point3 p2){
    Line l;
    l.p1 = p1;
    l.p2 = p2;

    l.direct.x = p2.x - p1.x;
    l.direct.y = p2.y - p1.y;
    l.direct.z = p2.z - p1.z;

    return l;
}
//两点之间距离
float inline distanceOfPoint(const TzhEaglPoint3* p1, const TzhEaglPoint3* p2)
{
    return sqrtf((p1->x - p2->x)*(p1->x - p2->x) + (p1->y - p2->y)*(p1->y - p2->y) + (p1->z - p2->z)*(p1->z - p2->z));
}
//两向量的乘积
float inline DotOf2Vector(const TzhEaglVector3* v1,const TzhEaglVector3* v2){
    double x1,x2,x3;
    double y1,y2,y3;
    x1 = v1->x; x2 = v1->y; x3 = v1->z;
    y1 = v2->x; y2 = v2->y; y3 = v2->z;
    return (x1 * y1 + x2 * y2 + x3 * y3);
    
}
//向量长短
float inline ValueOfVector(const TzhEaglVector3* v )
{
    double x, y, z;
    x = v->x;
    y = v->y;
    z = v->z;
    return sqrtf(x * x + y * y + z * z);
}
//两向量围成的面积
float inline AeraOf2Vector(const TzhEaglVector3* v1, const TzhEaglVector3* v2)
{
    TzhEaglVector3 v;
	v = crossOf2Vector(v1, v2);
    
    return ValueOfVector(&v );
}
//两向量法向量
TzhEaglVector3 inline crossOf2Vector( const TzhEaglVector3* v1,const TzhEaglVector3* v2){
    
    double x1,x2,x3;
    double y1,y2,y3;
    double k1,k2,k3;
    TzhEaglVector3 v;

    x1 = v1->x; x2 = v1->y; x3 = v1->z;
    y1 = v2->x; y2 = v2->y; y3 = v2->z;
    k1 = x2 * y3 - x3 * y2;
    k2 = y1 * x3 - x1 * y3;
    k3 = x1 * y2 - y1 * x2;

    v.x = k1;
    v.y = k2;
    v.z = k3;
    return v;
}
//向量 归一化
void inline normalOfVector(TzhEaglVector3* v){
    float value;
	value= ValueOfVector(v);
    if(value != 0){
        v->x /= value;
        v->y /= value;
        v->z /= value;
    }
}

Vector3 inline vector3Transfort(TzhEaglVector3* v, float x, float y, float z)
{
	Vector3 vv;
	vv.x=v->x + x;
	vv.y=v->y + y;
	vv.z=v->z + z;
    return vv;
}
Vector3 inline vector3MadeBy2Point(const TzhEaglPoint3* p1,const TzhEaglPoint3* p2){
    Vector3 vv;
	vv.x=p2->x - p1->x;
	vv.y=p2->y - p1->y;
	vv.z=p2->z - p1->z;
    return vv;
}

//求平面法向量
TzhEaglVector3 getNormalVectorOfPlane(const TzhEaglRectangle* p )
{
    float x1, x2, x3, y1, y2, y3;
    TzhEaglVector3 v1;
    TzhEaglVector3 v2;

    x1 = p->leftTop.x;
    x2 = p->leftTop.y;
    x3 = p->leftTop.z;
    y1 = p->leftButtom.x;
    y2 = p->leftButtom.y;
    y3 = p->leftButtom.z;

    v1.x = x1 - y1;
    v1.y = x2 - y2;
    v1.z = x3 - y3;

    x1 = p->leftButtom.x;
    x2 = p->leftButtom.y;
    x3 = p->leftButtom.z;
    y1 = p->rightButtom.x;
    y2 = p->rightButtom.y;
    y3 = p->rightButtom.z;

    v2.x = x1 - y1;
    v2.y = x2 - y2;
    v2.z = x3 - y3;
    return crossOf2Vector(&v1, &v2);
}

//判断两向量是否平行
int inline isParallelOf2Vector(const TzhEaglVector3* v1, const TzhEaglVector3* v2){
    TzhEaglVector3 v = crossOf2Vector(v1, v2);
    if(v.x == 0 && v.y == 0 && v.z == 0)
        return 1;
    else
        return 0;
}
//判断两向量是否垂直
int inline  isVerticalOf2Vector(const TzhEaglVector3* v1, const TzhEaglVector3* v2){
    return DotOf2Vector(v1, v2) == 0;
}

//判断一条直线是否在一个矩形
int isInsidePlane(const TzhEaglLine* l, const TzhEaglRectangle* p ){
    TzhEaglVector3 norv; //平面法线
    TzhEaglVector3 norm;
	TzhEaglVector3 lVec;
	float d;
	float t;

	norv = getNormalVectorOfPlane(p); //平面法线
    norm.x = norv.x;
    norm.y = norv.y;
    norm.z = norv.z;
    normalOfVector(&norm );//单位化
    
    lVec.x = l->p2.x - l->p1.x;
    lVec.y = l->p2.y - l->p1.y;
    lVec.z = l->p2.z - l->p1.z;
    normalOfVector(&lVec); //单位化

    if(isVerticalOf2Vector(&norv, &lVec) )//直线 与平面平行了，就不可能相交
    {
        return 0;
    }
    //根据 OpenGL-Nehe 碰撞检测提供的公式 计算向量和直线是否 可能相互碰撞
    d =fabsf(DotOf2Vector(&norm, &p->leftButtom)); //原点到平面的距离
    t = (d - fabsf(DotOf2Vector(&norm , &l->p1))) / fabsf((DotOf2Vector(&norm , &lVec)));//计算出碰撞时间 (单位速度下)
    if(t < 0)  //方向相反
        return  0;
    //
    else if(t > 0)
    {
        TzhEaglPoint3 pointOnPlane;//计算出射线与平面的交点
		TzhEaglLine l1;
        TzhEaglLine l2;
        TzhEaglLine l3;
        TzhEaglLine l4;
		float d1,d2,d3,d4,d12,d34;

		pointOnPlane.x = l->p1.x + t * lVec.x,
		pointOnPlane.y = l->p1.y + t * lVec.y,
		pointOnPlane.z = l->p1.z + t * lVec.z;

        //判断点是否在平面内
        l1.p1 = p->leftTop;
        l1.p2 = p->leftButtom;

        l2.p1 = p->leftButtom;
        l2.p2 = p->rightButtom;

        l3.p1 = p->rightButtom;
        l3.p2 = p->rightTop;

        l4.p1 = p->rightTop;
        l4.p2 = p->leftTop;

        d1 = distanceOfPoint2Line(&l1, &pointOnPlane);
        d2 = distanceOfPoint2Line(&l2, &pointOnPlane);
        d3 = distanceOfPoint2Line(&l3, &pointOnPlane);
        d4 = distanceOfPoint2Line(&l4, &pointOnPlane);
        d12 = distanceOfPoint2Line(&l1, &p->rightButtom);
        if( d1 + d3 -  d12 > 0.01)
            return 0;
        d34 = distanceOfPoint2Line(&l2, &p->leftTop);
        if(d2 + d4 -  d34 > 0.01)
            return 0;
    }
    return t;
}

//点到直线的距离
float distanceOfPoint2Line(const TzhEaglLine* l, const TzhEaglPoint3* p)
{
    TzhEaglVector3 direct;
    TzhEaglVector3 vec;
	float area;

    direct.x = l->p2.x - l->p1.x;
    direct.y = l->p2.y - l->p1.y;
    direct.z = l->p2.z - l->p1.z;

    vec.x = p->x - l->p1.x;
    vec.y = p->y - l->p1.y;
    vec.z = p->z - l->p1.z;

    area = AeraOf2Vector(&direct, &vec);
    return area / ValueOfVector(&direct);
}

//FUNCTION PROTOTYPES:
void _Matrix_Clear(MatrixPtr m)
{
	m[kIndice_x1] = 1.0;
	m[kIndice_y1] = 0.0;
	m[kIndice_z1] = 0.0;
	m[kIndice_w1] = 0.0;
	
	m[kIndice_x2] = 0.0;
	m[kIndice_y2] = 1.0;
	m[kIndice_z2] = 0.0;
	m[kIndice_w2] = 0.0;
	
	m[kIndice_x3] = 0.0;
	m[kIndice_y3] = 0.0;
	m[kIndice_z3] = 1.0;
	m[kIndice_w3] = 0.0;
	
	m[kIndice_x4] = 0.0;
	m[kIndice_y4] = 0.0;
	m[kIndice_z4] = 0.0;
	m[kIndice_w4] = 1.0;
}

void _Matrix_Copy(const MatrixPtr m, MatrixPtr res)
{
	memcpy(res, m, sizeof(Matrix));
}
/***
 *功能 ： 重置矩阵 为单位矩阵
 *参数 ： M : 需要重置的矩阵
 *****/
void MatrixReset(MatrixPtr M)
{
    _Matrix_Clear(M);
}
/***
 *功能 ： 制造 一个变换矩阵————沿着x，y，z轴方向旋转
 *参数 ： rX : 沿x轴旋转的角度（注意是 degree形式 ，比如 90度 就用90表示 而不是1／2PI）
 rY : 沿y轴旋转的角度
 rZ : 沿z轴旋转的角度
 [out]matrix : 待制造的变化矩阵
 *****/
void _Matrix_SetRotationFromAngles(MatrixPtr matrix, float rX, float rY, float rZ)
{
	float A, B, C, D, E, F;
	
	rX = DegreesToRadians(rX);//角度 －》pi
	rY = DegreesToRadians(rY);
	rZ = DegreesToRadians(rZ);
	
	A = (rX ? cos(rX) : 1.0);
	B = (rX ? sin(rX) : 0.0);
	C = (rY ? cos(rY) : 1.0);
	D = (rY ? sin(rY) : 0.0);
	E = (rZ ? cos(rZ) : 1.0);
	F = (rZ ? sin(rZ) : 0.0);
	
	matrix[kIndice_x1] = C * E;
	matrix[kIndice_y1] = B * D * E + A * F;
	matrix[kIndice_z1] = B * F - A * D * E;
	matrix[kIndice_w1] = 0.0;
	
	matrix[kIndice_x2] = -C * F;
	matrix[kIndice_y2] = A * E - B * D * F;
	matrix[kIndice_z2] = A * D * F + B * E;
	matrix[kIndice_w2] = 0.0;
	
	matrix[kIndice_x3] = D;
	matrix[kIndice_y3] = -B * C;
	matrix[kIndice_z3] = A * C;
	matrix[kIndice_w3] = 0.0;
	
	matrix[kIndice_x4] = 0.0;
	matrix[kIndice_y4] = 0.0;
	matrix[kIndice_z4] = 0.0;
	matrix[kIndice_w4] = 1.0;
}
//点 ＊ 矩阵
void MatrixMultByPoint3(const MatrixPtr m, const TzhEaglPoint3* v, TzhEaglPoint3* res)
{
	float x = v->x,
    y = v->y,
    z = v->z;
	
	res->x = m[kIndice_x1] * x + m[kIndice_y1] * y + m[kIndice_z1] * z;
	res->y = m[kIndice_x2] * x + m[kIndice_y2] * y + m[kIndice_z2] * z;
	res->z = m[kIndice_x3] * x + m[kIndice_y3] * y + m[kIndice_z3] * z;
}

void MatrixMultByQuaternion(const MatrixPtr m, const TzhEaglPoint4* v, TzhEaglPoint4* res)
{
	float x,y,z,w;
	x = v->x;
    y = v->y;
    z = v->z;
    w = v->w;
	
	res->x = m[kIndice_x1] * x + m[kIndice_y1] * y + m[kIndice_z1] * z + m[kIndice_w1] * w;
	res->y = m[kIndice_x2] * x + m[kIndice_y2] * y + m[kIndice_z2] * z + m[kIndice_w2] * w;
	res->z = m[kIndice_x3] * x + m[kIndice_y3] * y + m[kIndice_z3] * z + m[kIndice_w3] * w;
	res->w = m[kIndice_x4] * x + m[kIndice_y4] * y + m[kIndice_z4] * z + m[kIndice_w4] * w;
}
/***
 *功能 ： 两矩阵相乘
 *参数：
 m1, m2, [out]res
 res = m1 * m2
 *****/
void MatrixMultByMatrix(const MatrixPtr m1, const MatrixPtr m2, MatrixPtr res)
{
	MatrixMultByQuaternion(m1, MatrixGetPoint31(m2), MatrixGetPoint31(res));
	MatrixMultByQuaternion(m1, MatrixGetPoint32(m2), MatrixGetPoint32(res));
	MatrixMultByQuaternion(m1, MatrixGetPoint33(m2), MatrixGetPoint33(res));
	MatrixMultByQuaternion(m1, MatrixGetPoint34(m2), MatrixGetPoint34(res));
}
/***
 *功能 ： 计算矩阵的行列式
 *参数 ： ＊p ： 指向矩阵数组的指针
 numofrow ： 矩阵的行数
 *******/
float _Matrix_Det(float *p, int numOfRow){
    //矩阵行列式
    int i, j, m;
    int lop = 0, n = numOfRow;
    float result = 0;
    float mid = 1;
    if(n != 1){
        lop = (n == 2)?1:n;//循环次数
        for(m = 0; m < lop; m++){
            mid = 1;
            for(i = 0, j = m; i < n; i++,j--)
                mid = mid * (*( p + i * n + j % n));
            result -= mid;
        }
    }else{
        result = *p;
    }
    return result;
}

/***
 *功能：创造一个3维空间正交坐标系
 *参数： pVx : 接收x轴方向向量
 pVy : y轴方向向量
 outMatrix : 需要施加变换的矩阵
 *注意：z轴方向向量通过x，y轴计算而来；
 当y轴方向向量会重新计算，保证 正交
 *********/
void Make3DCoordSystemWith2Vec(const TzhEaglVector3* pVx, const TzhEaglVector3* pVy, Matrix outMatrix)
{
    Vector3 vz = crossOf2Vector(pVy, pVx);
    Vector3 vx;
    Vector3 vy;
    memcpy(&vx, pVx, sizeof(Vector3));
    normalOfVector(&vx);
    normalOfVector(&vz);
    vy = crossOf2Vector(&vx, &vz);
    MatrixReset(outMatrix);
    outMatrix[kIndice_x1] = vx.x; outMatrix[kIndice_x2] = vx.y; outMatrix[kIndice_x3] = vx.z;
    outMatrix[kIndice_y1] = vy.x; outMatrix[kIndice_y2] = vy.y; outMatrix[kIndice_y3] = vy.z;
    outMatrix[kIndice_z1] = vz.x; outMatrix[kIndice_z2] = vz.y; outMatrix[kIndice_z3] = vz.z;
    
}
/***
 *功能 ： 平移三维坐标系 矩阵
 *参数 ： Matrix :需要施加变换的矩阵
 x, y, z : 分别向x，y， z轴方向平移的量
 *********/
void Transfort3DCoordSystem(Matrix res, float x, float y, float z)
{
    res[kIndice_x4] = x;
    res[kIndice_y4] = y;
    res[kIndice_z4] = z;
}
/***
 *功能 ： 制造旋转矩阵——绕任意轴旋转
 *参数 ： ［out］matrix ： 待制造的矩阵
 angle  ： 旋转角度
 vX, vY,vZ : 分别表示中轴线向量的 x， y， z轴分量
 注意 ： 算法思想来源于 ： http://blog.csdn.net/tan625747/article/details/5523728
 *****/
void MakeRotatefMatrix( float angle, float vX, float vY, float vZ,Matrix outMatrix)
{
    
    //标准的左手 法则 不适应于opengl右手坐标体系！！需要做点处理
    float A = sqrtf(vX*vX + vY*vY + vZ*vZ);
    if(A == 0.)return;
    float Ax, Ay, Az;
    Ax = vX/A; Ay = vY/A; Az = -vZ/A;
    float theda = DegreesToRadians(angle);
    float C = cosf(theda);
    float S = sinf(theda);
    Matrix m = {
        C + Ax*Ax*(1 - C), Ax*Ay*(1 - C) - Az*S, -(Ax*Az*(1 - C) + Ay*S) ,  0,
        Ax*Ay*(1 - C) + Az*S, C + Ay*Ay*(1 - C), -(Ay*Az*(1 - C) - Ax*S) ,  0,
        Ax*Ay*(1 - C) - Ay*S, Ay*Az*(1 - C) + Ax*S, -(C + Az*Az*(1 - C)),   0,
        0,                    0,                0,                       1
    };
    
    memcpy(outMatrix, m , sizeof(Matrix));
}

//FUNCTIONS:
void make3DCoorSystem(const TzhEaglVector3* pVx, const TzhEaglVector3* pVy, float offsetX, float offsetY, float offsetZ, Matrix outMatrix){
    Make3DCoordSystemWith2Vec(pVx, pVy, outMatrix);
    Transfort3DCoordSystem(outMatrix, offsetX, offsetY, offsetZ);
}

void make3DCoordSystemByPoint(const TzhEaglPoint3* originPoint, const TzhEaglPoint3* Xaxis, const TzhEaglPoint3* Yaxis,
                              Matrix outMatrix){
    Vector3 Vx = vector3MadeBy2Point(originPoint, Xaxis);
    Vector3 Vy = vector3MadeBy2Point(originPoint, Yaxis);
    Make3DCoordSystemWith2Vec(&Vx, &Vy, outMatrix);
    Transfort3DCoordSystem(outMatrix, originPoint->x, originPoint->y, originPoint->z);
}

//向量乘以矩阵
void Vector4MultMatrix4(const TzhEaglVector4* v, const MatrixPtr m, TzhEaglVector4* out)
{
    MatrixMultByQuaternion(m , v, out);
}

void MakeRotationPoint3( float rX, float rY, float rZ,TzhEaglPoint3* v)
{
	Matrix m;
	
	_Matrix_SetRotationFromAngles((MatrixPtr)&m, rX, rY, rZ);
	MatrixMultByPoint3((MatrixPtr)&m, v, v);
}

void MakeRotationQuaternion(TzhEaglPoint4* v, float rX, float rY, float rZ)
{
	Matrix m;
	
	_Matrix_SetRotationFromAngles((MatrixPtr)&m, rX, rY, rZ);
	MatrixMultByQuaternion((MatrixPtr)&m, v, v);
}
//求两向量 之间的 夹角  和角度
void GetPoint3RotationAxisAndAngle(TzhEaglPoint3* vSrc, TzhEaglPoint3* vDst, TzhEaglPoint3* outAxis, float* outAngle)
{
	TzhEaglPoint3		v1 = Point3Normalize(*vSrc);
	TzhEaglPoint3		v2 = Point3Normalize(*vDst);
	TzhEaglPoint3		axis = Point3CrossProduct(v1, v2);
	float		dot = Point3DotProduct(v1, v2);
	
	*outAngle = acos(dot);
	*outAxis = Point3Normalize(axis);
}
//点 移动变换  并将移动后的点保存到 res
void TransformPoint3_Copy(MatrixPtr m, TzhEaglPoint3* v, TzhEaglPoint3* res)
{
	TzhEaglPoint3			vt;
	
	MatrixMultByPoint3(m, v, (TzhEaglPoint3*)&vt);
	
	res->x = vt.x;
	res->y = vt.y;
	res->z = vt.z;
}

void TransformPoint4_Copy(MatrixPtr m, TzhEaglPoint4* v, TzhEaglPoint4* res)
{
	TzhEaglPoint4		vt;
	
	MatrixMultByQuaternion(m, v, (TzhEaglPoint4*)&vt);
	
	res->x = vt.x/vt.w;
	res->y = vt.y/vt.w;
	res->z = vt.z/vt.w;
	res->w = vt.w/vt.w;
}

void MakeTransformationMatrix(float rX, float rY, float rZ, float tX, float tY, float tZ,MatrixPtr matrix)
{
	if((rX != 0.0) || (rY != 0.0) || (rZ != 0.0))
	{
		_Matrix_SetRotationFromAngles(matrix, rX, rY, rZ);
	}
	else
	{
		_Matrix_Clear(matrix);
	}
	matrix[kIndice_x4] = tX;
	matrix[kIndice_y4] = tY;
	matrix[kIndice_z4] = tZ;
}
void MakeTransformationMatrixFromVec2Vec( const TzhEaglVector3* fromVec,const TzhEaglVector3* toVec,const float offsetX,const float offsetY, const float offsetZ,MatrixPtr matrix){
    //    //如果两向量平行 且同向
    //    if(isParallelOf2Vector(fromVec, toVec) && (fromVec->x - toVec->x == 0 || fromVec->y - toVec->y || fromVec->z - toVec->z)){
    //        MatrixReset(matrix);
    //        return;
    //    }
    Vector3 vec = crossOf2Vector(fromVec, toVec);
    normalOfVector(&vec);
    float theda = acosf(DotOf2Vector(fromVec, toVec) / (ValueOfVector(toVec) * ValueOfVector(fromVec)));
    MakeRotatefMatrix( RadiansToDegrees(theda), vec.x, vec.y, vec.z,matrix);
    //偏移
    matrix[kIndice_x4] = offsetX;
    matrix[kIndice_y4] = offsetY;
    matrix[kIndice_z4] = offsetZ;
}
//是物体平移 信息报存在 matrix
void MakeTranslation(float offsetX, float offsetY, float offsetZ,Matrix matrix)
{
    matrix[kIndice_x4] += offsetX;
    matrix[kIndice_y4] += offsetY;
    matrix[kIndice_z4] += offsetZ;
}

void MultMatrix_Copy(MatrixPtr matrix1, MatrixPtr matrix2, MatrixPtr res)
{
	Matrix mt;
	
	MatrixMultByMatrix(matrix1, matrix2, (MatrixPtr)&mt);
	
	_Matrix_Copy((MatrixPtr)&mt, (MatrixPtr)&res);
}

void TransposeMatrix_Copy(MatrixPtr m, MatrixPtr res)
{
	Matrix mt;
	
	mt[kIndice_x1] = m[kIndice_x1];
	mt[kIndice_y1] = m[kIndice_x2];
	mt[kIndice_z1] = m[kIndice_x3];
	mt[kIndice_w1] = m[kIndice_x4];
	
	mt[kIndice_x2] = m[kIndice_y1];
	mt[kIndice_y2] = m[kIndice_y2];
	mt[kIndice_z2] = m[kIndice_y3];
	mt[kIndice_w2] = m[kIndice_y4];
	
	mt[kIndice_x3] = m[kIndice_z1];
	mt[kIndice_y3] = m[kIndice_z2];
	mt[kIndice_z3] = m[kIndice_z3];
	mt[kIndice_w3] = m[kIndice_z4];
    
	mt[kIndice_x4] = m[kIndice_w1];
	mt[kIndice_y4] = m[kIndice_w2];
	mt[kIndice_z4] = m[kIndice_w3];
	mt[kIndice_w4] = m[kIndice_w4];
    
	
	_Matrix_Copy((MatrixPtr)&mt, res);
}

void InvertTransformationMatrix_Copy(MatrixPtr m, MatrixPtr res)
{
	Matrix mt;
	
	TransposeMatrix_Copy(m, mt);
	
	_Matrix_Copy((MatrixPtr)&mt, res);
	res[kIndice_x4] = -mt[kIndice_w1];
	res[kIndice_y4] = -mt[kIndice_w2];
	res[kIndice_z4] = -mt[kIndice_w3];
}

TzhEaglPoint4 Point4TransformFromModelViewToModelView(TzhEaglPoint4 v, Matrix m1, Matrix m2)
{
	Matrix		m;
	
	TransposeMatrix_Copy(m1, (MatrixPtr)&m);
	TransformPoint4_Copy(m, (TzhEaglPoint4*)&v, (TzhEaglPoint4*)&v);
	TransformPoint4_Copy(m2, (TzhEaglPoint4*)&v, (TzhEaglPoint4*)&v);
	
	return v;
}

TzhEaglPoint3 Point3Transform(TzhEaglPoint3 v, Matrix m)
{
	Matrix		tm;
	
	TransposeMatrix_Copy(m, (MatrixPtr)&tm);
	TransformPoint4_Copy(tm, (TzhEaglPoint4*)&v, (TzhEaglPoint4*)&v);
	
	return v;
}

TzhEaglPoint3 Point3TransformFromModelViewToModelView(TzhEaglPoint3 p, Matrix m1, Matrix m2)
{
	TzhEaglPoint4		v = Point4TransformFromModelViewToModelView(Point4Make(p.x, p.y, p.z, 1.), m1, m2);
	
	return Point3Make(v.x, v.y, v.z);
}

float Point3DotProduct(TzhEaglPoint3 v1, TzhEaglPoint3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

TzhEaglPoint3 Point3CrossProduct(TzhEaglPoint3 v1, TzhEaglPoint3 v2)
{
	return Point3Make(v1.y*v2.z-v1.z*v2.y, v1.z*v2.x-v1.x*v2.z, v1.x*v2.y-v1.y*v2.x);
}

TzhEaglPoint3 Point3Normalize(TzhEaglPoint3 p)
{
	float norm = Norm(p.x, p.y, p.z);
	return Point3Make(p.x/norm, p.y/norm, p.z/norm);
}
//矩阵求逆
int  _MatrixReverse(float a[], int n){
    int *is,*js,i,j,k,l,u,v;
    float d,p;
    is = (int*)malloc(n*sizeof(int));
    js = (int*)malloc(n*sizeof(int));
    for (k=0; k<=n-1; k++)
    {
        d=0.0;
        for (i=k; i<=n-1; i++)
            for (j=k; j<=n-1; j++)
            { l=i*n+j; p=fabs(a[l]);
                if (p>d) { d=p; is[k]=i; js[k]=j;}
            }
        if (d+1.0==1.0)
        {
            free(is); free(js); printf("err**not inv\n");
            return(0);
        }
        if (is[k]!=k)
            for (j=0; j<=n-1; j++)
            { u=k*n+j; v=is[k]*n+j;
                p=a[u]; a[u]=a[v]; a[v]=p;
            }
        if (js[k]!=k)
            for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+js[k];
                p=a[u]; a[u]=a[v]; a[v]=p;
            }
        l=k*n+k;
        a[l]=1.0/a[l];
        for (j=0; j<=n-1; j++)
            if (j!=k)
            { u=k*n+j; a[u]=a[u]*a[l];}
        for (i=0; i<=n-1; i++)
            if (i!=k)
                for (j=0; j<=n-1; j++)
                    if (j!=k)
                    { u=i*n+j;
                        a[u]=a[u]-a[i*n+k]*a[k*n+j];
                    }
        for (i=0; i<=n-1; i++)
            if (i!=k)
            { u=i*n+k; a[u]=-a[u]*a[l];}
    }
    for (k=n-1; k>=0; k--)
    { if (js[k]!=k)
        for (j=0; j<=n-1; j++)
        { u=k*n+j; v=js[k]*n+j;
            p=a[u]; a[u]=a[v]; a[v]=p;
        }
        if (is[k]!=k)
            for (i=0; i<=n-1; i++)
            { u=i*n+k; v=i*n+is[k];
                p=a[u]; a[u]=a[v]; a[v]=p;
            }
    }
    free(is); free(js);
    return(1);
    
}
int _InvertMatrixd(const float m[16], float invOut[16])
{
    // printf("in __gluInvertMatrixed------>\n");
    //printArray(&m[0], 16);
    float inv[16], det;
    int i;
    inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
    + m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    inv[4] = -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
    - m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    inv[8] =  m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15];
    inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
    - m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    inv[1] = -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
    - m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
    inv[5] =  m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
    + m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
    inv[9] = -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
    - m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
    inv[13] = m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
    + m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
	inv[2] =  m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
    + m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
    inv[6] = -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
    - m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
    inv[10] = m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
    + m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
    inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
    - m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
    inv[3] = -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
    - m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
    inv[7] = m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
    + m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
    inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
    - m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
    inv[15] = m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
    + m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];
    det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
    if (det == 0)
        return 1;
    
    det = 1.0 / det;
    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
    return 1;
}


//求4 ＊ 4 矩阵行列式
float Matrix4Det(Matrix m){
    return  _Matrix_Det(m , 4);
}
//矩阵求逆
void Matrix4Reverse(Matrix m, Matrix res )
{
    TransposeMatrix_Copy(m, res);
    //_MatrixReverse(res, 4);
    _InvertMatrixd(m ,res);
}
/***
 *功能 ： 对矩形做 平移，旋转等变换
 *参数 ： rect ： 源矩形
 ［out］outRect ： 变换后的矩阵
 M : 施加变换的矩阵
 *****/
void RectangleMultMatrix(const TzhEaglRectangle* rect,TzhEaglMatrix M,TzhEaglRectangle* outRect){
    TzhEaglPoint3 p1 = Point3Transform_w(&rect->leftTop, M) ;
    TzhEaglPoint3 p2 = Point3Transform_w(&rect->leftButtom, M);
    TzhEaglPoint3 p3 = Point3Transform_w(&rect->rightButtom, M);
    TzhEaglRectangle temp = zhEaglRectangleMake(p1, p2, p3);
    memcpy(outRect, &temp, sizeof(TzhEaglRectangle));
}
TzhEaglPoint3 Point3Transform_w(const TzhEaglPoint3* p, Matrix m){
    float x, y, z, w;
    x = p->x; y = p->y; z = p->z; w = 1;
    TzhEaglPoint3 ret;
    ret.x = x * m[kIndice_x1] + y * m [kIndice_x2] + z * m[kIndice_x3] + w * m[kIndice_x4];
    ret.y = x * m[kIndice_y1] + y * m [kIndice_y2] + z * m[kIndice_y3] + w * m[kIndice_y4];
    ret.z = x * m[kIndice_z1] + y * m [kIndice_z2] + z * m[kIndice_z3] + w * m[kIndice_z4];
    return ret;
}
void RectangleMultDirect(const TzhEaglRectangle* rect, float x, float y, float z,TzhEaglRectangle* outRect)
{
    Matrix m;
    MatrixReset(m );
    m[kIndice_x4] = x;
    m[kIndice_y4] = y;
    m[kIndice_z4] = z;
    RectangleMultMatrix(rect, m,outRect);
}
void printMatrix4(Matrix mt){
    printf("\n[ %f %f %f %f ]\n[ %f %f %f %f ]\n[ %f %f %f %f ]\n[ %f %f %f %f ]\n",
           mt[kIndice_x1], mt[kIndice_y1], mt[kIndice_z1], mt[kIndice_w1],
           mt[kIndice_x2], mt[kIndice_y2], mt[kIndice_z2], mt[kIndice_w2],
           mt[kIndice_x3], mt[kIndice_y3], mt[kIndice_z3], mt[kIndice_w3],
           mt[kIndice_x4], mt[kIndice_y4], mt[kIndice_z4], mt[kIndice_w4]);
}

TzhEaglRect zhEaglRectMake(float x, float y, float width, float height)
{
    TzhEaglRect rect;
    rect.x = x; rect.y = y;
    rect.width = width; rect.height = height;
    return rect;
}

TzhEaglSize zhEaglSizeMake(float width, float height)
{
    TzhEaglSize rect;
    rect.width = width; rect.height = height;
    return rect;
}

TzhEaglColorRGB zhEaglColorRGBMake(float r,float g,float b)
{
    TzhEaglColorRGB rgb;
    rgb.r=r;
    rgb.g=g;
    rgb.b=b;
    return rgb;
}

TzhEaglColorRGBA zhEaglColorRGBAMake(float r,float g,float b,float a)
{
    TzhEaglColorRGBA rgba;
    rgba.r=r;
    rgba.g=g;
    rgba.b=b;
    rgba.a=a;
    return rgba;
}


//常用 点 向量操作
inline Point3 Point3Make(float x, float y, float z)
{
	Point3 p;
	p.x=x;
	p.y=y;
	p.z=z;
	return p;
}

inline Point3 Point3Add(Point3 p1, Vector3 p2)
{
	Point3 p;
	p.x=p1.x + p2.x;
	p.y=p1.y + p2.y;
	p.z=p1.z + p2.z;
	return p;
}

inline Point3 Point3Sub(Point3 p1, Point3 p2)
{
	Point3 p;
	p.x=p1.x - p2.x;
	p.y=p1.y - p2.y;
	p.z=p1.z - p2.z;
	return p;
}

inline Point3 Point3Mult(Point3 p1, float l)
{
	Point3 p;
	p.x=p1.x * l;
	p.y=p1.y * l;
	p.z=p1.z * l;
	return p;
}

inline int Point3EqualsPoint3(Point3 p1, Point3 p2)
{
	return (p1.x == p2.x) && (p1.y == p2.y) && (p1.z == p2.z);
}

inline float Point3Norm(Point3 p)
{
	return sqrt((p.x * p.x) + (p.y * p.y) + (p.z * p.z));
}

/* Point4 */

inline Point4 Point4Make(float x, float y, float z, float w)
{
	Point4 p;
	p.x=x;
	p.y=y;
	p.z=z;
	p.w=w;
	return p;
}

inline Point4 Point4Mult(Point4 p1, float l)
{
	Point4 p;
	p.x=p1.x * l;
	p.y=p1.y * l;
	p.z=p1.z * l;
	p.w=p1.w * l;
	return p;
}

inline Point4 Point4Make(float x, float y, float z, float w)
{
	Point4 p;
	p.x=x;
	p.y=y;
	p.z=z;
	p.w=w;
	return p;
}

inline Point4 Point4Mult(Point4 p1, float l)
{
	Point4 p;
	p.x=p1.x * l;
	p.y=p1.y * l;
	p.z=p1.z * l;
	p.w=p1.w * l;
	return p;
}